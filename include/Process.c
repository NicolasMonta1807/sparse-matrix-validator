/**
 * @file Process.c
 * @brief Source file for process operations
 * @date 31/10/2023
 * @version 1.0
 * @authors Gabriel Espitia y Nicolás Montañez
 */

#include "Process.h"

void childProcessWork(int *pipe_fd, int **matrix, int rows)
{
    pid_t processID = getpid();

    // Recibir columnas a procesar
    int matrixSegment[2];
    read(pipe_fd[0], matrixSegment, sizeof(matrixSegment));
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
        /**
         * ---------- END TIMER ----------
         */
        // Si el valor procesado es menor o igual a 254, se retorna el valor procesado
        exit(count);
    }
    else
    {
        /**
         * ---------- END TIMER ----------
         */
        // Si el valor procesado es mayor a 254, se guarda el valor procesado en un archivo temporal
        char filename[20];
        sprintf(filename, "%d.txt", getpid());
        FILE *file = fopen(filename, "w");
        fprintf(file, "%d", count);
        fclose(file);
        exit(255);
    }
}

int countColumnsPerProcess(int process, int columns)
{
    return round(((float)(columns) / (process)));
}

int totalWork(int process, int columns, int rows, int columnsPerProcess, int **data)
{
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

    for (int i = 0; i < process; i++)
    {
        if (i == process - 1)
            end = columns - 1;

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

            childProcessWork(pipe_fd, data, rows);
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

    int totalCount = 0;

    /**
     * ---------- TIMER ----------
     */
    struct timespec begin, final;
    clock_gettime(CLOCK_REALTIME, &begin);

    for (int i = 0; i < process; i++)
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

    clock_gettime(CLOCK_REALTIME, &final);
    double time_spent = (final.tv_sec - begin.tv_sec) +
                        (final.tv_nsec - begin.tv_nsec) / BILLION;
    printf("Terminado en %f\n", totalCount, time_spent);

    return totalCount;
}

void processResults(int total, int rows, int columns, int acceptance, char *sparse)
{
    int totalZero = (rows * columns) - total;
    int totalSparse = (int)((float)(totalZero * 100) / (float)(rows * columns));
    printf("La matriz en el archivo %s tiene un total %d ceros. ", sparse, totalZero);

    // Validación por porcentaje de aceptación
    if (totalSparse >= acceptance)
    {
        printf("La matriz es dispersa.\n");
    }
    else
    {
        printf("La matriz NO es dispersa.\n");
    }
}