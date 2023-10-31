/**
 * @file hdispersa.c
 * @brief Source file for sparse matrix verification using POSIX threads
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#include <unistd.h>

#include "Threads.h"
#include "Arguments.h" // Argumetns parsing
#include "Matrix.h"    // Matrix operations

int main(int argc, char *argv[])
{
  /**
   * ---------- ARGUMENTOS ----------
   */
  struct arguments arguments;
  init_arguments(argc, argv, &arguments);

  int number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
  if (arguments.process > number_of_processors)
  {
    printf("No puede ejecutar mas procesos de los CPUs disponibles\n");
    return -1;
  }

  /**
   * ---------- MATRIZ ----------
   */
  struct Matrix sparseMatrix = createMatrix(arguments.rows, arguments.columns);
  if (validateMatrix(arguments.sparse, arguments.rows, arguments.columns) != 1)
  {
    printf("Las filas y las columnas no son las correspondientes al archivo %s \n", arguments.sparse);
    return -1;
  }

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
  return 0;
}
