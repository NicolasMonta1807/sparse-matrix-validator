#ifndef _MODULOPROCESOS_H
#define _MODULOPROCESOS_H

#include <stdlib.h>   // Standard library
#include <stdio.h>    // Standard input/output definitions
#include <math.h>     // Math library (round)
#include <unistd.h>   // Symbolic constants and types
#include <sys/wait.h> // Wait for process termination

void childProcessWork(int pipe_fd, int **matrix, int rows);
int countColumnsPerProcess(int process, int columns);
int totalWork(int process, int columns, int rows, int end, int start, int columnsPerProcess, int *pipe_fd, int **data);
void processResults(int total, int rows, int columns, int acceptance, char *sparse);

#endif // _MODULOPROCESOS_H