#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

struct Matrix
{
  int rows;
  int cols;
  int **data;
};

struct Matrix createMatrix(int rows, int columns);
void loadMatrix(struct Matrix *matrix, char *filename);
void printMatrix(struct Matrix *matrix);
void freeMatrix(struct Matrix *matrix);

#endif // MATRIX_H