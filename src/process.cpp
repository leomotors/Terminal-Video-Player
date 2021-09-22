#include "process.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

const char *ASCII_ARRAY{".-+*wGHM#&%"}; // * 12 Levels

void processFrame(cv::Mat Frame, int width, int height)
{
    cv::cvtColor(Frame, Frame, cv::COLOR_BGR2GRAY);
    cv::resize(Frame, Frame, cv::Size(width, height));

    std::string screen{"\n\n\n\n\n"};
    screen.reserve(width * height * 2);

    for (int i = 0; i < Frame.rows; i++)
    {
        const uint8_t *col = Frame.ptr<uint8_t>(i);
        for (int j = 0; j < Frame.cols; j++)
        {
            screen += ASCII_ARRAY[(int)col[j] * 11 / 256];
        }
        screen += '\n';
    }
    screen.pop_back();

    std::cout << screen;
}
