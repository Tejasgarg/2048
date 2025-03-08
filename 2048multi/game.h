#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define SIZE 4
#define HIGHSCORE_FILE "highscore.txt"

extern int arr[SIZE][SIZE];
extern int score, highscore;

// ANSI Colors
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

// Function Declarations
char get_input();
void load_highscore();
void save_highscore();
void print_board();
void add_random_number();
void copy_board(int src[SIZE][SIZE], int dest[SIZE][SIZE]);
int board_changed(int old_board[SIZE][SIZE]);
void move_left();
void move_right();
void move_up();
void move_down();
int is_game_over();
void reset_game();

#endif // GAME_H
