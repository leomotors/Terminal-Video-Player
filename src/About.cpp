#include "About.hpp"

#include <string>

#include "AppProps.h"

std::string tplay::about::About()
{
    return std::string("Terminal Video Player\nVersion: ") + APP_VERSION +
           "\nMade by Leomotors\n" +
           "GitHub Repository: "
           "https://github.com/Leomotors/Terminal-Video-Player";
}

std::string tplay::about::AboutShort()
{
    return std::string("Terminal Video Player ") + APP_VERSION;
}
