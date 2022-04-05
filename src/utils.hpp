#pragma once

#include <string>

namespace tplay::utils {
struct String {
  public:
    std::string content;
    int actualLength;

    String(char *filename);
};

std::string createHeader(String filename, int framesPassed, int totalLength,
                         double fps, int colLimit);

std::string formatTime(int seconds);
}  // namespace tplay::utils
