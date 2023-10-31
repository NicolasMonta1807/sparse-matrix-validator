/**
 * @file Process.h
 * @brief Header file for the Process module
 *
 * This file contains the prototypes for the functions of the Process module
 *
 * @date 31/10/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#ifndef _MODULOPROCESOS_H
#define _MODULOPROCESOS_H

/**
 * @brief Constant for the number of nanoseconds in a second
 */
#define BILLION 1000000000.0

#include <stdlib.h>    // Standard library
#include <stdio.h>     // Standard input/output definitions
#include <math.h>      // Math library (round)
#include <unistd.h>    // Symbolic constants and types
#include <sys/wait.h>  // Wait for process termination
#include <sys/types.h> // System Data types
#include <time.h>      // Time library

/**
 * @brief Counts the non-zero elements in a section of the matrix
 * @param pipe_fd Pipe file descriptor
 * @param matrix Matrix to process
 * @param rows Number of rows in the matrix
 * @return Amount of non-zero elements in the section of the matrix
 */
void childProcessWork(int *pipe_fd, int **matrix, int rows);

/**
 * @brief Calculates the amount of columns to be processed per process
 * @param process Number of processes
 * @param columns Number of columns in the matrix
 * @return Amount of columns to be processed per process
 */
int countColumnsPerProcess(int process, int columns);

/**
 * @brief Calculates the total amount of work to be done by the processes
 * @param process Number of processes
 * @param columns Number of columns in the matrix
 * @param rows Number of rows in the matrix
 * @param columnsPerProcess Amount of columns to be processed per process
 * @param data Matrix to process
 * @return Total amount of work to be done by the processes
 */
int totalWork(int process, int columns, int rows, int columnsPerProcess, int **data);

/**
 * @brief Creates the processes and assigns them the columns to process - Concurrency function
 * @param process Number of processes
 * @param columnsPerProcess Amount of columns to be processed per process
 * @param columns Number of columns in the matrix
 * @param rows Number of rows in the matrix
 * @param data Matrix to be processed
 * @return void
 */
void processResults(int total, int rows, int columns, int acceptance, char *sparse);

#endif // _MODULOPROCESOS_H