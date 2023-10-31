/**
 * @file Threads.h
 * @brief Header file for the Threads module
 *
 *  This file contains the prototypes for the functions of the Threads module
 *
 * @date 31/10/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#ifndef _MODULOHILOS_H
#define _MODULOHILOS_H

/**
 * @brief Constant for the number of nanoseconds in a second
 */
#define BILLION 1000000000.0

#include <stdlib.h>  // Standard library
#include <stdio.h>   // Standard input/output definitions
#include <math.h>    // Math library (ro
#include <pthread.h> // POSIX threads library
#include <unistd.h>  // Symbolic constants
#include <time.h>    // Time library

/**
 * @brief Structure for the arguments of the threads
 */
struct ThreadArgs
{
    int toProcess[2]; // First and last column to process
    int **matrix;
    int rows;
    int count;
};

/**
 * @brief Counts the non-zero elements in a section of the matrix
 * @param arg Pointer to the arguments of the thread
 * @return Pointer to the result of the thread
 */
void *threadWork(void *arg);

/**
 * @brief Calculates the ampunt of columns to be processed per thread
 * @param process Number of threads
 * @param columns Number of columns in the matrix
 * @return Amount of columns to be processed per thread
 */
int countColumnsPerThread(int process, int columns);

/**
 * @brief Creates the threads and assigns them the columns to process - Concurrency function
 * @param threads Array of threads
 * @param start First column to process
 * @param end Last column to process
 * @param columnsPerThread Amount of columns to be processed per thread
 * @param columns Number of columns in the matrix
 * @param rows Number of rows in the matrix
 * @param process Number of threads
 * @param data Matrix to be processed
 * @return Void
 */
void threadCreation(pthread_t *threads, int start, int end, int columnsPerThread, int columns, int rows, int process, int **data);

/**
 * @brief Counts the total amount of non-zero elements in the matrix
 * @param threads Array of threads
 * @param process Number of threads
 * @return Total amount of non-zero elements in the matrix
 */
int totalCount(pthread_t *threads, int process);

/**
 * @brief Prints the results of the program
 * @param total Total amount of non-zero elements in the matrix
 * @param rows Number of rows in the matrix
 * @param columns Number of columns in the matrix
 * @param acceptance Acceptance percentage
 * @param sparse Sparse or dense matrix
 * @return Void
 */
void results(int total, int rows, int columns, int acceptance, char *sparse);

#endif // _MODULOHILOS_H