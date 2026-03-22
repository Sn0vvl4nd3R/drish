#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const uint64_t offset = 0xcbf29ce484222325;
const uint64_t prime = 0x100000001b3;

int height = 0;
int width = 0;

uint64_t fnv(const std::string& str) {
  uint64_t hash = offset;
  for (const char& byte : str) {
    hash ^= byte;
    hash *= prime;
  }
  return hash;
}

void PrintSymLine(void) {
  std::cout << '+';
  for (int i = 0; i < width; ++i) std::cout << '-';
  std::cout << "+\n";
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix, int start_x,
                 int start_y, int end_x, int end_y) {
  const std::string symbols = " .o+=*BOX@%&#/^";
  PrintSymLine();
  for (int y = 0; y < height; ++y) {
    std::cout << '|';
    for (int x = 0; x < width; ++x) {
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
  std::cout << "Enter the height & width:\n";
  std::cin >> height >> width;

  std::vector<std::vector<int>> vec(height, std::vector<int>(width, 0));
  int x = width / 2;
  int y = height / 2;

  std::cout << "Enter your string:\n";
  std::string str;
  std::getline(std::cin >> std::ws, str);

  int total_steps = width * height;
  int steps_done = 0;
  int iter = 0;
  while (steps_done < total_steps) {
    uint64_t hash = fnv(str + std::to_string(iter));
    iter++;
    for (size_t i = 0; i < 32 && steps_done < total_steps; ++i) {
      int bit = hash & 3;
      hash >>= 2;
      steps_done++;

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
