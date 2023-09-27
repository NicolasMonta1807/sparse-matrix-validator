/**
 * @file hdispersa.c
 * @brief Source file for sparse matrix verification using POSIX threads
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#include <stdlib.h>  // Standard library
#include <stdio.h>   // Standard input/output definitions
#include <math.h>    // Math library (ro
#include <pthread.h> // POSIX threads library

#include "Arguments.h" // Argumetns parsing
#include "Matrix.h"    // Matrix operations

/**
 * @brief parameters for thread work operation
 */
struct ThreadArgs
{
  int toProcess[2]; // First and last column to process
  int **matrix;
  int rows;
  int count;
};

/**
 * @brief Thread work operation
 * @param arg Thread arguments structure
 * @see struct ThreadArgs
 * @return void
 */
void *threadWork(void *arg)
{
  // Retrieve arguments from given structure
  struct ThreadArgs *args = (struct ThreadArgs *)arg;
  int total = 0;

  // Count non-zero elements in the given column-section of the matrix
  for (int i = args->toProcess[0]; i < args->toProcess[1] + 1; i++)
  {
    for (int j = 0; j < args->rows; j++)
    {
      if (args->matrix[j][i] != 0)
        total++;
    }
  }

  // Save result in the given structure
  args->count = total;
  return arg;
}

int main(int argc, char *argv[])
{
  /**
   * ---------- ARGUMENTOS ----------
   */
  struct arguments arguments;
  init_arguments(argc, argv, &arguments);

  /**
   * ---------- MATRIZ ----------
   */
  struct Matrix sparseMatrix = createMatrix(arguments.rows, arguments.columns);
  loadMatrix(&sparseMatrix, arguments.sparse);

  /**
   * ---------- PROCESAMIENTO ----------
   */

  // Cantidad de columnas por hilo
  int columnsPerThread = round((float)(arguments.columns / arguments.process));

  // Indice de la columna inicial y final a procesar
  int start = 0;
  int end = columnsPerThread - 1;

  /**
   * ---------- HILOS ----------
   */
  pthread_t threads[arguments.process];
  for (int i = 0; i < arguments.process; i++)
  {

    if (i == arguments.process - 1)
      end = arguments.columns - 1;

    // Estructura de argumentos para cada hilo
    struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
    int *thread_num = (int *)malloc(sizeof(int));

    // Inicializar argumentos
    args->toProcess[0] = start;
    args->toProcess[1] = end;
    args->rows = arguments.rows;
    args->matrix = sparseMatrix.data;

    // Separación del hilo
    pthread_create(&threads[i], NULL, threadWork, args);

    // Actualización de indices
    start = end + 1;
    end = end + columnsPerThread;
  }

  /**
   * ---------- PADRE ----------
   */
  int total = 0;
  for (int i = 0; i < arguments.process; i++)
  {
    // Recibir argumentos de cada hilo
    struct ThreadArgs *args;
    pthread_join(threads[i], (void **)&args);
    // Sumar cantidad de elementos diferentes de cero
    total += args->count;
  }

  /**
   * ---------- RESULTADOS ----------
   */
  int totalZero = (arguments.rows * arguments.columns) - total;
  int totalSparse = (int)((float)(totalZero * 100) / (float)(arguments.rows * arguments.columns));
  printf("La matriz en el archivo %s tiene un total %d ceros (%d\%): ", arguments.sparse, totalZero, totalSparse);

  // Validación por porcentaje de aceptación
  if (totalSparse >= arguments.acceptance)
  {
    printf("la matriz es dispersa.\n");
  }
  else
  {
    printf("la matriz NO es dispersa.\n");
  }

  /**
   * ---------- LIBERAR MEMORIA ----------
   */
  freeMatrix(&sparseMatrix);

  return 0;
}
