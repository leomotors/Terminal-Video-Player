#include "process.hpp"

#include <cstring>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

// * Options 1: 1 for 11 Levels, 2 for 69 Levels (Default)
// * Options 2: 1 to use dot for darkest (Default), 2 to use blank space for darkest
void tplay::process::setup(int options1, int options2)
{
    if (options1 == 1)
    {
        ascii_arrlen = 11 + options2 - 1;
        ascii_array = new char[11 + options2];
        std::strcpy(ascii_array,
                    options2 == 1 ? ".-+*wGHM#&%" : " .-+*wGHM#&%");
    }
    else
    {
        ascii_arrlen = 69 + options2 - 1;
        ascii_array = new char[69 + options2];
        // https://stackoverflow.com/questions/30097953/ascii-art-sorting-an-array-of-ascii-characters-by-brightness-levels-c-c
        std::strcpy(ascii_array,
                    options2 == 1 ? ".\'`^\",:;Il!i><~+_-?][}{1)(|\\/"
                                    "tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
                                  : " .\'`^\",:;Il!i><~+_-?][}{1)(|\\/"
                                    "tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$");
    }
}

void tplay::process::processFrame(cv::Mat Frame, int width, int height,
                                  std::string header)
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
            screen += ascii_array[(int)col[j] * ascii_arrlen / 256];
        }
        screen += '\n';
    }
    screen.pop_back();

    // https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
    std::cout << "\033[0;0H";
    std::cout << screen << std::flush;
}
