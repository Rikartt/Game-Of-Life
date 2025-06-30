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
                neighbor[i] %= grid.length
                neighbor[j] %= grid[0].length
                if (grid[neighbor[i]][neighbor[j]]) {
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

let maingrid = createEmptyGrid(20, 20)

maingrid[1][2] = true
maingrid[2][3] = true
maingrid[3][1] = true
maingrid[3][2] = true
maingrid[3][3] = true

console.log(maingrid)
console.log(CheckGrid(maingrid))