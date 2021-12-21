#include "Life.h"
#include "random"
#include <algorithm>


Life::Life(int width, int heigth) : _width(width), _height(heigth), cell_states(std::vector<bool>(width * heigth)) {
    if (width < 3 && heigth < 3) {
        throw LifeException("Wrong size");
    };
}

int Life::GetWidth() const {
    return _width;
}

int Life::GetHeight() const {
    return _height;
}

const std::vector<bool> &Life::GetCellStates() const {
    return cell_states;
}

void Life::SetCellStates(bool state, int index) {
    cell_states[index] = state;
}

void Life::SetStateAlive(int x, int y) {
    using namespace std;
    if (IsValid(x, y)) {
        cell_states[(y * _width) + x] = true;
    } else {
        throw LifeException("Wrong position (" + to_string(x) + ", " + to_string(y) + ")");
    }
}

bool Life::IsValid(int x, int y) const {
    return x >= 0 && y >= 0 && x < _width && y < _height;
}

void Life::SetStateDead(int x, int y) {
    using namespace std;
    if (IsValid(x, y)) {
        cell_states[(y * _width) + x] = false;
    } else {
        throw LifeException("Wrong position (" + to_string(x) + ", " + to_string(y) + ")");
    }
}

bool Life::GetStateCell(int x, int y) {
    using namespace std;

    if (x == -1) {
        x = x + _width;
    }
    if (y == -1) {
        y = y + _height;
    }
    if (x == _width) {
        x = 0;
    }
    if (y == _height) {
        y = 0;
    }
    if (IsValid(x, y)) {
        return cell_states[(y * _width) + x];
    } else {
        throw LifeException("Wrong pos (" + to_string(x) + ", " + to_string(y) + ")");
    }
}

std::vector<bool> Life::GetNearStates(int x, int y) {
    if (IsValid(x, y)) {
        return {
                GetStateCell(x - 1, y - 1), GetStateCell(x, y - 1), GetStateCell(x + 1, y - 1),
                GetStateCell(x - 1, y), GetStateCell(x + 1, y), GetStateCell(x - 1, y + 1),
                GetStateCell(x, y + 1), GetStateCell(x + 1, y + 1)};
    } else {
        throw LifeException("Wrong pos (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
}


void Life::Mutate() {
    Life other(this->_width, this->_height);
    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            if (!GetStateCell(x, y)) {
                if (GetLiveCountNearCell(x, y) == 3) {
                    other.SetStateAlive(x, y);
                } else {
                    continue;
                }
            } else {
                auto count_live = GetLiveCountNearCell(x, y);
                if (count_live == 3 || count_live == 2) {
                    other.SetStateAlive(x, y);
                } else {
                    other.SetStateDead(x, y);
                }
            }
        }
    }
    std::swap(*this, other);
}

int Life::GetLiveCountNearCell(int x, int y) {
    auto near_cells = GetNearStates(x, y);
    return std::count(near_cells.begin(), near_cells.end(), true);
}

void Life::ClearStates() {
    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            SetStateDead(x, y);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Life &life) {
using namespace std;
for (size_t y = 0; y < life._height; ++y) {
std::string buffer = "!";
size_t counter = 0;
for (size_t x = 0; x < life._width; ++x) {
std::string item = (life.cell_states[(y * life._width) + x]) ? "o" : "x";
++counter;
if (counter == life._width) {
buffer += item;
} else {
buffer += item + " ";
}
}
buffer += "!";
os << buffer + "\n";
}
return os;
}

std::string Life::ToString() {
    using namespace std;
    string result;
    for (size_t y = 0; y < _height; ++y) {
        std::string buffer = "!";
        size_t counter = 0;
        for (size_t x = 0; x < _width; ++x) {
            std::string item = (cell_states[(y * _width) + x]) ? "o" : "x";
            ++counter;
            if (counter == _width) {
                buffer += item;
            } else {
                buffer += item + " ";
            }
        }
        buffer += "!";
        result += buffer + "\n";
    }
    return result;
}


void Life::FillRandomStates() {
    int i = 0;
    while (i <= GetCellStates().size()) {
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution<> dist(0, 1);
        dist(mt) ? SetCellStates(false, i) : SetCellStates(true, i);
        ++i;
    }
}