#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int height = 9;
int width = 7;

void PrintMatrix(const std::vector<std::vector<int>>& matrix, int start_x, int start_y, int end_x, int end_y) {
  const std::string symbols = " .o+=*BOX@%&#/^";
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      if (x == start_x && y == start_y) std::cout << " S ";
      else if (x == end_x && y == end_y) std::cout << " E ";
      else {
        char sym = std::min(matrix[y][x], 14);
        std::cout << ' ' << symbols[sym] << ' ';
      }
    }
    std::cout << std::endl;
  }
}

int main(void) {
  std::vector<std::vector<int>> vec(height, std::vector<int>(width, 0));
  int x = width / 2;
  int y = height / 2;

  std::string str("Hello, World!");

  for (char c : str) {
    for (size_t i = 0; i < 4; ++i) {
      int bit = c & 3;
      c >>= 2;

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
  }
  PrintMatrix(vec, width / 2, height / 2, x, y);
  return 0;
}
