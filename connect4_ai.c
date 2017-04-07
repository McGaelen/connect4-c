/*
	Connect Four Blocking AI
	Gaelen McIntee
	3/3/17

	This AI is designed to block any attempt by the player to win the match.  It doesn't try to win for itself at all, although that may happen by chance.

	This is not a very good AI. But it does play the game, and does more just pick a random column.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int player, opp;

void ai_setPlayer(int p)
{
	player = p;
	if (player == 1)
		opp = 2;
	else
		opp = 1;
}

void ai_init(int playerNum)
{
	srand(time(NULL));
	ai_setPlayer(playerNum);
}


bool ai_checkColFull(int **board, int col)
{
	if (board[0][col] != 0)
		return true;
	return false;
}

int ai_randomInt(int **board)
{
	int i = rand()%6;
	while (ai_checkColFull(board, i) == true)
		i = rand()%6;
	return i;
}

int ai_getmove(int **board, int rows, int cols)
{

	for (int row = 0; row<rows; row++) {

		for (int col = 0; col<cols; col++){
			if (board[row][col] == opp) {

				//////////////////////////////BACK AND UP
				if ((col-3) >= 0 && (row-3) >= 0) {
					if (board[row-1][col-1] == opp && board[row-2][col-2] == opp){
						if (board[row-3][col-3] == 0 && board[row-2][col-3] != 0) {
							if (ai_checkColFull(board, col-3) == false)
								return col-3;
						}
					}
				}

				//////////////////////////////BACK AND DOWN
				if ((col-3) >= 0 && (row+3) < rows) {
					if (board[row+1][col-1] == opp && board[row+2][col-2] == opp){
						if (board[row+3][col-3] == 0) {
							if ((row+4) >= rows) {
								if (ai_checkColFull(board, col-3) == false)
									return col-3;
							} else if (board[row+4][col-3] != 0) {
								if (ai_checkColFull(board, col-3) == false)
									return col-3;
							}
						}
					}
				}

				/////////////////////////////UP
				if ((row-3) >= 0 && board[row-3][col] == 0 && board[row-2][col] == opp && board[row-1][col] == opp) {
					if (ai_checkColFull(board, col) == false)
						return col;
				}
				/////////////////////////////LEFT
				if ((col-3) >= 0 && board[row][col-3] == 0 && board[row][col-2] == opp && board[row][col-1] == opp) {
					if (row+1 >= 6) {
						if (ai_checkColFull(board, col-3) == false)
							return col-3;
					} else if (board[row+1][col-3] != 0) {
						if (ai_checkColFull(board, col-3) == false)
							return col-3;
					}
				}

				/////////////////////////////LEFT MID
				if ((col-3) >= 0 && board[row][col-3] == opp) {
					if (board[row][col-2] == opp) {
						if (row+1 >= rows) {
							if (ai_checkColFull(board, col-1) == false)
								return col-1;
						} else if (board[row+1][col-1] != 0) {
							if (ai_checkColFull(board, col-1) == false)
								return col-1;
						}
					} else if (board[row][col-1] == opp) {
						if (row+1 >= rows) {
							if (ai_checkColFull(board, col-2) == false)
								return col-2;
						} else if (board[row+1][col-2] != 0) {
							if (ai_checkColFull(board, col-2) == false)
								return col-2;
						}
					}
				}
				//////////////////////////////BACK AND UP AND MID
				if ((col-3) >= 0 && (row-3) >= 0) {
					if (board[row-3][col-3] == opp){
						if (board[row-2][col-2] == opp) {
							if (board[row-1][col-1] == 0 && board[row][col-1] != 0) {
								if (ai_checkColFull(board, col-1) == false)
									return col-1;
							}
						}
						if (board[row-1][col-1] == opp) {
							if (board[row-2][col-2] == 0 && board[row-1][col-2] != 0) {
								if (ai_checkColFull(board, col-2) == false)
									return col-2;
							}
						}
					}
				}

				//////////////////////////////FORWARD AND UP AND MID
				if ((col+3) < cols && (row-3) >= 0) {
					if (board[row-3][col+3] == opp){
						if (board[row-2][col+2] == opp) {
							if (board[row-1][col+1] == 0 && board[row][col+1] != 0) {
								if (ai_checkColFull(board, col+1) == false)
									return col+1;
							}
						}
						if (board[row-1][col+1] == opp) {
							if (board[row-2][col+2] == 0 && board[row-1][col+2] != 0) {
								if (ai_checkColFull(board, col+2) == false)
									return col+2;
							}
						}
					}
				}
			}
		}
	}
	return ai_randomInt(board);
}
