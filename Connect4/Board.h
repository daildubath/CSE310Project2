#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
private:
    std::vector<std::vector<char>> grid;
    int cols = 7;
    int rows = 7;

public:
    Board(); // Constructor
    void display() const;
    bool isColumnFull(int x) const;
    int dropToken(int x, char token);
    bool checkWin(int last_x, int last_y, char token) const;
    //Added, and hopeful logic
    bool isWinningMove(int col, char token) const;
};

#endif
