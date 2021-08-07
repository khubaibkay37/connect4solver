
#include "Position.hpp"
#include <iostream>

// Default constructor for Position
Position::Position() : current_position{0}, mask{0}, moves{0} {}

// Sees whether it is possible to insert in the given column or not
// @param column: the column to check
// @return: true if it is possible to insert in the given column, false otherwise
bool Position::canPlay(int col) const
{
    return (mask & top_mask(col)) == 0;
}

// Play a piece in the given column
// @param column: the column to play in
void Position::play(int col)
{
    current_position ^= mask;
    mask |= mask + bottom_mask(col);
    moves++;
    // if (canPlay(col))
    // {
    //     board[col][height[col]] = 1 + moves % 2;
    //     moves++;
    //     height[col]++;
    // }
    // else
    // {
    //     std::cout << "Invalid move" << std::endl;
    //     exit(1);
    // }
}

// // Removes the piece in the given column
// // @param column: the column to remove from
// void Position::undo(int col)
// {
//     // height[col]--;
//     // board[col][height[col]] = 0;
//     // moves--;
// }

// // Prints the current state of the board
// void Position::printState()
// {
//     for (int j = HEIGHT - 1; j >= 0; j--)
//     {
//         for (int i = 0; i < WIDTH; i++)

//         {
//             if (board[i][j] == 0)
//             {
//                 std::cout << "- ";
//             }
//             else
//             {
//                 std::cout << board[i][j] << " ";
//             }
//         }
//         std::cout << "\n";
//     }
// }
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
/**    
       * @return a compact representation of a position on WIDTH*(HEIGHT+1) bits.
       */
uint64_t Position::key() const
{
    return current_position + mask;
}

// Checks whether a position is on the board or not
// @param x: the x coordinate to check. 0-indexed
// @param y: the y coordinate to check. 0-indexed
// @return: true if the position is on the board, false otherwise
bool Position::valid_xy(int x, int y) const
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Position::alignment(uint64_t pos) {
        // horizontal 
        uint64_t m = pos & (pos >> (HEIGHT+1));
        if(m & (m >> (2*(HEIGHT+1)))) return true;

        // diagonal 1
        m = pos & (pos >> HEIGHT);
        if(m & (m >> (2*HEIGHT))) return true;

        // diagonal 2 
        m = pos & (pos >> (HEIGHT+2));
        if(m & (m >> (2*(HEIGHT+2)))) return true;

        // vertical;
        m = pos & (pos >> 1);
        if(m & (m >> 2)) return true;

        return false;
      }

// Returns whether the given move is a winning move or not
// @param col: the column to check
// @return: true if the move is a winning move, false otherwise
bool Position::isWinningMove(int col) const
{

        uint64_t pos = current_position; 
        pos |= (mask + bottom_mask(col)) & column_mask(col);
        return alignment(pos);
}

// Returns number of moves played yet
// @return: number of moves played
int Position::nbMoves() const
{
    return moves;
}

uint64_t Position::top_mask(int col)
{
    return (UINT64_C(1) << (HEIGHT - 1)) << col * (HEIGHT + 1);
}

// return a bitmask containg a single 1 corresponding to the bottom cell of a given column
uint64_t Position::bottom_mask(int col)
{
    return UINT64_C(1) << col * (HEIGHT + 1);
}

// return a bitmask 1 on all the cells of a given column
uint64_t Position::column_mask(int col)
{
    return ((UINT64_C(1) << HEIGHT) - 1) << col * (HEIGHT + 1);
}
// Destructor
Position::~Position(){};
