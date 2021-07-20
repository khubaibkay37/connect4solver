from helper import is_winning_move
import pygame
from cpp_api import get_best_move,get_score_of_position
# from helper import is_winning_move


def doMove(state,height,col):
    """
    Function does the move of inserting in a particular column

    Args:
        state [nested list]: Nested list representing current board position
        height [list]: A list of integers representing the number of elements in each column
        col [int] : Column to insert into
    """    
    global current_player,current_actions
    
    # Add the current action to the list of actions and make col 0 indexed
    current_actions+= f"{col}"
    col -=1

    if height[col] < 6:
        row = height[col]
        state[col][row] = current_player
        current_player = "X" if current_player == "O" else "O"
        height[col] += 1
    else:
        print("Column is full, move is invalid")

def start_from_position(position,state,height):
    """
    Updates state and height to the one at the 
    specified position of the game

    Args:
        position [string]: position that we want the board to be at
        state [nested list]: Nested list representing current board position
        height [list]: A list of integers representing the number of elements in each column
    """    
    for move in position:
        doMove(state,height,int(move))



# -------Initialization Start--------------------

# Initialize CONSTANTS 

GRAY = (155, 155, 155)
RED = (255,0,0) 
BLUE = (0,0,255)
EMPTY = (50,50,50)
WHITE = (255,255,255)
X = 30
Y = 100


# Initialize parameters

state = [["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""]]
height = [0] * 7
current_actions = ""
current_player = "X"

starting_position = "2252576253462244111563365343671351441"

start_from_position(starting_position,state,height)
    
# -------Initialization End----------------------

# --------------- Pygame init start ---------------
pygame.init()
screen = pygame.display.set_mode((700, 700))
game_over = False

# --------------- Pygame init end ---------------


# --------------- Pygame loop start ---------------
while not game_over:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_over = True
        
        # Some key is being pressed
        if event.type == pygame.KEYDOWN:
            """
            F: Give the best possible move suggestion
            1-7: Insert in column 1-7 depending on the key pressed
            """
            if event.key == pygame.K_f:
                best_move = get_best_move(current_actions)
                if is_winning_move(best_move-1,height,current_player,state):
                    score_of_best_move = "Doesn't matter you win"
                else:
                    score_of_best_move =- get_score_of_position(current_actions+f"{best_move}")
                print(f"Best Move is {best_move} with score {score_of_best_move}")
            
            # Insert in column 1-7 depending on the key pressed
            mapping = {pygame.K_1 : 1, pygame.K_2 : 2, pygame.K_3 : 3, pygame.K_4 : 4, pygame.K_5 : 5, pygame.K_6 : 6, pygame.K_7 : 7}
            if event.key in mapping:
                col = mapping[event.key] 
                if height[col-1] < 6:
                    doMove(state,height,col)
                else:
                    print("Invalid move")   



    color = EMPTY

    # ------ Draw the board Start ------

    for col_index,col in enumerate(state):
        for row_ind,value in enumerate(col):
            pygame.draw.rect(screen, GRAY, [X+(80*col_index), Y+(80*(len(col)-1-row_ind)), 70, 70]) 
            if value == "X":
                color = RED
            elif value == "O":
                color = BLUE
            pygame.draw.ellipse(screen, color, [X+(80*col_index), Y+(80*(len(col)-1-row_ind)), 70, 70]) 
            color = EMPTY
    pygame.display.flip()

    # ------ Draw the board End ------
# --------------- Pygame loop end ---------------