#pragma once

#include <opencv2/opencv.hpp>

namespace tplay::process {

static char *ascii_array;
static int ascii_arrlen;
void setup(int options1, int options2);
void processFrame(cv::Mat Frame, int width, int height, std::string header);

}  // namespace tplay::process
