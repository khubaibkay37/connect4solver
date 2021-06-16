#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    Position(/* args */) : board{0}, height{0}, moves{0} {

                                                };
    bool canPlay(int col) const
    {
        return height[col] < HEIGHT;
    }

    bool play(int col)
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
    void printState()
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

    unsigned int play(char *seq)
    {
        unsigned int i = 0;
        for (unsigned int i = 0; seq[i] != '\0'; i++)
        {
            int col = seq[i] - '1';
            if (col < 0 || col >= WIDTH || !canPlay(col) || isWinningMove(col))
                return i; // invalid move
            play(col);
        }
        return i;
    }
    bool valid_xy(int x, int y) const
    {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }
    bool isWinningMove(int col) const
    {
        int current_player = 1 + moves % 2;
        int num_elements_in_col = height[col];
        if (num_elements_in_col > 3 && board[col][num_elements_in_col - 1] == current_player && board[col][num_elements_in_col - 2] == current_player && board[col][num_elements_in_col - 3] == current_player)
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
    unsigned int nbMoves() const
    {
        return moves;
    }

    ~Position()
    {
    }
};

int negamax(const Position &P)
{
    if (P.nbMoves() == Position::WIDTH * Position::HEIGHT) // check for draw game
        return 0;

    for (int x = 0; x < Position::WIDTH; x++) // check if current player can win next move
        if (P.canPlay(x) && P.isWinningMove(x))
            return (Position::WIDTH * Position::HEIGHT + 1 - P.nbMoves()) / 2;

    int bestScore = -Position::WIDTH * Position::HEIGHT; // init the best possible score with a lower bound of score.

    for (int x = 0; x < Position::WIDTH; x++) // compute the score of all possible next move and keep the best one
        if (P.canPlay(x))
        {
            Position P2(P);
            P2.play(x);               // It's opponent turn in P2 position after current player plays x column.
            int score = -negamax(P2); // If current player plays col x, his score will be the opposite of opponent's score after playing col x
            if (score > bestScore)
                bestScore = score; // keep track of best possible score so far.
        }

    return bestScore;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Format: .\\a.exe <filename>";
        return 1;
    }
    std::ifstream file;
    file.open(argv[1]);
    if (!file)
    {
        std::cout << "Bruh\n";
        return 1;
    }
    char a[43];
    int b;
    int i = 1;
    while (!file.eof())
    {
        file >> a >> b;
        // std::cout << "Board: " << a << ", "
        //           << "Best Move: " << b << std::endl;
        Position game;

        game.play(a);
        int score = negamax(game);
        if (score == b)
        {
            // std::cout << "Test " << i << " passed" << std::endl;
        }
        else
        {
            std::cout << "Test " << i << " failed, Actual: " << b << " , Predicted: " << score << std::endl;
        }
        i++;
    }
    // Postion game;
    // int move = 0;
    // bool state;
    // do
    // {
    //     std::cout << "Enter your move: ";
    //     std::cin >> move;
    //     state = game.play(move);
    //     game.printState();
    //     /* code */
    // } while (!state);

    // game.printState();
}