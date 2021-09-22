#include "process.hpp"

#include <opencv2/opencv.hpp>

const char *ASCII_ARRAY{".-+*wGHM#&%"}; // * 12 Levels

cv::Mat processFrame(cv::Mat Frame)
{
    cv::cvtColor(Frame, Frame, cv::COLOR_BGR2GRAY);
    cv::resize(Frame, Frame, cv::Size(120, 80));

    for (int i = 0; i < Frame.rows; i++)
    {
        const uint8_t *col = Frame.ptr<uint8_t>(i);
        for (int j = 0; j < Frame.cols; j++)
            std::cout << col[j] << " ";
        std::cout << std::endl;
    }
    std::cout << "=====================" << std::endl;

    return Frame;
}
