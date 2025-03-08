#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    load_highscore();
    add_random_number();
    print_board();

    while (1) {
        int old_board[SIZE][SIZE];
        copy_board(arr, old_board);

        char move = get_input();
        if (move == 'R' || move == 'r') reset_game();
        else if (move == 'U' || move == 'u') exit(0);
        else if (move == 'A' || move == 'a') move_left();
        else if (move == 'D' || move == 'd') move_right();
        else if (move == 'W' || move == 'w') move_up();
        else if (move == 'S' || move == 's') move_down();

        if (score > highscore) {
            highscore = score;
            save_highscore();
        }

        if (board_changed(old_board)) add_random_number();
        print_board();

        if (is_game_over()) 
            printf("\n\t\t\t" RED "GAME OVER!" RESET " Press " BOLD "R" RESET " to Restart or " BOLD "U" RESET " to Exit.\n");
    }
    return 0;
}
