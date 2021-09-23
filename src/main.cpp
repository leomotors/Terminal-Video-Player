#include "process.hpp"

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
            std::cout << About() << std::endl;
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

    std::string toExec("ffmpeg -y -i \"");
    toExec += input_file + "\" .tplaytemp.mp3";
    std::cout << "Executing: " << toExec << std::endl;
    std::system(toExec.c_str());

    bool setupCompleted{false};

    // https://stackoverflow.com/questions/44654548/stdasync-doesnt-work-asynchronously
    std::future<void> audio = std::async(std::launch::async, playAudio,
                                         ".tplaytemp.mp3", &setupCompleted);

    while (!setupCompleted)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto StartTime = std::chrono::steady_clock::now();
    int framesPassed{0};

    while (true)
    {
        cv::Mat frame;
        InputVid >> frame;
        framesPassed++;

        if (frame.empty())
            break;

        processFrame(frame, getWinCol(), getWinRow() - 1);
        std::this_thread::sleep_until(
            StartTime +
            std::chrono::microseconds((int)(1000000 * framesPassed / fps)));
    }

    InputVid.release();
    return EXIT_SUCCESS;
}
