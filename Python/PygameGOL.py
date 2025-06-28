from GOL import createEmptyGrid, CheckGrid
import pygame
import sys
GRIDWIDTH = 100
GRIDHEIGHT = 100
WINDOWWIDTH = 800
WINDOWHEIGHT = 800
ONCOLOR = (255, 255, 255)
OFFCOLOR = (0, 0, 0)
maingrid = createEmptyGrid(GRIDWIDTH, GRIDHEIGHT)
maingrid[1][2] = True
maingrid[2][3] = True
maingrid[3][1] = True
maingrid[3][2] = True
maingrid[3][3] = True
pygame.init()
def PGRenderGrid(grid, windowheight, windowwidth, offcolor, oncolor):
    blockwidth = windowwidth / len(grid) #height and width of one block are defined
    blockheight = windowheight / len(grid[0])
    #Draw the grid
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j]:
                pygame.draw.rect(screen, oncolor, (i*blockwidth, j*blockheight, blockwidth, blockheight))
            else:
                pygame.draw.rect(screen, offcolor, (i*blockwidth, j*blockheight, blockwidth, blockheight))

def HandleClick(grid, windowheight, windowwidth, x, y):
    #Identify which tile was clicked.
    blockwidth = windowwidth / len(grid) #height and width of one block are defined
    blockheight = windowheight / len(grid[0])
    clickedblockX = int(x // blockwidth)
    clickedblockY = int(y // blockheight)
    print(clickedblockX, " ", clickedblockY)
    #Toggle this tile
    grid[clickedblockX][clickedblockY] = not grid[clickedblockX][clickedblockY]
    return grid

screen = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
pygame.display.set_caption("Conway's Game Of Life")

clock = pygame.time.Clock()

running = True
paused = False
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            pos = pygame.mouse.get_pos()
            maingrid = HandleClick(maingrid, WINDOWHEIGHT, WINDOWWIDTH, pos[0], pos[1])
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE: #Toggle the pause
                paused = not paused
                #print("Pause!")

    # Game logic updates here
    if not paused:
        maingrid = CheckGrid(maingrid) #Update the grid if it's not paused
    screen.fill((0, 0, 0))  # Clear screen with black

    # Drawing code here
    PGRenderGrid(maingrid, WINDOWHEIGHT, WINDOWHEIGHT, OFFCOLOR, ONCOLOR)

    pygame.display.flip()  # Update the display

    clock.tick(10)  # Limit to 60 FPS

pygame.quit()
sys.exit()