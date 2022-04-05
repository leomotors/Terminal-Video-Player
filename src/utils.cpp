#include "utils.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

extern "C" {
#include "lib/getch.h"
}

#include "About.hpp"

namespace tplay::utils {

String::String(char *filename) : content(filename) {
    // https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
    int x, y;

    std::string result;

    std::printf("%s\033[6n", filename);

    do {
        result += getch();
    } while (result.back() != 'R');

    std::sscanf(result.c_str(), "\033[%d;%dR", &x, &y);

    this->actualLength = y - 1;
}

std::string createHeader(String filename, int framesPassed, int totalFrames,
                         double fps, int colLimit) {
    const std::string about = tplay::about::AboutShort();

    if (about.size() > (std::size_t)colLimit) return std::string(colLimit, ' ');

    int totalLength = totalFrames / fps;
    int currentTime = framesPassed / fps;

    const std::string timePos =
        '[' + formatTime(currentTime) + "/" + formatTime(totalLength) + ']';

    if (about.size() + timePos.size() + 1 > (std::size_t)colLimit)
        return about + std::string(colLimit - about.size(), ' ');

    if (about.size() + timePos.size() + filename.actualLength + 2 >
        (std::size_t)colLimit)
        return about + " " + timePos +
               std::string(colLimit - about.size() - timePos.size() - 1, ' ');

    return about + " " + filename.content + " " + timePos +
           std::string(colLimit - about.size() - timePos.size() -
                           filename.actualLength - 2,
                       ' ');
}

std::string formatTime(int seconds) {
    int minutes = seconds / 60;
    seconds %= 60;

    return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") +
           std::to_string(seconds);
}

}  // namespace tplay::utils
