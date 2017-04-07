/*
	Connect Four Blocking AI Header
	Gaelen McIntee

*/

#ifndef C4_AI_H
#define C4_AI_H
#include <stdbool.h>

void ai_init(int playerNum);
void ai_setPlayer(int p);
bool ai_checkColFull(int **board, int col);
int ai_randomInt(int **board);
int ai_getmove(int **board, int rows, int cols);

#endif
