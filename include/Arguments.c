#include "Arguments.h"

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
  {
  case 'f':
    arguments->rows = atoi(arg);
    break;
  case 'c':
    arguments->columns = atoi(arg);
    break;
  case 'a':
    arguments->sparse = arg;
    break;
  case 'n':
    arguments->process = atoi(arg);
    break;
  case 'p':
    arguments->acceptance = atoi(arg);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

void init_arguments(int argc, char *argv[], struct arguments *arguments)
{
  arguments->rows = 0;
  arguments->columns = 0;
  arguments->sparse = NULL;
  arguments->process = 0;
  arguments->acceptance = 0;

  argp_parse(&argp, argc, argv, 0, 0, arguments);
}
