#pragma once

#include <map>
#include <tuple>

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

const std::map<Colors, Color> WinTerm = {
    {Colors::Black, {12, 12, 12}},
    {Colors::Red, {197, 15, 31}},
    {Colors::Green, {19, 161, 14}},
    {Colors::Yellow, {193, 156, 0}},
    {Colors::Blue, {0, 55, 218}},
    {Colors::Magenta, {136, 23, 152}},
    {Colors::Cyan, {58, 150, 221}},
    {Colors::White, {204, 204, 204}},
    {Colors::BrightBlack, {118, 118, 118}},
    {Colors::BrightRed, {231, 72, 86}},
    {Colors::BrightGreen, {22, 198, 12}},
    {Colors::BrightYellow, {249, 241, 165}},
    {Colors::BrightBlue, {59, 120, 255}},
    {Colors::BrightMagenta, {180, 0, 158}},
    {Colors::BrightCyan, {97, 214, 214}},
    {Colors::BrightWhite, {242, 242, 242}}};

extern std::map<Color, std::string> ColorToAnsi;

std::string makeColor(Colors color, auto c);
Color darkenColor(Colors color, double brightness);
inline void addAnsiToMap(Colors color, char c, double brightness) {
    ColorToAnsi[darkenColor(color, brightness)] =
        AnsiCodes.at(color) + c + AnsiReset;
}

}  // namespace tplay::colors
