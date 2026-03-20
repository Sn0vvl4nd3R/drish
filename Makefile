CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = drunken_bishop
SRC = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
