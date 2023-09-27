/**
 * @file Arguments.h
 * @brief Header file for command line arguments parsing
 *
 *  This file contains the declarations for parsing and validating the command line arguments
 *  given to the program when it is executed.
 *
 * @date 27/09/2023
 * @version 1.0
 * @author Gabriel Espitia
 * @author Nicolás Montañez
 */

#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H

#include <stdlib.h> // Standard libraries
#include <argp.h>   // Library for parsing unix-style argument

/**
 * @brief stores the command line arguments
 * @see argp
 */
struct arguments
{
  char *args[2]; // Flag and argument

  // Possible arguments
  int columns;
  int rows;
  char *sparse;   // Matrix file location
  int process;    // Number of processes or threads of distribution
  int acceptance; // Percentage for determining if a matrix is sparse
};

/**
 * @brief Array of possible command line arguments in this single program
 * @see arguments
 */
static struct argp_option options[] = {
    {"rows", 'f', "ROWS", 0, "Number of rows"},
    {"columns", 'c', "COLUMNS", 0, "Number of columns"},
    {"sparse", 'a', "SPARSE_FILE", 0, "Sparse matrix file"},
    {"process", 'n', "PROCESS", 0, "Number of processes"},
    {"acceptance", 'p', "ACCEPTANCE", 0, "Percentage for sparse acceptance"},
    {0}};

/**
 * @brief Cnd validates a single command line argument and set them to the proper structure field
 *
 * This function should be passed to the argp final structure as the parser argument.
 *
 * @param key flag or key of the argument
 * @param arg argument value
 * @param state state of the argument parser (given by argp.h)
 * @return error_t error code if the argument is invalid or 0 if it is valid
 */
error_t parse_opt(int key, char *arg, struct argp_state *state);

/**
 * @brief Parses and validates all the command line arguments and set them to the given structure
 * @param argc number of arguments
 * @param argv array of arguments
 * @param arguments structure to set the arguments
 * @return void
 */
void init_arguments(int argc, char *argv[], struct arguments *arguments);

/**
 * @brief usable argp structure for parsing and validating command line arguments as stated in the arpg library
 * @see argp
 */
static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = "ROWS COLUMNS SPARSE_FILE PROCESS ACCEPTANCE",
    .doc = "Sparse matrix validation"};

#endif // _ARGUMENTS_H
