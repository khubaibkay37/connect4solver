#pragma once

#include <cstdint>
class Position
{
public:
    static const int WIDTH = 7;  // Width of the board
    static const int HEIGHT = 6; // Height of the board
    static const int MIN_SCORE = -(WIDTH * HEIGHT) / 2 + 3;
    static const int MAX_SCORE = (WIDTH * HEIGHT + 1) / 2 - 3;

private:
    // int board[WIDTH][HEIGHT];
    // int height[WIDTH];
    int moves;
    uint64_t current_position;
    uint64_t mask;
    static bool alignment(uint64_t pos);
    static uint64_t top_mask(int col);
    static uint64_t bottom_mask(int col);
    static uint64_t column_mask(int col);

public:
    Position();
    bool canPlay(int col) const;
    void play(int col);
    unsigned int play(const char *seq);
    bool valid_xy(int x, int y) const;
    bool isWinningMove(int col) const;
    void undo(int col);
    uint64_t key() const;
    int nbMoves() const;
    void printState();
    ~Position();
};
