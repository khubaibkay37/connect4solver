#pragma once

#include <cstdint>
#include <string>
#include <iostream>
using namespace std;


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
    public: static uint64_t column_mask(int col);


    //static uint16_t maybeThisworks =  appleBottom(WIDTH, HEIGHT);
    //const static uint64_t bottom = appleBottom(WIDTH, HEIGHT);
    static uint64_t bottom;

    //const static uint64_t bottom = maybeThisworks;
    //const static uint64_t board_mask = bottom * ((1LL << HEIGHT) - 1);
    static uint64_t board_mask;

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

    //anticipating wiining move
    uint64_t possibleNnlosingMoves() const;
    uint64_t opponent_winning_position() const;
    uint64_t possible() const;
    static uint64_t compute_winning_position(uint64_t position, uint64_t mask);

    //hope this wrks
    static uint64_t appleBottom(int width, int height);

    //check if next winning move
    uint64_t winning_position() const;
    bool canWinNext() const;
    
    //move ordering
    int moveScore(uint64_t move) const;   
    static unsigned int popcount(uint64_t m);
};
