#include <chrono>
#include <cmath>
#include <cstdlib>
#include <future>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

extern "C" {
#include "lib/playAudio.h"
#include "lib/winSize.h"
}

#include "About.hpp"
#include "process.hpp"
#include "utils.hpp"

#define DEFAULT_OPTION_1 2
#define DEFAULT_OPTION_2 1

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Invalid Argument!" << std::endl;
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        if (argv[1][1] == 'v') {
            std::cout << tplay::about::About() << std::endl;
            return EXIT_SUCCESS;
        }
        if (argv[1][1] == 'h') {
            std::cout << "Usage: tplay \"Your Video File Name\""
                      << " [Optional: -cxx or -lxx (See src/process.cpp for "
                         "more detail)]"
                      << std::endl;
            return EXIT_SUCCESS;
        }

        std::cerr << "Unknown Option: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    int options1 = DEFAULT_OPTION_1;
    int options2 = DEFAULT_OPTION_2;

    bool ColorMode = true;

    if (argc == 3) {
        if (argv[2][0] != '-') {
            std::cerr << "Invalid Arguments: " << argv[2][0] << std::endl;
            return EXIT_FAILURE;
        }
        if (argv[2][1] != 'l' && argv[2][1] != 'c') {
            std::cerr << "Invalid Arguments: " << argv[2][0] << std::endl;
            return EXIT_FAILURE;
        }

        if (argv[2][1] != 'c') {
            ColorMode = false;
        }

        if (argv[2][2] == '1') options1 = 1;
        if (argv[2][2] && argv[2][3] == '2') options2 = 2;
    }

    tplay::process::setup(options1, options2);

    if (ColorMode) tplay::process::setupColor(options2);

    std::string input_file(argv[1]);
    cv::VideoCapture InputVid(input_file);

    if (!InputVid.isOpened()) {
        std::cerr << "Error Opening Video File" << std::endl;
        return EXIT_FAILURE;
    }

    const double fps = InputVid.get(cv::CAP_PROP_FPS);
    const int totalFrames = InputVid.get(cv::CAP_PROP_FRAME_COUNT);

    std::cout << tplay::about::AboutShort() << "\n"
              << "Input Video: " << argv[1] << "\n"
              << "Video FPS: " << fps << "\n"
              << std::endl;

    std::string toExec("ffmpeg -y -i \"");
    toExec += input_file + "\" .tplaytemp.mp3";
    std::cout << "Executing: " << toExec << std::endl;
    std::system(toExec.c_str());

    bool setupCompleted{false};

    // https://stackoverflow.com/questions/44654548/stdasync-doesnt-work-asynchronously
    std::future<void> audio = std::async(std::launch::async, playAudio,
                                         ".tplaytemp.mp3", &setupCompleted);

    tplay::utils::String filename(argv[1]);
    int framesPassed = 0;
    int framesMissed = 0;
    int totalLength = totalFrames / fps;

    while (!setupCompleted)
        std::this_thread::sleep_for(std::chrono::microseconds(500));

    const auto StartTime = std::chrono::steady_clock::now();
    while (true) {
        cv::Mat frame;
        InputVid >> frame;
        framesPassed++;

        if (frame.empty()) break;

        auto expectedTime =
            StartTime + std::chrono::microseconds(static_cast<int64_t>(
                            1000000.0 * framesPassed / fps));

        if (std::chrono::steady_clock::now() > expectedTime) {
            framesMissed++;
            continue;
        }

        int col = getWinCol();
        int row = getWinRow() - 1;
        (ColorMode ? tplay::process::processFrameColor
                   : tplay::process::processFrame)(
            frame, col, row,
            tplay::utils::createHeader(filename, framesPassed, totalLength, fps,
                                       col));

        std::this_thread::sleep_until(expectedTime);
    }

    InputVid.release();

    int32_t frameRendered = totalFrames - framesMissed;
    double apparentFPS = frameRendered / totalLength;
    apparentFPS = apparentFPS > fps ? fps : apparentFPS;

    int lastcol = getWinCol();
    int lastrow = getWinRow() - 1;

    std::cout << "\nBENCHMARK RESULT\n";
    std::cout << "Current Resolution (NOT AVERAGE): " << lastcol << "x"
              << lastrow << " (" << lastcol * lastrow << " pixels)\n";
    std::cout << "Successfully played " << totalFrames - framesMissed
              << " from " << totalFrames << " frames\n";
    std::cout << "Actual FPS: " << fps << "\n";
    std::cout << "Average Apparent FPS: " << apparentFPS << "\n";
    std::cout << "FPS Percentage: " << apparentFPS / fps * 100 << "%\n";

    double score = (lastcol * lastrow / (80.0 * 24.0) * 1000.0) * (fps / 30) *
                   std::pow(apparentFPS / fps, 0.8);

    std::cout << "BENCHMARK SCORE: " << score << "\n";

    return EXIT_SUCCESS;
}
