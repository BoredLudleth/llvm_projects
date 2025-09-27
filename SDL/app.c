#include "sim.h"
#define COLOR_BLUE 0xFF003366
#define COLOR_WHITE 0xFFFFFFFF

void GenerateStartPosition(int field[]) {
  for (int a = 0; a < NUM_CELLS; ++a) {
    field[a] = simRand() & 1;
  }
}

void paintXY(int a, int argb) {
  int aa = a % NUM_CELL_IN_LINE, bb = a / NUM_CELL_IN_LINE;
  fillRect(1 + LENGTH_OF_CELL * aa, 1 + LENGTH_OF_CELL * bb, LENGTH_OF_CELL - 1,
           LENGTH_OF_CELL - 1, argb);
}

int countNeighbours(int field[], int a) {
  int x = a % NUM_CELL_IN_LINE;
  int y = a / NUM_CELL_IN_LINE;

  int y_prev =
      ((y - 1 + NUM_CELL_IN_LINE) % NUM_CELL_IN_LINE) * NUM_CELL_IN_LINE;
  int y_next = ((y + 1) % NUM_CELL_IN_LINE) * NUM_CELL_IN_LINE;
  int x_prev = (x - 1 + NUM_CELL_IN_LINE) % NUM_CELL_IN_LINE;
  int x_next = (x + 1) % NUM_CELL_IN_LINE;
  int y_curr = y * NUM_CELL_IN_LINE;

  return field[y_prev + x_prev] + field[y_prev + x] + field[y_prev + x_next] +
         field[y_curr + x_prev] + field[y_curr + x_next] +
         field[y_next + x_prev] + field[y_next + x] + field[y_next + x_next];
}

void NextStep(int field[]) {
  int field_2[NUM_CELLS] = {};

  for (int a = 0; a < NUM_CELLS; ++a) {
    int result = countNeighbours(field, a);
    field_2[a] = (result == 3) || (result == 2 && field[a] == 1);
  }

  for (int i = 0; i < NUM_CELLS; ++i) {
    field[i] = field_2[i];
  }
}

void DrawField(int field[]) {
  for (int a = 0; a < NUM_CELLS; ++a) {
    if (field[a]) {
      paintXY(a, COLOR_BLUE);
    } else {
      paintXY(a, COLOR_WHITE);
    }
  }
}

void app() {
  int field[NUM_CELLS] = {};
  GenerateStartPosition(field);
  for (int step = 0; step < 10000; ++step) {
    DrawField(field);
    NextStep(field);
    simFlush();
  }
}
