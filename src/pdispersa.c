/**
 * @file pdispersa.c
 * @brief Source file for sparse matrix verification using processes
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#include <stdlib.h>   // Standard library
#include <stdio.h>    // Standard input/output definitions
#include <math.h>     // Math library (round)
#include <unistd.h>   // Symbolic constants and types
#include <sys/wait.h> // Wait for process termination

#include "Arguments.h" // Argumetns parsing
#include "Matrix.h"    // Matrix operations

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
void childProcessWork(int pipe_fd, int **matrix, int rows)
{
  /**
   * ---------- HIJO ----------
   */

  // Recibir columnas a procesar
  int matrixSegment[2];
  read(pipe_fd, matrixSegment, sizeof(matrixSegment));

  // Contar elementos diferentes de cero en la matriz
  int count = 0;
  for (int i = matrixSegment[0]; i < matrixSegment[1] + 1; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      if (matrix[j][i] != 0)
        count++;
    }
  }

  // Retornar el valor procesado
  if (count <= 254)
  {
    // Si el valor procesado es menor o igual a 254, se retorna el valor procesado
    exit(count);
  }
  else
  {
    // Si el valor procesado es mayor a 254, se guarda el valor procesado en un archivo temporal
    char filename[20];
    sprintf(filename, "%d.txt", getpid());
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d", count);
    fclose(file);
    exit(255);
  }
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

  // Cantidad de columnas por proceso
  int columnsPerProcess = round((float)(arguments.columns / arguments.process));

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
  for (int i = 0; i < arguments.process; i++)
  {
    if (i == arguments.process - 1)
      end = arguments.columns - 1;

    int columns[] = {start, end};
    pid_t pid = fork();

    if (pid == 0)
    {
      /**
       * ---------- HIJO ----------
       * 1. Recibir columnas a procesar: [Inicio, Final]
       * 2. Apuntador a la matriz
       * 3. Cantidad de filas por columna
       */
      write(pipe_fd[1], columns, sizeof(columns));
      childProcessWork(pipe_fd[0], sparseMatrix.data, arguments.rows);
    }
    else if (pid < 0)
    {
      perror("Error en fork");
      exit(EXIT_FAILURE);
    }

    // Actualización de indices
    start = end + 1;
    end = end + columnsPerProcess;
  }

  /**
   * ---------- PADRE ----------
   */
  int totalCount = 0;
  for (int i = 0; i < arguments.process; i++)
  {
    int status;
    pid_t childID = wait(&status);
    // Esperar a que los procesos hijo terminen
    if (WIFEXITED(status))
    {
      int exit_status = WEXITSTATUS(status);
      /**
       * 1. Si el proceso hijo termina con un valor diferente a 255, significa que no superó el límite de 254 ceros
       */
      if (exit_status != 255)
      {
        totalCount += exit_status;
      }
      else
      {
        /**
         * 2. Si el proceso hijo termina con un valor de 255, significa que superó el límite de 254 ceros
         * y se debe leer el valor procesado desde un archivo identificado con el ID del proceso hijo
         *
         * 3. Se remueve el archivo temporal con la información procesada
         */
        char filename[20];
        sprintf(filename, "%d.txt", childID);
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
          printf("Error opening file\n");
          exit(1);
        }
        int count;
        fscanf(file, "%d", &count);
        totalCount += count;
        fclose(file);
        remove(filename);
      }
    }
  }

  /**
   * ---------- RESULTADOS ----------
   */
  int totalZero = (arguments.rows * arguments.columns) - totalCount;                               // Cantidad de ceros
  int totalSparse = (int)((float)(totalZero * 100) / (float)(arguments.rows * arguments.columns)); // Porcentaje de ceros
  printf("La matriz en el archivo %s tiene un total %d ceros (%d\%): ", arguments.sparse, totalZero, totalSparse);

  // Validación por porcentaje de aceptación dado
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
