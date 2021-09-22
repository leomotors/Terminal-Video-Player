#include "process.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: Invalid Argument!" << std::endl;
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

    while (true)
    {
        cv::Mat frame;
        InputVid >> frame;

        if (frame.empty())
            break;

        processFrame(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / fps)));
    }

    InputVid.release();

    return EXIT_SUCCESS;
}
