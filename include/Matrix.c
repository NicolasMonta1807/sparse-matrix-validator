/**
 * @file Matrix.c
 * @brief Source file for matrix operations
 * @date 27/09/2023
 * @version 1.0
 * @authors Gabriel Espitia y Nicolás Montañez
 */

#include "Matrix.h" // Header file

struct Matrix createMatrix(int rows, int columns)
{
  int **data = (int **)malloc(rows * sizeof(int *));
  struct Matrix matrix;

  for (int i = 0; i < rows; i++)
    data[i] = (int *)malloc(columns * sizeof(int));

  matrix.rows = rows;
  matrix.cols = columns;
  matrix.data = data;

  return matrix;
}

void loadMatrix(struct Matrix *matrix, char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Error opening file\n");
    exit(1);
  }

  for (int i = 0; i < matrix->rows; i++)
    for (int j = 0; j < matrix->cols; j++)
      fscanf(file, "%d", &matrix->data[i][j]);
}

void printMatrix(struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows; i++)
  {
    for (int j = 0; j < matrix->cols; j++)
      printf("%d ", matrix->data[i][j]);
    printf("\n");
  }
}

void freeMatrix(struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows; i++)
    free(matrix->data[i]);
  free(matrix->data);
}