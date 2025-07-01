function createEmptyGrid (width, height) {
    return Array(width).fill().map(() => Array(height).fill(false));
}
//console.log(createEmptyGrid(10, 11))
function CheckGrid (grid) {
    let retgrid = createEmptyGrid (grid.length, grid[0].length)
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            let liveneighborcount = 0
            let neighbors = [[i+1, j+1], [i+1, j], [i+1, j-1],
                         [i, j+1], [i, j-1],
                         [i-1, j+1], [i-1, j], [i-1, j-1]]
            for (let n = 0; n < neighbors.length; n++) {
                let neighbor = neighbors[n]
                neighbor[0] = (neighbor[0] + grid.length) % grid.length
                neighbor[1] = (neighbor[1] + grid[0].length) % grid[0].length
                if (grid[neighbor[0]][neighbor[1]]) {
                    liveneighborcount += 1
                }
            }

            if (liveneighborcount < 2 || liveneighborcount > 3) {
                retgrid[i][j] = false;
            } else if (liveneighborcount === 2) {
                retgrid[i][j] = grid[i][j];
            } else if (liveneighborcount === 3) {
                retgrid[i][j] = true
            }
        }
    }
    return retgrid
}

function RandomizeGrid (grid) {
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            grid[i][j] = Math.random() < 0.5;
        }
    }
    return grid
}

function RenderGrid(grid, elementid) {
    var c = document.getElementById(elementid);
    var ctx = c.getContext("2d");
    var dwidth = c.width; var dheight = c.height; //Screen width and height
    var tilewidth = dwidth / grid.length; var tileheight = dheight / grid[0].length; // Tile height and width
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            if (grid[i][j]) {
                ctx.fillStyle = "white";
            } else {
                ctx.fillStyle = "black";
            }
            ctx.fillRect(i*tilewidth, j*tileheight, tilewidth, tileheight);
        }
    }
}

let desiredFPS = 30;
let interval = 1000 / desiredFPS;
let lastTime = 0;

function mainloop(currentTime, grid) {
    if (!lastTime) lastTime = currentTime;
    let elapsed = currentTime - lastTime;

    if (elapsed > interval) {
        lastTime = currentTime;

        RenderGrid(maingrid, "maincanvas");
        maingrid = CheckGrid(maingrid);
    }

    requestAnimationFrame(mainloop);
}




let maingrid = RandomizeGrid(createEmptyGrid(300, 300));

maingrid[1][2] = true
maingrid[2][3] = true
maingrid[3][1] = true
maingrid[3][2] = true
maingrid[3][3] = true

console.log(maingrid)
console.log(CheckGrid(maingrid))
//function mainloop() {
    //RenderGrid(maingrid, "maincanvas");
    //maingrid = CheckGrid(maingrid);
    //requestAnimationFrame(mainloop); // Instead of infinite blocking while loop
//}

requestAnimationFrame(mainloop());