#include "process.hpp"

#include <cstring>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "colors.hpp"

// * Options 1: 1 for 11 Levels, 2 for 69 Levels (Default)
// * Options 2: 1 to use dot for darkest (Default),
// * 2 to use blank space for darkest

namespace tplay::process {

char *ascii_array;
int ascii_arrlen;

void setup(int options1, int options2) {
    if (options1 == 1) {
        ascii_arrlen = 11 + options2 - 1;
        ascii_array = new char[11 + options2];
        std::strcpy(ascii_array,
                    options2 == 1 ? ".-+*wGHM#&%" : " .-+*wGHM#&%");
    } else {
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

void setupColor(int options2) {
    for (int i = 0; i < ascii_arrlen; i++) {
        for (int c = 0; c < 16; c++) {
            colors::addAnsiToMap(
                static_cast<colors::Colors>(c), ascii_array[i],
                options2 == 1 ? static_cast<double>(i + 1) / (ascii_arrlen)
                              : i / (ascii_arrlen - 1.0));
        }
    }
}

void processFrame(cv::Mat Frame, int width, int height, std::string header) {
    cv::resize(Frame, Frame, cv::Size(width, height));
    cv::cvtColor(Frame, Frame, cv::COLOR_BGR2GRAY);

    std::string screen{header};
    screen += '\n';

    screen.reserve(width * height * 2);

    for (int i = 0; i < Frame.rows; i++) {
        const uint8_t *col = Frame.ptr<uint8_t>(i);
        for (int j = 0; j < Frame.cols; j++) {
            screen += ascii_array[(int)col[j] * ascii_arrlen / 256];
        }
        screen += '\n';
    }
    screen.pop_back();

    // https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
    std::cout << "\033[0;0H";
    std::cout << screen << std::flush;
}

std::string getClosestColorLinear(colors::Color target) {
    int32_t closest = INT32_MAX;
    colors::Color closestColor;

    int32_t tr = std::get<0>(target);
    int32_t tg = std::get<1>(target);
    int32_t tb = std::get<2>(target);

    for (const auto &[color, ansi] : colors::ColorToAnsi) {
        int32_t r = std::get<0>(color);
        int32_t g = std::get<1>(color);
        int32_t b = std::get<2>(color);

        int32_t dist =
            (tr - r) * (tr - r) + (tg - g) * (tg - g) + (tb - b) * (tb - b);

        if (dist < closest) {
            closest = dist;
            closestColor = color;
        }
    }

    return colors::ColorToAnsi.at(closestColor);
}

void processFrameColor(cv::Mat Frame, int width, int height,
                       std::string header) {
    cv::resize(Frame, Frame, cv::Size(width, height));

    std::string screen{header};
    screen += '\n';

    screen.reserve(width * height * 12);

    for (int i = 0; i < Frame.rows; i++) {
        const auto *col = Frame.ptr<cv::Vec3b>(i);
        for (int j = 0; j < Frame.cols; j++) {
            colors::Color color = {col[j][2], col[j][1], col[j][0]};
            screen += getClosestColorLinear(color);
        }
        screen += '\n';
    }
    screen.pop_back();

    // https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
    std::cout << "\033[0;0H";
    std::cout << screen << std::flush;
}

}  // namespace tplay::process
