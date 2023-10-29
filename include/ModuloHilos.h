#ifndef _MODULOHILOS_H
#define _MODULOHILOS_H

#define BILLION 1000000000.0

#include <stdlib.h>  // Standard library
#include <stdio.h>   // Standard input/output definitions
#include <math.h>    // Math library (ro
#include <pthread.h> // POSIX threads library
#include <unistd.h>  // Symbolic constants
#include <time.h>    // Time library

struct ThreadArgs
{
    int toProcess[2]; // First and last column to process
    int **matrix;
    int rows;
    int count;
};

void *threadWork(void *arg);
int countColumnsPerThread(int process, int columns);
void threadCreation(pthread_t *threads, int start, int end, int columnsPerThread, int columns, int rows, int process, int **data);
int totalCount(pthread_t *threads, int process);
void results(int total, int rows, int columns, int acceptance, char *sparse);

#endif // _MODULOHILOS_H