#include "process.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

const char *ASCII_ARRAY{".-+*wGHM#&%"}; // * 12 Levels

void processFrame(cv::Mat Frame, int width, int height, std::string header)
{
    cv::cvtColor(Frame, Frame, cv::COLOR_BGR2GRAY);
    cv::resize(Frame, Frame, cv::Size(width, height));

    std::string screen{header};
    screen += '\n';

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

    // https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
    std::cout << "\033[0;0H";
    std::cout << screen << std::flush;
}
