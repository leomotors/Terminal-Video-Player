#include "colors.hpp"

#include <cmath>
#include <string>

namespace tplay::colors {

std::map<Color, std::string> ColorToAnsi;

std::string makeColor(Colors color, auto c) {
    return AnsiCodes.at(color) + c + AnsiReset;
}

Color darkenColor(Colors color, double brightness) {
    auto [r, g, b] = WinTerm.at(color);
    r = static_cast<uint8_t>(std::round(r * brightness));
    g = static_cast<uint8_t>(std::round(g * brightness));
    b = static_cast<uint8_t>(std::round(b * brightness));
    return {r, g, b};
}

}  // namespace tplay::colors
