#include "About.hpp"

#include <string>

#include "AppProps.h"

namespace tplay::about {

std::string About() {
    return std::string(
               "Terminal Video Player 2 ～CANDY COLOR DAYS～\n"
               "App Version: ") +
           APP_VERSION +
           "\nMade by Leomotors\n"
           "GitHub Repository: "
           "https://github.com/Leomotors/Terminal-Video-Player";
}

std::string AboutShort() {
    return std::string("Terminal Video Player ") + APP_VERSION;
}

}  // namespace tplay::about