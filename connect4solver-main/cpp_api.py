import subprocess
import os

def get_score_of_position(position):
    """
    Returns the score of the position.
    We define a score for any non final position reflecting the outcome of
    the game for the player to play, considering that both players play
    perfectly and try to win as soon as possible or lose as late as
    possible. A position has:
    A positive score if the current player can win.
    1 if he wins with his last stone,
    2 if he wins with your second last stone and so on...
    A o score if the game will end by a draw game
    A negative score if the current player lose whatever he plays.
    -1 if his opponent wins with his last stone,
    -2 if his opponent wins with his second last stone and so on...
    Args:
    position [string]: Contains the moves that need to be done to get the game
    in the position we want to evaluate.
    Returns:
    score [int]: The score of the position we want to evaluate.
    """
    # TODO: Rename the filename to what you get when you do g++ *.cpp
    filename = "a.out"
    
    if not os.path.isfile(filename):
        raise Exception(filename + " does not exist")
    
    proc = subprocess.Popen(
        [f"./{filename}", "value", position], stdout = subprocess.PIPE)
    output = proc.stdout.read().decode('utf-8').strip()
    try:
        score = int(output)
        return score
    except:
        print(output)
        raise ValueError(
            "The program failed to evaluate the score of this position\n"
            + f"Output of the program is as follows: {output}")


def get_best_move(position):
    """
    Returns the best move possible for the player at the position.
    We define a score for any non final position reflecting the outcome of
    the game for the player to play, considering that both players play
    perfectly and try to win as soon as possible or lose as late as
    possible. A position has:
    A positive score if the current player can win.
    1 if he wins with his last stone,
    2 if he wins with your second last stone and so on...
    A o score if the game will end by a draw game
    A negative score if the current player lose whatever he plays.
    -1 if his opponent wins with his last stone,
    -2 if his opponent wins with his second last stone and so on...
    Args:
    position [string]: Contains the moves that need to be done to get the game
    in the position we want to evaluate.
    Returns:
    score [int]: The score of the position we want to evaluate.
    """


    # TODO: Rename the filename to what you get when you do g++ *.cpp
    filename = "a.out"
    if not os.path.isfile(filename):
        raise Exception(filename + " does not exist")
    
    proc = subprocess.Popen(
        [f"./{filename}", "best", position], stdout=subprocess.PIPE)
    output = proc.stdout.read().decode('utf-8').strip()
    try:
        best_move = int(output)
        return best_move
    except:
        print(output)
        raise ValueError(
            "The program failed to evaluate the best move at this position\n"
            + "This maybe because the position provided is invalid or the game is finished.\n"
            + f"Output of the program is as follows: {output}")
