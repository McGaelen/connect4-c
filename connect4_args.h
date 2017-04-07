#ifndef C4_ARGS_H
#define C4_ARGS_H

#include <argp.h>

struct arguments {
	int rows, cols, connect, ai;
	char *load;
};

error_t parse_opt(int key, char *arg, struct argp_state *state);
void parse_args(int argc, char **argv, struct arguments *arguments);

#endif
