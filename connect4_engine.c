/*
    CIS 343 Connect 4 - Game Engine code
    Gaelen McIntee
    3/3/17
*/

#include <stdlib.h>
#include <string.h>
#include "connect4_args.h"
#define PLAYER_MAX 2

int checkwin(int *winner, int connects, int rows, int cols, int **board)
{
	int cell;
	int offset;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++)
		{
			offset = 0;
			cell = board[r][c];
			if (cell == 0)
				continue;

			/* Horizontal case */
			for ( int i = c; i < (c+connects); i++)
			{
				if (i == cols || board[r][i] != cell)
					break;

				if (i == ((c+connects)-1)) {
					*winner = cell;
					return 0;
				}
			}

			/* Vertical case */
			for ( int i = r; i < (r+connects); i++)
			{
				if (i == rows || board[i][c] != cell)
					break;

				if (i == ((r+connects)-1)) {
					*winner = cell;
					return 0;
				}
			}

			/* Up and Right case */
			for ( int i = c; i < (c+connects); i++)
			{
				if (i == cols || (r-offset) < 0 || board[r-offset][i] != cell)
					break;

				if (i == ((c+connects)-1)) {
					*winner = cell;
					return 0;
				}
				offset++;
			}

			/* Up and Left case */
			offset = 0;
			for ( int i = c; i > (c-connects); i--)
			{
				if (i < 0 || (r-offset) < 0 || board[r-offset][i] != cell)
					break;

				if (i == ((c-connects)+1)) {
					*winner = cell;
					return 0;
				}
				offset++;
			}
		}
	}

	return -1;
}

/* Check if the entire board is full.
If the top row is filled, then we can assume the entire board is full.
-1 == not full, 0 == full */
int checkfull(int cols, int **board)
{
	for (int i = 0; i < cols; i++)
	{
		if (board[0][i] == 0)
			return -1;
	}

	return 0;
}

/* Increments to the next player's turn and wraps around to player 1. */
void advance_turn(int *turn)
{
	(*turn)++;

	if (*turn > PLAYER_MAX)
		*turn = 1;

}

/* place the player's chip in the given column. */
int place_chip(int player, int col, int rows, int **board)
{
	int r = 0;
	col--;

	if (board[0][col] != 0)
	{
		fprintf(stderr, "Column is full.\n");
		return -1;
	}

	while (board[r][col] == 0)
	{
		if (r == (rows-1) || board[r+1][col] != 0)
		{
			board[r][col] = player;
			return 0;
		}
		r++;
	}

	return -1;
}

/* Prints the entire board. */
void print_board(int rows, int cols, int **board)
{
	if (board == NULL)
	{
		fprintf(stderr, "Board is empty.\n");
	}
	else
	{
		fprintf(stderr, "\n");
		for(int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {

				if (board[i][j] == 0)
					fprintf(stderr, "–  ");
				else
					fprintf(stderr, "%i  ", board[i][j]);
			}
			fprintf(stderr, "\n");
		}
	}
}

/* This function takes a pointer to a double pointer of int's to hold the game board.  It mallocs 2 areas to manage the board: 1) for holding the game board itself in a long list of values, and 2) for holding a list of offsets to access the board itself given a row number, allowing us to use "board[r][c]" notation without putting in the offset every time. */
void create_board(int rows, int cols, int ***boardptr)
{
	/* This will hold a list of offsets for accessing each row. */
	*boardptr = (int **) malloc(rows * sizeof(int *));
	/* This will hold the board itself in a list of values. */
	**boardptr = (int *) malloc(cols * rows * sizeof(int));

	if ( *boardptr == NULL || **boardptr == NULL) {
		perror("malloc()");
		exit(1);
	}

	/* This sets up the list of offsets to hold the correct positions for each start of a row in the board itself. The size of a row is the number of columns in the board. */
	int **temp;
	for (int i = 0; i < rows; i++) {
		/* Can't just use "boardptr[i]" here, it will increment boardptr first before dereferencing. We want to set the values contained in the malloc'd region, so we have to dereference boardptr first to get our malloc'd region, then increment by i. */
		temp = ((*boardptr)+i);
		/* Then set the value in the malloc'd region to the proper offset. This will allow us to reference the board by using "board[r][c]", and the correct offset will be used everytime. */
		*temp = (**boardptr + (cols * i));
		//fprintf(stderr, "create_board(): i = %i, rows = %i\n", i+1, rows); // debug
	}
	//fprintf(stderr, "create_board():rows = %i\n",rows); // debug
}

/* Calculate the number of digits in an int. */
int num_digits(int num)
{
	int mult = 10;
	int d = 1;
	while (1)
	{
		if (num < mult)
			return d;

		mult *= 10;
		d++;
	}
}

/* Parse the first 3 parameters retrieved from a save file. */
void parse_file(char *loadstr, struct arguments *args, int *turn)
{
	char *temp;

	temp = strtok(loadstr, "\n\002\06");
	args->cols = atoi(temp);
	temp = strtok(NULL, "\n");
	args->rows = atoi(temp);
	temp = strtok(NULL, "\n");
	*turn  = atoi(temp);

	if (args->rows <= 0) args->rows = 7;
	if (args->cols <= 0) args->cols = 7;
	if (args->connect <= 0) args->connect = 4;
}

/* Parse the board that was retrieved in the save file. */
void parse_boardstr(char *boardstr, int rows, int cols, int **board)
{
	char *temp = strtok(boardstr, "\n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			switch ( temp[j] ) {
				case '0':
					board[i][j] = 0; break;
				case '1':
					board[i][j] = 1; break;
				case '2':
					board[i][j] = 2; break;
				case '\n':
					break;
				case ' ':
					break;
				default:
					fprintf(stderr, "Error parsing char %c\n", temp[j]); break;
			}
		}
		temp = strtok(NULL, "\n");
	}
}
