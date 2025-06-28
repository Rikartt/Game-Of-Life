import os
import copy
import sys
import time
#import pygame

#SCREEN_WIDTH = 500
#SCREEN_HEIGHT = 500

def createEmptyGrid(width, height):
    grid = [[False for x in range(width)] for x in range(height)]
    return grid
print(createEmptyGrid(10, 10))
def CheckGrid(grid):
    retgrid = copy.deepcopy(grid)
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            liveneighborcount = 0
            neighbors = [[i+1, j+1], [i+1, j], [i+1, j-1],
                         [i, j+1], [i, j-1],
                         [i-1, j+1], [i-1, j], [i-1, j-1]]
            for x in neighbors:
                if 0 <= x[0] <= len(grid)-1 and len(grid[0])-1 >= x[1] >= 0:
                    if grid[x[0]][x[1]]:
                        liveneighborcount += 1
            #print("Live neighbor count", liveneighborcount)
            if liveneighborcount < 2:
                retgrid[i][j] = False
                #print("cell died or had no neighbors")
            elif liveneighborcount == 2:
                retgrid[i][j] = grid[i][j]
                #print("cell stayed alive")
            elif liveneighborcount > 3:
                retgrid[i][j] = False
            elif liveneighborcount == 3:
                retgrid[i][j] = True
            else:
                retgrid[i][j] = grid[i][j]
    return retgrid

def RenderGrid(grid):
    retgrid = copy.deepcopy(grid) #grid thats filled with X's where a live cell is and O's where a dead cell is
    for x in range(len(grid)):
        for y in range(len(grid[x])):
            if grid[x][y] == True:
                retgrid[x][y] = "X"
            else:
                retgrid[x][y] = "O"
    return retgrid

def TextAnimateFrame(grid):
    # Clear screen (works on most terminals)
    [sys.stdout.write(str(" ".join(x)) + '\n') for x in RenderGrid(grid)]
    grid = CheckGrid(grid)
    time.sleep(0.5)
    sys.stdout.flush()
    os.system('cls' if os.name == 'nt' else 'clear')
    return grid

def PygameAnimateFrame(grid):
    pass

maingrid = createEmptyGrid(20, 20)

maingrid[1][2] = True
maingrid[2][3] = True
maingrid[3][1] = True
maingrid[3][2] = True
maingrid[3][3] = True
#pygame.init()
for i in range(100):
    sys.stdout.write("gen: " + str(i) + '\n')
    maingrid = TextAnimateFrame(maingrid)