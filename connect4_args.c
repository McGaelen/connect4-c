#include <stdlib.h>
#include "connect4_args.h"

const char *argp_program_version = "Connect Four version 1.0";
const char *argp_program_bug_address = "mcinteeg@mail.gvsu.edu";

char doc[] = "Connect Four: Place 4 tiles in a row vertically, horizontally, or diagonally to win.";

const struct argp_option options[] = {
	{"width", 	'w',	"WIDTH",	0,	"Set the width (number of columns) of the Connect Four game board."},
	{"height",	'h',	"HEIGHT",	0,	"Set the height (number of rows) of the Connect Four game board."},
	{"square",	's',	"SQUARE",	0,	"Set the width and height of the Connect Four game board."},
	{"connect",	'c', 	"CONNECT",	0,	"Set the number of spots in a row needed to win."},
	{"load",	'l',	"LOAD_FILE",0,	"Load a saved game from a file."},
	{"ai",		'a',	NULL,		0,	"(EXPERIMENTAL) Play against an AI."},
	{ 0 }
};

/* Contains how to parse arguments */
const struct argp argp = { options, parse_opt, NULL, doc };

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch (key) {
		case 'w':
			arguments->cols = atoi(arg);
			break;
		case 'h':
			arguments->rows = atoi(arg);
			break;
		case 's':
			arguments->rows = arguments->cols = atoi(arg);
			break;
		case 'c':
			arguments->connect = atoi(arg);
			break;
		case 'l':
			arguments->load = arg;
			break;
		case 'a':
			arguments->ai = 1;
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

void parse_args(int argc, char **argv, struct arguments *arguments)
{
	argp_parse(&argp, argc, argv, 0, 0, arguments);
}
