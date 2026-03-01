#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10
#define WIDTH 30
#define HEIGHT 30
int splitstring(char *string, int out[][2], int max_pairs) {
    char *tok = strtok(string, " ");
    char *output[100];
    int count = 0;
    while (tok && count < max_pairs * 2) {
        if (count%2==0) {out[count/2][0] = atoi(tok);}
        else {out[count/2][1] = atoi(tok);}
        count++;
        tok = strtok(NULL," ");
    }
    return count / 2;
}
int printgrid(bool grid[HEIGHT][WIDTH]) {
    for (int i=0;i<HEIGHT;i++) { //print grid
        for (int j=0;j<WIDTH;j++) {
            if (grid[i][j] == 1) {printf("X ");}
            if (grid[i][j] == 0) {printf("  ");}
        }
        printf("\n");
    }
}
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
                togglesquare(grid, i, j);
            }
        }
    }
}
void handleinput(bool grid[HEIGHT][WIDTH]) {
    printf("\"X Y\" to toggle square at location X Y and leave empty to pass:");
    char input[10000];
    int pairs;
    int formattedinput[100][2];
    fgets(input, sizeof input, stdin);
    //if (input==NULL) {return -1;}
    //if (input[0]=='\n') {return 0;} //if input is just enter
    if (input[0]=='\n') {return;}
    sscanf(input, "");
    pairs = splitstring(input, formattedinput, 100);
    if (pairs>0) {printf("%d pairs toggled: \n",pairs);}
    for (int i=0;i<pairs;i++) {
        int X=formattedinput[i][0], Y=formattedinput[i][1];
        //if (sscanf(input, "%d %d", &X, &Y) != 2) {
        //    printf("Invalid input. Please enter two integers like: 3 5\n");
        //    return -1;
        //}
        X %= WIDTH; Y %= HEIGHT;
        if (togglesquare(grid, X, Y) == 1) {
            printf("    Square (%d, %d) toggled.\n", X, Y);
        } else {
            printf("    Square (%d, %d) not toggled. Possibly out of range. \n",X,Y);
        }
    }
    fflush(stdout);
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
    static bool grid[HEIGHT][WIDTH];
    initemptygrid(grid); //init empty grid
    randomizegrid(grid);
    printgrid(grid); //print empty grid
    //LOOP
    int amt = 100;
    bool start = true;
    while (amt > 0) {
    //  handle input
        handleinput(grid);
    //  update grid with logic
        updategrid(grid);
    //  render/print grid
        printgrid(grid);
        amt--;
    }
}