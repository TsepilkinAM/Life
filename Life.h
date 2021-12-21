#pragma once

#include <vector>
#include <string>
#include <stdexcept>

class LifeException : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};

class Life {
public:
    Life(int weight, int height);

    const std::vector<bool> &GetCellStates() const;

    void SetCellStates(bool state, int index);

    std::string ToString();

    friend std::ostream &operator<<(std::ostream &os, const Life &life);

    void SetStateAlive(int x, int y);

    void SetStateDead(int x, int y);

    void ClearStates();

    bool GetStateCell(int x, int y);

    int GetLiveCountNearCell(int x, int y);

    void FillRandomStates();

    void Mutate();

    int GetWidth() const;

    int GetHeight() const;

private:
    std::vector<bool> GetNearStates(int x, int y);
    bool IsValid(int x, int y) const;
    int _width;
    int _height;
    std::vector<bool> cell_states;
};