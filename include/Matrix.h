/**
 * @file Matrix.h
 * @brief Header file for matrix operations
 *
 *  This file contains the declarations for matrix operations
 *  usage and operation. (creation, load, print, free)
 *
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdlib.h> // Standard libraries
#include <stdio.h>  // Standard input/output definitions

/**
 * @brief stores the matrix dimensions and data
 */
struct Matrix
{
  int rows;
  int cols;
  int **data;
};

/**
 * @brief Creates a matrix with the given dimensions
 * @param rows number of rows
 * @param columns number of columns
 * @return instance of created matrix
 */
struct Matrix createMatrix(int rows, int columns);

/**
 * @brief Loads a matrix from a file
 * @param matrix pointer to the matrix to load
 * @param filename name of the file to load
 * @return void
 */
void loadMatrix(struct Matrix *matrix, char *filename);

/**
 * @brief Prints a matrix to the console
 * @param matrix pointer to the matrix to print
 * @return void
 */
void printMatrix(struct Matrix *matrix);

/**
 * @brief Frees the memory of a matrix
 * @param matrix pointer to the matrix to free
 * @return void
 */
void freeMatrix(struct Matrix *matrix);

/**
 * @brief Validates the rows and cols within the file
 * @param filename name of the file to be read
 * @param expectedRows number of rows that should be in the file
 * @param expectedRows number of columns that should be in the file
 * @return int 1 if valid
 */
int validateMatrix(char *filename, int expectedRows, int expectedCols);

#endif // _MATRIX_H