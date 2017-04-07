/*
	Connect Four - main code file
	Gaelen McIntee
	3/3/17

	Connect Four: Place 4 tiles in a row vertically, horizontally, or diagonally to win.

	Issues:
	–	Doing a save followed by a load on the same file causes a seg fault and erases the contents of said file.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "file_utils.h"
#include "connect4_args.h"
#include "connect4_engine.h"
#include "connect4_ai.h"
#define INPUT_MAX 100

int main(int argc, char *argv[])
{
	/* Holds parsed arguments. */
	struct arguments args;
	/* Holds user input whenever we ask for it. */
	char input[INPUT_MAX];
	/* Buffers to hold string representations of the game board. */
	char *loadBuffer, *saveBuffer;
	/* The board itself. */
	int **board = NULL;
	/* Holds the number of the player whose turn it is. */
	int turn = 1;
	/* Holds which column the user wants to place their chip. */
	int move = 0;
	/* Holds the number corresponding to the winning player, or 0 if no current winner. */
	int winner = 0;

	/* initialize default vals for args */
	args.rows = 7;
	args.cols = 7;
	args.connect = 4;
	args.load = "";
	args.ai = 0;

	parse_args(argc, argv, &args);

	/* If args.load isn't empty, then try to load the requeusted file. */
	if ( strcmp(args.load, "") != 0 )
	{
		read_file(args.load, &loadBuffer);

		parse_file(loadBuffer, &args, &turn);
		char *boardstr = strtok(NULL, "");

		create_board(args.rows, args.cols, &board);
		parse_boardstr(boardstr, args.rows, args.cols, board);
		free(loadBuffer);
	}
	/* Create an empty board with the correct row and col values. */
	else
	{
		create_board(args.rows, args.cols, &board);

		for (int i = 0; i < args.rows; i++) {
			for (int j = 0; j < args.cols; j++) {
				board[i][j] = 0;
			}
		}
	}

	/* Only if playing against an AI. */
	if (args.ai == 1)
		ai_init(2);

	/* Print welcome message */
	fprintf(stderr, "Rows: %i\nCols: %i\nConnects: %i\nLoad file: %s\nAI: %i\n\nGame start!\n", args.rows, args.cols, args.connect, args.load, args.ai);
	print_board(args.rows, args.cols, board);


	/* Main program loop */
	while (1)
	{
		/* Perform AI's turn if we're playing against one */
		if (args.ai == 1 && turn == 2)
		{
			fprintf(stderr, "AI's turn...\n");
			sleep(2); // the AI is "thinking"

			move = 1 + ai_getmove(board, args.rows, args.cols);
			place_chip(turn, move, args.rows, board);

			fprintf(stderr, "AI placed a chip in column %i\n", move);
			print_board(args.rows, args.cols, board);
			advance_turn(&turn);
		}

		/* Display input prompt. */
		fprintf(stderr, "(connect4-p%i) ", turn);
		fgets(input, INPUT_MAX, stdin);
		move = atoi(input);

		/* Quit */
		if (strcmp(input, "q\n") == 0 ||
			strcmp(input, "Q\n") == 0 ||
			strcmp(input, "exit\n") == 0)
		{
			free(*board);
			free(board);
			exit(0);
		}
		/* Load */
		else if (strcmp(input, "load\n") == 0)
		{
			fprintf(stderr, " Filename? ");
			fgets(input, INPUT_MAX, stdin);

			read_file(strtok(input, "\n"), &loadBuffer);
			args.load = input;

			parse_file(loadBuffer, &args, &turn);
			char *boardstr = strtok(NULL, "");

			create_board(args.rows, args.cols, &board);
			parse_boardstr(boardstr, args.rows, args.cols, board);

			fprintf(stderr, "Rows: %i\nCols: %i\nConnects: %i\nLoad file: %s\n\nGame start!\n", args.rows, args.cols, args.connect, args.load);
			print_board(args.rows, args.cols, board);

			free(loadBuffer);
		}
		/* Save */
		else if (strcmp(input, "save\n") == 0)
		{
			fprintf(stderr, " Filename? ");
			fgets(input, INPUT_MAX, stdin);

			int size = num_digits(args.cols) + num_digits(args.rows) + num_digits(turn) + 4 + ((args.rows+1) * args.cols);
			fprintf(stderr, "Filesize: %i Bytes\n", size);
			saveBuffer = (char *)malloc(size);

			*saveBuffer = '\0';
			sprintf(saveBuffer, "%i\n%i\n%i\n", args.cols, args.rows, turn);

			char temp[1];
			for (int r = 0; r < args.rows; r++) {
				for (int c = 0; c < args.cols; c++) {
					sprintf(temp, "%i", board[r][c]);
					strcat(saveBuffer, temp);
				}
				strcat(saveBuffer, "\n");
			}

			write_file(strtok(input, "\n"), saveBuffer, size);
			fprintf(stderr, "File saved.\n");
			free(saveBuffer);
		}
		/* Place a chip if the user's input is a valid column. */
		else if (move > 0)
		{
			if (move > args.cols)
			{
				fprintf(stderr, "Column doesn't exist.\n");
			}
			else if (place_chip(turn, move, args.rows, board) == 0)
			{
				fprintf(stderr, "Player %i placed a chip in column %i\n", turn, move);
				print_board(args.rows, args.cols, board);
				advance_turn(&turn);
			}
		}
		else
		{
			fprintf(stderr, "Unrecognized input.\n");
		}

		/* Check for either a full board or new winner. */
		if (checkwin(&winner, args.connect, args.rows, args.cols, board) >= 0 ||
			checkfull(args.cols, board) == 0)
		{
			if (winner > 0)
				fprintf(stderr, "Player %i wins!\nPlay again? (y/n) ", winner);
			else
				fprintf(stderr, "Game over, board is full!\nPlay again? (y/n) " );

			fgets(input, INPUT_MAX, stdin);

			/* If the user wants to play again, make an empty board. Otherwise, just exit the program */
			if (strcmp(input, "y\n") == 0 || strcmp(input, "Y\n") == 0)
			{
				create_board(args.rows, args.cols, &board);
				for (int i = 0; i < args.rows; i++) {
					for (int j = 0; j < args.cols; j++) {
						board[i][j] = 0;
					}
				}
				turn = 1;
				args.load = "";

				fprintf(stderr, "Rows: %i\nCols: %i\nConnects: %i\nLoad file: %s\n\nGame start!\n", args.rows, args.cols, args.connect, args.load);
				print_board(args.rows, args.cols, board);
			}
			else
			{
				fprintf(stderr, "Goodbye!\n");
				free(*board);
				free(board);
				exit(0);
			}
		}
	}

	return 0;
}
