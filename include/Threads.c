/**
 * @file Threads.c
 * @brief Source file for threads operations
 * @date 31/10/2023
 * @version 1.0
 * @authors Gabriel Espitia y Nicolás Montañez
 */

#include "Threads.h"

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

    /**
     * ---------- END TIMER ----------
     */
    return arg;
}

int countColumnsPerThread(int process, int columns)
{
    return round((float)(columns / process));
}

void threadCreation(pthread_t *threads, int start, int end, int columnsPerThread, int columns, int rows, int process, int **data)
{
    for (int i = 0; i < process; i++)
    {
        if (i == process - 1)
            end = columns - 1;

        // Estructura de argumentos para cada hilo
        struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
        int *thread_num = (int *)malloc(sizeof(int));

        // Inicializar argumentos
        args->toProcess[0] = start;
        args->toProcess[1] = end;
        args->rows = rows;
        args->matrix = data;

        // Separación del hilo
        pthread_create(&threads[i], NULL, threadWork, args);

        // Actualización de indices
        start = end + 1;
        end = end + columnsPerThread;
    }
}

int totalCount(pthread_t *threads, int process)
{
    /**
     * ---------- TIMER ----------
     */
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    int total = 0;

    for (int i = 0; i < process; i++)
    {
        // Recibir argumentos de cada hilo
        struct ThreadArgs *args;
        pthread_join(threads[i], (void **)&args);
        // Sumar cantidad de elementos diferentes de cero
        total += args->count;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - begin.tv_sec) +
                        (end.tv_nsec - begin.tv_nsec) / BILLION;
    printf("Terminado en %f\n", time_spent);

    return total;
}

void results(int total, int rows, int columns, int acceptance, char *sparse)
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