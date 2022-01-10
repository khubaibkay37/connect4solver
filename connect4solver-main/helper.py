def valid_xy(x,y):
        return x >= 0 and x < 7 and y >= 0 and y < 6 
def is_winning_move(col,height,current_player,board):
    """
    Returns if the move is a winning move or not.

    Args:
        col [int]: column of the move 0-indexed
        height [list]: list of heights of each column
        current_player [string]: person doing the move
        board [nested list]: Current state of the board

    Returns:
        [type]: [description]
    """    ''''''
    num_elements_in_col = height[col]
    current_player = current_player
    if (num_elements_in_col >= 3 and board[col][num_elements_in_col - 1] == current_player and board[col][num_elements_in_col - 2] == current_player and board[col][num_elements_in_col - 3] == current_player):
        return True
    for axis in range(-1,2,1):
        in_player_flavor = 0 
        for direction in range(-1,2,2):
            x = col + direction
            y = height[col] + (axis * direction)
            while x>=0 and valid_xy(x,y) and board[x][y] == current_player:
                x+=direction
                y+=direction * axis
                in_player_flavor+=1
        if in_player_flavor >=3:
            return True
    return False