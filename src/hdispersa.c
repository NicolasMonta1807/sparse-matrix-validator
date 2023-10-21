/**
 * @file hdispersa.c
 * @brief Source file for sparse matrix verification using POSIX threads
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#include "ModuloHilos.h"
#include "Arguments.h" // Argumetns parsing
#include "Matrix.h"    // Matrix operations
#include "RunningTime.h"

int main(int argc, char *argv[])
{
  /**
   * ---------- TIMER ----------
   */
  struct times *myTimes = (struct times *)malloc(sizeof(struct times));
  startTimer(myTimes);

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
  int columnsPerThread = countColumnsPerThread(arguments.process, arguments.columns);

  // Indice de la columna inicial y final a procesar
  int start = 0;
  int end = columnsPerThread - 1;

  /**
   * ---------- HILOS ----------
   */
  pthread_t threads[arguments.process];
  threadCreation(threads, start, end, columnsPerThread, arguments.columns, arguments.rows, arguments.process, sparseMatrix.data);
  /**
   * ---------- PADRE ----------
   */
  int total = totalCount(threads, arguments.process);

  /**
   * ---------- RESULTADOS ----------
   */
  results(total, arguments.rows, arguments.columns, arguments.acceptance, arguments.sparse);

  if (arguments.columns <= 10 && arguments.rows <= 10)
    printMatrix(&sparseMatrix);

  /**
   * ---------- LIBERAR MEMORIA ----------
   */
  freeMatrix(&sparseMatrix);

  /**
   * ---------- END TIMER ----------
   */
  endTimer(myTimes);

  return 0;
}
