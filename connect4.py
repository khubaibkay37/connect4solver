import pygame
from test import get_cpp_opinion
# If you want to start the game off from somewhere
starting = "555422433323451176441511577777"

# Each sublist represents a column. There are 7 columns in total of size 6 each. 0th index represent bottom of the column
state = [["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""],
          ["","","","","",""]]
# How many elements are in each column
height = [0] * 7
# your voice is lagging
def doMove(movestring,state,height,col = -1,type = "one"):
    global current,currentmoves
    # Update history of our current moves
    currentmoves+= f"{movestring}"
    for move in movestring:
        # If we are doing a lot of moves then we need to read the current move just need to make it 0 indexed (-1)
        if type != "one":
            col = int(move) - 1
        else:
            col -=1
        if height[col] < 6:
            row = height[col]
            state[col][row] = current
            current = "X" if current == "O" else "O"
            height[col] += 1
currentmoves = ""
current = "X"
doMove("75662564375666511575212332122171447733",state,height,type="")
print(state)
pygame.init()
screen = pygame.display.set_mode((700, 700))
done = False
mode = ""
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_f:
                print(currentmoves)
                if current == "X":
                    maximize = -50
                    bestmove = -1
                    for i in range(7):
                        if height[i]<6:
                            val = get_cpp_opinion(currentmoves+f"{i+1}")
                            if maximize < val:
                                maximize = val
                                bestmove = i+1
                else:
                    minimize = 50
                    bestmove = -1
                    for i in range(7):
                        if height[i]<6:
                            val = get_cpp_opinion(currentmoves+f"{i+1}")
                            if minimize > val:
                                minimize = val
                                bestmove = i+1
                print(bestmove)
            mapping = {pygame.K_1 : 1, pygame.K_2 : 2, pygame.K_3 : 3, pygame.K_4 : 4, pygame.K_5 : 5, pygame.K_6 : 6, pygame.K_7 : 7}
            if event.key in mapping:
                col = mapping[event.key] 
                doMove(f"{col}",state,height,col)
                    # if height[col] < 6:
                    #     row = -height[col]-1
                    #     state[row][col] = current
                    #     current = "X" if current == "O" else "O"
                    #     height[col] += 1

    grey = (155, 155, 155)
    Red = (255,0,0) 
    Blue = (0,0,255)
    empty = (50,50,50)
    white = (255,255,255)
    color = empty
    x = 30
    y = 100
    # Draw stuff 

    for col_index,col in enumerate(state):
        for row_ind,value in enumerate(col):
            pygame.draw.rect(screen, grey, [x+(80*col_index), y+(80*(len(col)-1-row_ind)), 70, 70]) 
            if value == "X":
                color = Red
            elif value == "O":
                color = Blue
            pygame.draw.ellipse(screen, color, [x+(80*col_index), y+(80*(len(col)-1-row_ind)), 70, 70]) 
            color = empty
    pygame.display.flip()