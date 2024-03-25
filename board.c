#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  FILE *fp; 
  if((fp = fopen(initFileName, "r")) == NULL) { 
    return NULL; 
  }
  boards_t *board = malloc(sizeof(boards_t));

  fscanf(fp, "%zu", &board->numRows); 
  fscanf(fp, "%zu",&board->numCols);

  board->bufferA = malloc(board->numRows * board->numCols * sizeof(unsigned char));
  board->bufferB = malloc(board->numRows * board->numCols * sizeof(unsigned char));
  board->currentBuffer = board->bufferA;
  board->nextBuffer = board->bufferB;

  size_t numOne; 
  size_t numTwo; 

  clearBoards(board); 
  while(fscanf(fp, "%zu %zu",&numOne, &numTwo) > 0) { 
      size_t index = getIndex(board->numCols, numOne, numTwo); //txt file provides which cells are alive in gen 0
      board->currentBuffer[index] = 1;
  }
  board->gen = 0;
  fclose(fp);
  return board;  
}

/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
   free((*bptrPtr)->bufferB);
   free((*bptrPtr)->bufferA);
   free(*bptrPtr); 
   *bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
   size_t totalCells = self->numRows * self->numCols; 

   for(int i = 0; i < totalCells;i++){ 
	self->currentBuffer[i] = 0;
        self->nextBuffer[i] = 0;
   }
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  belem *temp = self->currentBuffer; 
  self->currentBuffer = self->nextBuffer; 
  self->nextBuffer = temp; 
}


/**
 * get a cell index
 */
size_t getIndex(size_t numCols, size_t row, size_t col){
   return  numCols*row + col;
}
