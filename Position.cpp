#include "Position.hpp"
#include <iostream>

// Default constructor for Position
Position::Position() : board{0}, height{0}, moves{0}
{
}

// Sees whether it is possible to insert in the given column or not
// @param column: the column to check
// @return: true if it is possible to insert in the given column, false otherwise
bool Position::canPlay(int col) const
{
    return height[col] < HEIGHT;
}

// Play a piece in the given column
// @param column: the column to play in
void Position::play(int col)
{
    if (canPlay(col))
    {
        board[col][height[col]] = 1 + moves % 2;
        moves++;
        height[col]++;
    }
    else
    {
        std::cout << "Invalid move" << std::endl;
        exit(1);
    }
}

// Removes the piece in the given column
// @param column: the column to remove from
void Position::undo(int col)
{
    height[col]--;
    board[col][height[col]] = 0;
    moves--;
}

// Prints the current state of the board
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
// Plays a particular sequence of moves
// @param moves: the sequence of moves to play
// @return: number of moves played.
unsigned int Position::play(const char *seq)
{
    unsigned int i = 0;
    for (i = 0; seq[i] != '\0'; i++)
    {

        int col = seq[i] - '1';
        // if the move is invalid
        if (col < 0 || col >= WIDTH || !canPlay(col))
        {

            std::cout << "Invalid thing: " << col + 1 << std::endl;
            std::cout << seq << std::endl;
            return i;
        }
        if (isWinningMove(col))
        {
            std::cout << "Game over\n";
            exit(1);
        }
        play(col);
    }
    return i;
}
// Checks whether a position is on the board or not
// @param x: the x coordinate to check. 0-indexed
// @param y: the y coordinate to check. 0-indexed
// @return: true if the position is on the board, false otherwise
bool Position::valid_xy(int x, int y) const
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// Returns whether the given move is a winning move or not
// @param col: the column to check
// @return: true if the move is a winning move, false otherwise
bool Position::isWinningMove(int col) const
{

    int current_player = 1 + moves % 2;
    int num_elements_in_col = height[col];

    // See if we win vertically
    if (num_elements_in_col >= 3 && board[col][num_elements_in_col - 1] == current_player && board[col][num_elements_in_col - 2] == current_player && board[col][num_elements_in_col - 3] == current_player)
    {
        return true;
    }
    // See if we win left diagonal: -1, horizontally: 0, right diagonal: 1
    for (int axis = -1; axis <= 1; axis++)
    {
        
        int pieces_in_favor_of_player = 0;
        for (int direction = -1; direction <= 1; direction += 2)
        {
            // While we are in the bounds of the board and are seeing a piece of the current player
            for (int x = col + direction, y = height[col] + (axis * direction); x >= 0 && valid_xy(x, y) && board[x][y] == current_player; pieces_in_favor_of_player++)
            {
                x += direction;
                y += direction * axis;
            }
        }
        if (pieces_in_favor_of_player >= 3)
        {
            return true;
        }
    }
    return false;
}

// Returns number of moves played yet
// @return: number of moves played
unsigned int Position::nbMoves() const
{
    return moves;
}
// Destructor
Position::~Position(){};
