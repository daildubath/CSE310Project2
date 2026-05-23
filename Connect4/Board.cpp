#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>

Board::Board() {
    grid = std::vector<std::vector<char>>(cols, std::vector<char>(rows, ' '));
}

void Board::display() const {
    // \x1B[2J clears the entire screen
    // \x1B[H moves the cursor back to the top left (Home)
    std::cout << "\x1B[2J\x1B[H";
// #ifdef _WIN32
//     std::system("cls");
// #else
//     std::system("clear");
// #endif

    std::cout << "-----------------------------\n";
    for (int y = 0; y < rows; ++y) {
        std::cout << "| ";
        for (int x = 0; x < cols; ++x) {
            std::cout << grid[x][y] << " | ";
        }
        std::cout << "\n-----------------------------\n";
    }
    std::cout << "||1   2   3   4   5   6   7||\n";
    std::cout << "^^                         ^^\n";

    // Force the terminal to draw the board immediately before the next frame
    std::cout << std::flush;
}

bool Board::isColumnFull(int x) const {
    return grid[x][0] != ' ';
}

int Board::dropToken(int x, char token) {
    if (isColumnFull(x)) return -1;

    int final_y = 0;
    for (int y = 0; y < rows; ++y) {
        if (grid[x][y] == ' ') {
            grid[x][y] = token;
            display();
            grid[x][y] = ' ';
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (y == rows - 1 || grid[x][y + 1] != ' ') {
            grid[x][y] = token;
            final_y = y;
            break;
        }
    }
    display();
    return final_y;
}

bool Board::checkWin(int last_x, int last_y, char token) const {
    // Adding 'const' fixes the inner-scope warning!
    static constexpr int dx[] = {1, 0, 1, 1};
    static constexpr int dy[] = {0, 1, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int count = 1;
        for (int step = 1; step < 4; ++step) {
            int nx = last_x + dx[i] * step;
            int ny = last_y + dy[i] * step;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[nx][ny] == token) count++;
            else break;
        }
        for (int step = 1; step < 4; ++step) {
            int nx = last_x - dx[i] * step;
            int ny = last_y - dy[i] * step;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[nx][ny] == token) count++;
            else break;
        }
        if (count >= 4) return true;
    }
    return false;
}
// Added function for hopeful competition
bool Board::isWinningMove(int col, char token) const
{
    // If column is full, it obviously can't be a winning move
    if (isColumnFull(col)) return false;

    // 1. Find the hypothetical row it WOULD land on
    int target_y = 0;
    for (int y = 0; y < rows; ++y)
    {
        if (y == rows - 1 || grid[col][y + 1] != ' ')
        {
            target_y = y;
            break;
        }
    }

    // 2. Cast rays from that hypothetical spot
    static constexpr int dx[] = {1, 0, 1, 1};
    static constexpr int dy[] = {0, 1, 1, -1};

    for (int i = 0; i < 4; ++i)
    {
        int count = 1;
        for (int step = 1; step < 4; ++step)
        {
            int nx = col + dx[i] * step;
            int ny = target_y + dy[i] * step;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[nx][ny] == token) count++;
            else break;
        }
        for (int step = 1; step < 4; ++step)
        {
            int nx = col - dx[i] * step;
            int ny = target_y - dy[i] * step;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[nx][ny] == token) count++;
            else break;
        }
        if (count >= 4) return true;
    }
    return false;
}
