#define SIM_X_SIZE 1000
#define SIM_Y_SIZE 1000
#define CELLS_PER_ROW 100
#define CELL_SIZE SIM_X_SIZE / CELLS_PER_ROW
#define TOTAL_CELLS CELLS_PER_ROW * CELLS_PER_ROW

#ifndef __sim__
void simInit();
void simExit();
void simFlush();
int simRand();
void FillFigure(int x, int y, int width, int height, int argb);
void app();
#endif
