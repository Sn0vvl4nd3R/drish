#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const size_t offset = 0xcbf29ce484222325;
const size_t prime = 0x100000001b3;

const int height = 9;
const int width = 7;

uint64_t fnv(std::string str) {
  uint64_t hash = offset;
  for (const char& byte : str) {
    hash ^= byte;
    hash *= prime;
  }
  return hash;
}

void PrintSymLine(void) {
  std::cout << '+';
  for (size_t i = 0; i < width; ++i) std::cout << '-';
  std::cout << "+\n";
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix, size_t start_x,
                 size_t start_y, size_t end_x, size_t end_y) {
  const std::string symbols = " .o+=*BOX@%&#/^";
  PrintSymLine();
  for (size_t y = 0; y < height; ++y) {
    std::cout << '|';
    for (size_t x = 0; x < width; ++x) {
      if (x == start_x && y == start_y)
        std::cout << "S";
      else if (x == end_x && y == end_y)
        std::cout << "E";
      else {
        char sym = std::min(matrix[y][x], 14);
        std::cout << symbols[sym];
      }
    }
    std::cout << '|' << std::endl;
  }
  PrintSymLine();
}

int main(void) {
  std::vector<std::vector<int>> vec(height, std::vector<int>(width, 0));
  int x = width / 2;
  int y = height / 2;

  std::string str("Hello, World!");
  uint64_t hash = fnv(str);

  for (size_t i = 0; i < 32; ++i) {
    int bit = hash & 3;
    hash >>= 2;

    switch (bit) {
      case (0):
        --x;
        --y;
        break;
      case (1):
        ++x;
        --y;
        break;
      case (2):
        --x;
        ++y;
        break;
      case (3):
        ++x;
        ++y;
        break;
    }

    if (x < 0) {
      ++x;
    } else if (x > width - 1) {
      --x;
    }
    if (y < 0) {
      ++y;
    } else if (y > height - 1) {
      --y;
    }

    vec[y][x]++;
  }
  PrintMatrix(vec, width / 2, height / 2, x, y);
  return 0;
}
