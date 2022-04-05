#pragma once

#include <opencv2/opencv.hpp>

#include "colors.hpp"

namespace tplay::process {

extern char *ascii_array;
extern int ascii_arrlen;
void setup(int options1, int options2);
void setupColor(int options2);
void processFrame(cv::Mat Frame, int width, int height, std::string header);

std::string getClosestColorLinear(colors::Color target);

void processFrameColor(cv::Mat Frame, int width, int height,
                       std::string header);

}  // namespace tplay::process
