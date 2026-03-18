#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define WIDTH 100
#define HEIGHT 100
int initemptygrid(bool grid[HEIGHT][WIDTH]) {
    for (int i=0;i<HEIGHT;i++) { //init grid
        for (int j=0;j<WIDTH;j++) {
            grid[i][j] = false;
        }
    }
}
int togglesquare(bool grid[HEIGHT][WIDTH], int X, int Y) {
    if (X<WIDTH && Y<HEIGHT && X>=0 && Y>=0) {
        grid[Y][X] = !grid[Y][X];
        return 1;
    }
    return -1;
}
void randomizegrid(bool grid[HEIGHT][WIDTH]) {
    for (int i=0;i<HEIGHT;i++) {
        for (int j=0;j<WIDTH;j++) {
            if (rand()%2==0) {
                togglesquare(grid, j, i);
            }
        }
    }
}
void updategrid(bool grid[HEIGHT][WIDTH]) {
    bool retgrid[HEIGHT][WIDTH];
    for (int i=0;i<HEIGHT;i++) {
        for (int j=0;j<WIDTH;j++) {
            int neighborcoords[8][2] = {
                {i-1, j-1}, {i-1,j},{i-1,j+1},
                {i, j-1}, {i,j+1},
                {i+1, j-1}, {i+1,j},{i+1,j+1}
            };
            int liveneighborcount = 0;
            for (int P=0;P<8;P++) {
                int ny = (neighborcoords[P][0]+HEIGHT)%HEIGHT; int nx = (neighborcoords[P][1]+WIDTH)%WIDTH;
                if (grid[ny][nx] == true) {
                    liveneighborcount++;
                }
            }
            if (liveneighborcount < 2 || liveneighborcount > 3) {
                retgrid[i][j] = false;
            } else if (liveneighborcount == 2) {
                retgrid[i][j] = grid[i][j];
            } else if (liveneighborcount == 3) {
                retgrid[i][j] = true;
            }
        }
    }
    memcpy(grid, retgrid, sizeof retgrid); 
}
int main(void) {
    const int screenWidth = floor(1200/WIDTH)*WIDTH;
    const int screenHeight = floor(1200/HEIGHT)*HEIGHT;
    const int sqWidth = floor(screenWidth/WIDTH);
    const int sqHeight = floor(screenHeight/HEIGHT);
    static bool grid[HEIGHT][WIDTH];
    initemptygrid(grid);
    randomizegrid(grid);
    InitWindow(screenWidth, screenHeight, "Conway's Game Of Life");
    bool paused = false;
    int gencount = 0;
    float camstepunzoomed = screenWidth/20;
    float camstep = camstepunzoomed;
    float camx = 0; float camy = 0;
    Camera2D camera = { 0 };
        camera.offset = (Vector2){ 0, 0 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    SetTargetFPS(20);   
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_SPACE))
        {
            paused = !paused;
            if (paused) {printf("Paused! Gencount: %d \n", gencount);}
        }
        if (IsKeyPressed(KEY_R))
        {
            randomizegrid(grid);
            gencount = 0;
            printf("Randomized! Gencount: %d \n", gencount);
        }
        if (IsKeyPressed(KEY_C)) {
            initemptygrid(grid);
            gencount = 0;
            paused = true;
            printf("Cleared the grid and paused! Gencount: %d \n", gencount);
        }
        camstep = camstepunzoomed/camera.zoom;
        if (IsKeyDown(KEY_LEFT)) {
            camx -= camstep;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            camx += camstep;
        }
        if (IsKeyDown(KEY_UP)) {
            camy -= camstep;
        }
        if (IsKeyDown(KEY_DOWN)) {
            camy += camstep;
        }
        if (camera.zoom > 3.0) {
            camera.zoom = 3.0f;
        }
        if (camera.zoom < 1.0) {
            camera.zoom = 1.0f;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            int gridX = floor(mouseWorldPos.x/sqWidth); 
            int gridY = floor(mouseWorldPos.y/sqHeight);
            togglesquare(grid, gridX, gridY);
        }
        if (camx<0) {camx=0;} if (camy<0) {camy=0;} 
        if (camx+screenWidth/camera.zoom > screenWidth) {camx = screenWidth*(1-1/camera.zoom);} 
        if (camy+screenHeight/camera.zoom > screenWidth) {camy = screenHeight*(1-1/camera.zoom);}
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (!paused) {
            updategrid(grid);
            gencount++;
        }
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
        camera.target = (Vector2){ camx, camy };

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            BeginMode2D(camera);
                ClearBackground(BLACK);
                //Draw loop:
                for (int i=0;i<HEIGHT;i++) {
                    for (int j=0;j<WIDTH;j++) {
                        if (grid[i][j]) {
                            struct sq {
                                int x;
                                int y;
                            };
                            struct sq currsq;
                            currsq.x=j*sqWidth; currsq.y=i*sqWidth;
                            DrawRectangle(currsq.x, currsq.y, sqHeight, sqWidth, WHITE);
                        }
                    }
                }
            EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();
    return 0;
}