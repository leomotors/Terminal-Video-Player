#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace tplay::colors {

typedef std::tuple<uint8_t, uint8_t, uint8_t> Color;

enum class Colors {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
};

extern const std::map<Colors, std::string> AnsiCodes;
extern const std::string AnsiReset;
extern const std::vector<Colors> disabledColors;
extern const std::map<Colors, Color> WinTerm;

bool isDisabledColor(Colors color);

extern std::map<Color, std::string> ColorToAnsi;

std::string makeColor(Colors color, auto c);
Color darkenColor(Colors color, double brightness);
inline void addAnsiToMap(Colors color, char c, double brightness) {
    auto converted = darkenColor(color, brightness);

    if (ColorToAnsi.find(converted) != ColorToAnsi.end()) return;

    ColorToAnsi[converted] = AnsiCodes.at(color) + c + AnsiReset;
}

}  // namespace tplay::colors
