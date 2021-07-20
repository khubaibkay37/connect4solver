#pragma once
class Position
{
public:
    static const int WIDTH = 7;  // Width of the board
    static const int HEIGHT = 6; // Height of the board
private:
    int board[WIDTH][HEIGHT];
    int height[WIDTH];
    unsigned int moves;

public:
    Position();
    bool canPlay(int col) const;
    void play(int col);

    unsigned int play(const char *seq);
    bool valid_xy(int x, int y) const;
    bool isWinningMove(int col) const;
    void undo(int col);
    unsigned int nbMoves() const;
    void printState();
    ~Position();
};
