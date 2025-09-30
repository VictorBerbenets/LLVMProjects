#include "sim.h"

#define CELL_ALIVE_COLOR 0xFF3366CC
#define CELL_DEAD_COLOR  0xFFFFFFFF

void InitializeGameState(int grid[]) {
    for (int i = 0; i < TOTAL_CELLS; ++i) {
        grid[i] = simRand() & 1;
    }
}

void RenderCell(int index, int color) {
    int col = index % CELLS_PER_ROW;
    int row = index / CELLS_PER_ROW;
    FillFigure(1 + CELL_SIZE * col, 1 + CELL_SIZE * row, 
             CELL_SIZE - 1, CELL_SIZE - 1, color);
}

int CalculateLivingNeighbors(int grid[], int index) {
    int col = index % CELLS_PER_ROW;
    int row = index / CELLS_PER_ROW;

    int prev_row = ((row - 1 + CELLS_PER_ROW) % CELLS_PER_ROW) * CELLS_PER_ROW;
    int next_row = ((row + 1) % CELLS_PER_ROW) * CELLS_PER_ROW;
    int prev_col = (col - 1 + CELLS_PER_ROW) % CELLS_PER_ROW;
    int next_col = (col + 1) % CELLS_PER_ROW;
    int curr_row = row * CELLS_PER_ROW;

    return grid[prev_row + prev_col] + grid[prev_row + col] + grid[prev_row + next_col] +
           grid[curr_row + prev_col] + grid[curr_row + next_col] +
           grid[next_row + prev_col] + grid[next_row + col] + grid[next_row + next_col];
}

void AdvanceGeneration(int grid[]) {
    int next_grid[TOTAL_CELLS] = {};

    for (int i = 0; i < TOTAL_CELLS; ++i) {
        int neighbors = CalculateLivingNeighbors(grid, i);
        next_grid[i] = (neighbors == 3) || (neighbors == 2 && grid[i] == 1);
    }

    for (int i = 0; i < TOTAL_CELLS; ++i) {
        grid[i] = next_grid[i];
    }
}

void DisplayGrid(int grid[]) {
    for (int i = 0; i < TOTAL_CELLS; ++i) {
        if (grid[i]) {
            RenderCell(i, CELL_ALIVE_COLOR);
        } else {
            RenderCell(i, CELL_DEAD_COLOR);
        }
    }
}

void app() {
    int game_grid[TOTAL_CELLS] = {};
    InitializeGameState(game_grid);
    
    for (int generation = 0; generation < 10000; ++generation) {
        DisplayGrid(game_grid);
        AdvanceGeneration(game_grid);
        simFlush();
    }
}
