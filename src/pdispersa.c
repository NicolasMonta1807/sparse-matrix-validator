/**
 * @file pdispersa.c
 * @brief Source file for sparse matrix verification using processes
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#include "ModuloProcesos.h"
#include "Arguments.h" // Argumetns parsing
#include "Matrix.h"    // Matrix operations
#include "RunningTime.h"

/**
 * @brief Matrix sparse verification
 *
 * This function is used to count the number of non-zero elements in the given column-section of a matrix
 * and return the result to the parent process.
 *
 * @param pipe_fd Pipe descriptor
 * @param matrix Matrix pointer
 * @param rows Number of rows in the matrix
 * @return void
 */

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
  if (validateMatrix(arguments.sparse, arguments.rows, arguments.columns) != 1)
  {
    printf("Las filas y las columnas no son las correspondientes al archivo %s \n", arguments.sparse);
    return -1;
  }

  loadMatrix(&sparseMatrix, arguments.sparse);

  /**
   * ---------- PROCESAMIENTO ----------
   */

  // Cantidad de columnas por proceso
  int columnsPerProcess = countColumnsPerProcess(arguments.process, arguments.columns);

  // Comunicación entre procesos
  int pipe_fd[2];
  if (pipe(pipe_fd) == -1)
  {
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }

  // Indice de la columna inicial y final a procesar
  int start = 0;
  int end = columnsPerProcess - 1;

  /**
   * ---------- PROCESOS ----------
   */

  int totalCount = totalWork(arguments.process, arguments.columns, arguments.rows, end, start, columnsPerProcess, pipe_fd, sparseMatrix.data);

  /**
   * ---------- RESULTADOS ----------
   */
  processResults(totalCount, arguments.rows, arguments.columns, arguments.acceptance, arguments.sparse);

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
