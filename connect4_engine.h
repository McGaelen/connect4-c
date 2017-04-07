/*
    CIS 343 Connect 4 - Game Engine Header
    Gaelen McIntee
    3/3/17
*/

#ifndef C4_ENGINE_H
#define C4_ENGINE_H

int checkfull(int cols, int **board);
int checkwin(int *winner, int connects, int rows, int cols, int **board);
void advance_turn(int *turn);
int place_chip(int player, int col, int rows, int **board);
void print_board(int rows, int cols, int **board);
void create_board(int rows, int cols, int ***board);
void parse_file(char *loadstr, struct arguments *args, int *turn);
void parse_boardstr(char *boardstr, int rows, int cols, int **board);
int num_digits(int num);

#endif
