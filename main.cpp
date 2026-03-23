#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

const uint64_t offset = 0xcbf29ce484222325;
const uint64_t prime = 0x100000001b3;

class DrunkenBishop {
 private:
  int height_;
  int width_;
  std::pair<int, int> start_;
  std::pair<int, int> end_;
  std::vector<std::vector<int>> vec_;
  std::string str_;

  void PrintSymLine(void) {
    std::cout << '+';
    for (int i = 0; i < width_; ++i) std::cout << '-';
    std::cout << "+\n";
  }

  uint64_t FNV(std::string iter) {
    std::string iter_string = str_ + iter;
    uint64_t hash = offset;
    for (const char& byte : iter_string) {
      hash ^= byte;
      hash *= prime;
    }
    return hash;
  }

  void Process(void) {
    int total_steps = width_ * height_;
    int steps_done = 0;
    int iter = 0;
    while (steps_done < total_steps) {
      uint64_t hash = FNV(std::to_string(iter));
      iter++;
      for (size_t i = 0; i < 32 && steps_done < total_steps; ++i) {
        int bit = hash & 3;
        hash >>= 2;
        steps_done++;

        switch (bit) {
          case (0):
            --end_.first;
            --end_.second;
            break;
          case (1):
            ++end_.first;
            --end_.second;
            break;
          case (2):
            --end_.first;
            ++end_.second;
            break;
          case (3):
            ++end_.first;
            ++end_.second;
            break;
        }

        if (end_.first < 0) {
          ++end_.first;
        } else if (end_.first > width_ - 1) {
          --end_.first;
        }
        if (end_.second < 0) {
          ++end_.second;
        } else if (end_.second > height_ - 1) {
          --end_.second;
        }

        vec_[end_.second][end_.first]++;
      }
    }
  }

 public:
  DrunkenBishop(int height, int width, std::string str)
      : height_(height),
        width_(width),
        vec_(height_, std::vector<int>(width, 0)),
        str_(str) {
          start_.first = width_ / 2;
          start_.second = height_ / 2;
          end_ = start_;
        }

  void Print(void) {
    Process();
    const std::string symbols = " .o+=*BOX@%&#/^";
    PrintSymLine();
    for (int y = 0; y < height_; ++y) {
      std::cout << '|';
      for (int x = 0; x < width_; ++x) {
        if (x == start_.first && y == start_.second)
          std::cout << "S";
        else if (x == end_.first && y == end_.second)
          std::cout << "E";
        else {
          int len = symbols.length() - 1;
          char sym = std::min(vec_[y][x], len);
          std::cout << symbols[sym];
        }
      }
      std::cout << '|' << std::endl;
    }
    PrintSymLine();
  }
};

int main(void) {
  int h = 0;
  int w = 0;
  std::cout << "Enter the height & width:\n";
  std::cin >> h >> w;

  std::cout << "Enter your string:\n";
  std::string str;
  std::getline(std::cin >> std::ws, str);

  DrunkenBishop bishop(h, w, str);

  bishop.Print();

  return 0;
}
