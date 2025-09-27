#define SIM_X_SIZE 1000
#define SIM_Y_SIZE 1000
#define NUM_CELL_IN_LINE 100
#define LENGTH_OF_CELL SIM_X_SIZE / NUM_CELL_IN_LINE
#define NUM_CELLS NUM_CELL_IN_LINE * NUM_CELL_IN_LINE

#ifndef __sim__
void simInit();

void simExit();

void simFlush();

int simRand();

void fillRect(int x, int y, int width, int height, int argb);

void app();
#endif
