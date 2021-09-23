#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

extern "C"
{
#include "lib/playAudio.h"
#include "lib/winSize.h"
}

#include "About.hpp"
#include "process.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Invalid Argument!" << std::endl;
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-')
    {
        if (argv[1][1] == 'v')
        {
            std::cout << tplay::about::About() << std::endl;
            return EXIT_SUCCESS;
        }
        if (argv[1][1] == 'h')
        {
            std::cout << "Usage: tplay \"Your Video File Name\"" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cerr << "Unknown Option: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::string input_file(argv[1]);
    cv::VideoCapture InputVid(input_file);

    if (!InputVid.isOpened())
    {
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
    int framesPassed{0};

    while (!setupCompleted)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    const auto StartTime = std::chrono::steady_clock::now();
    while (true)
    {
        cv::Mat frame;
        InputVid >> frame;
        framesPassed++;

        if (frame.empty())
            break;

        auto expectedTime =
            StartTime + std::chrono::microseconds(
                            (int64_t)(1000000.0 * framesPassed / fps));

        if (std::chrono::steady_clock::now() > expectedTime)
            continue;

        int col = getWinCol();
        int row = getWinRow() - 1;
        processFrame(frame, col, row,
                     tplay::utils::createHeader(filename, framesPassed,
                                                totalFrames, fps, col));

        std::this_thread::sleep_until(expectedTime);
    }

    InputVid.release();
    return EXIT_SUCCESS;
}
