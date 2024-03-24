#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, size_t, size_t, size_t);

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t getModVal(int x, size_t N){
    size_t adj = x/N;
    return((x+adj*N)%N);
}

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *src, size_t row, size_t rows, size_t cols){
  for(size_t i = 0; i < cols; i++) {
    int neighbors = 0; 
    for(int j = -1; j <= 1; j++) { 
      for(int k = -1; k <= 1; k++) { 
        if(j == 0 && k == 0) { 
          continue; 
        } 
        size_t adjRow = getModVal(row + j, rows); 
        size_t adjCol = getModVal(i + k, cols); 
        neighbors += src[getIndex(cols, adjRow, adjCol)]; 
      }
    } 
    size_t index = getIndex(cols, row, i); 
    if(src[index] == 1) { 
      if(neighbors == 1 || neighbors == 0) { 
        dest[index] = 0;
      } else if(neighbors == 2 || neighbors == 3) {
        dest[index] = 1;
      } else if(neighbors ==4) {
        dest[index] = 0;
      }
    } else {
      if(neighbors == 3) {
        dest[index] = 1;
      } else {
        dest[index] = 0;
      }
    }
  }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
: */
void simLoop(boards_t *self, unsigned int steps){
  for(int i = 0; i < steps; i++) {
    for(size_t j = 0; j < self->numRows; j++) {
      doRow(self->nextBuffer, self->currentBuffer, j, self->numRows, self->numCols);
    }
    swapBuffers(self);
    self->gen++;
  }
}

