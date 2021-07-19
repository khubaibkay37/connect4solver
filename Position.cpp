#include "Position.hpp"
#include <iostream>

Position::Position(/* args */) : board{0}, height{0}, moves{0} {};

bool Position::canPlay(int col) const
{
    return height[col] < HEIGHT;
}

bool Position::play(int col)
{
    if (canPlay(col))
    {
        bool win = isWinningMove(col);
        board[col][height[col]] = 1 + moves % 2;
        moves++;
        height[col]++;
        return win;
        // std::cout << height[col] << std::endl;
    }
    else
    {
        exit(1);
    }
}

void Position::undo(int col) {
        height[col]--;
        board[col][height[col]] = 0;
        moves--;
    
}
void Position::printState()
{
    for (int j = HEIGHT - 1; j >= 0; j--)
    {
        for (int i = 0; i < WIDTH; i++)

        {
            if (board[i][j] == 0)
            {
                std::cout << "- ";
            }
            else
            {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}

unsigned int Position::play(const char *seq)
{
    unsigned int i = 0;
    for (i = 0; seq[i] != '\0'; i++)
    {
        int col = seq[i] - '1';
        if (col < 0 || col >= WIDTH || !canPlay(col))
        {

            std::cout << "Invalid thing: " << col+1 << std::endl;
            std::cout << seq << std::endl;
            return i; // invalid move
        }
        play(col);
    }
    return i;
}

bool Position::valid_xy(int x, int y) const
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Position::isWinningMove(int col) const
{
    int current_player = 1 + moves % 2;
    int num_elements_in_col = height[col];
    if (num_elements_in_col >= 3 && board[col][num_elements_in_col - 1] == current_player && board[col][num_elements_in_col - 2] == current_player && board[col][num_elements_in_col - 3] == current_player)
    {
        return true;
    }
    for (int axis = -1; axis <= 1; axis++)
    {
        int in_player_favor = 0;
        for (int direction = -1; direction <= 1; direction += 2)
        {
            for (int x = col + direction, y = height[col] + (axis * direction); x >= 0 && valid_xy(x, y) && board[x][y] == current_player; in_player_favor++)
            {
                x += direction;
                y += direction * axis;
            }
        }
        if (in_player_favor >= 3)
        {
            return true;
        }
    }
    return false;
}

unsigned int Position::nbMoves() const
{
    return moves;
}

Position::~Position(){};
