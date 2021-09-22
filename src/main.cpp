#include "process.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

#define DEFAULT_WIDTH 120
#define DEFAULT_HEIGHT 30

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Invalid Argument!" << std::endl;
        return EXIT_FAILURE;
    }

    int width{DEFAULT_WIDTH};
    int height{DEFAULT_HEIGHT};

    if (argc > 2)
    {
        if (argc < 4)
        {
            std::cerr << "Please specify height too!" << std::endl;
            return EXIT_FAILURE;
        }

        std::stringstream swidth(argv[2]), sheight(argv[3]);
        swidth >> width;
        sheight >> height;

        if (width <= 0 || width >= 1280)
        {
            std::cerr << "Invalid Width of " << width << " (" << argv[2] << ")" << std::endl;
            return EXIT_FAILURE;
        }
        if (height <= 0 || height >= 720)
        {
            std::cerr << "Invalid Height of " << height << " (" << argv[3] << ")" << std::endl;
            return EXIT_FAILURE;
        }
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

        processFrame(frame, width, height);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / fps)));
    }

    InputVid.release();

    return EXIT_SUCCESS;
}
