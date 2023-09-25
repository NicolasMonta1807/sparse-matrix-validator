#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <stdlib.h>
#include <argp.h>

struct arguments
{
  char *args[2];  // Flag and argument
  int columns;    // Columns
  int rows;       // Rows
  char *sparse;   // Matrix information
  int process;    // Number of processes of distribution
  int acceptance; // Percentage for sparse acceptance
};

static struct argp_option options[] = {
    {"rows", 'f', "ROWS", 0, "Number of rows"},
    {"columns", 'c', "COLUMNS", 0, "Number of columns"},
    {"sparse", 'a', "SPARSE_FILE", 0, "Sparse matrix file"},
    {"process", 'n', "PROCESS", 0, "Number of processes"},
    {"acceptance", 'p', "ACCEPTANCE", 0, "Percentage for sparse acceptance"},
    {0}};

error_t parse_opt(int key, char *arg, struct argp_state *state);
void init_arguments(int argc, char *argv[], struct arguments *arguments);

static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = "ROWS COLUMNS SPARSE_FILE PROCESS ACCEPTANCE",
    .doc = "Sparse matrix validation"};

#endif // ARGUMENTS_H
