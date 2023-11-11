#include "colors.hpp"

#include <cmath>
#include <string>

namespace tplay::colors {

const std::map<Colors, std::string> AnsiCodes = {
    {Colors::Black, "\u001b[30m"},       {Colors::Red, "\u001b[31m"},
    {Colors::Green, "\u001b[32m"},       {Colors::Yellow, "\u001b[33m"},
    {Colors::Blue, "\u001b[34m"},        {Colors::Magenta, "\u001b[35m"},
    {Colors::Cyan, "\u001b[36m"},        {Colors::White, "\u001b[37m"},
    {Colors::BrightBlack, "\u001b[90m"}, {Colors::BrightRed, "\u001b[91m"},
    {Colors::BrightGreen, "\u001b[92m"}, {Colors::BrightYellow, "\u001b[93m"},
    {Colors::BrightBlue, "\u001b[94m"},  {Colors::BrightMagenta, "\u001b[95m"},
    {Colors::BrightCyan, "\u001b[96m"},  {Colors::BrightWhite, "\u001b[97m"},
};

const std::string AnsiReset = "\u001b[0m";

//--- BEGIN USER CONFIG ---//
const std::vector<Colors> disabledColors = {};

const std::map<Colors, Color> WinTerm = {
    // Use neofetch to get these colors, these are specific to terminal
    {Colors::Black, {12, 12, 12}},
    {Colors::Red, {184, 49, 27}},
    {Colors::Green, {87, 192, 56}},
    {Colors::Yellow, {198, 196, 63}},
    {Colors::Blue, {12, 37, 191}},
    {Colors::Magenta, {185, 62, 193}},
    {Colors::Cyan, {88, 195, 197}},
    {Colors::White, {199, 199, 199}},
    {Colors::BrightBlack, {104, 104, 104}},
    {Colors::BrightRed, {237, 119, 109}},
    {Colors::BrightGreen, {140, 247, 122}},
    {Colors::BrightYellow, {254, 252, 126}},
    {Colors::BrightBlue, {108, 147, 203}},
    {Colors::BrightMagenta, {237, 127, 248}},
    {Colors::BrightCyan, {142, 250, 253}},
    {Colors::BrightWhite, {255, 255, 255}}};
//--- END USER CONFIG ---//

bool isDisabledColor(Colors color) {
    for (auto c : disabledColors) {
        if (color == c) return true;
    }

    return false;
}

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
