#include "process.hpp"

#include <cstdlib>
#include <future>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return EXIT_FAILURE;

    std::string input_file(argv[1]);
    cv::VideoCapture InputVid(input_file);

    if (!InputVid.isOpened())
    {
        std::cerr << "Error Opening Video File" << std::endl;
        return EXIT_FAILURE;
    }

    while (true)
    {
        cv::Mat frame;
        InputVid >> frame;

        cv::Mat processed = processFrame(frame);

        if (frame.empty())
            break;
    }

    InputVid.release();

    return EXIT_SUCCESS;
}
