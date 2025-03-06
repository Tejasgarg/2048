#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For usleep()
#include <termios.h> // For handling keypresses without Enter

#define SIZE 4

int arr[SIZE][SIZE] = {0}, score = 0, highscore = 0;

// ANSI color codes for better visibility
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

// Function to get a single key input without pressing Enter
char get_input() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Function to colorize numbers based on value
const char* get_color(int value) {
    switch (value) {
        case 2: return CYAN;
        case 4: return GREEN;
        case 8: return YELLOW;
        case 16: return RED;
        case 32: return MAGENTA;
        case 64: return BLUE;
        case 128: return "\033[1;91m";  // Bright Red
        case 256: return "\033[1;92m";  // Bright Green
        case 512: return "\033[1;93m";  // Bright Yellow
        case 1024: return "\033[1;95m"; // Bright Magenta
        case 2048: return "\033[1;94m"; // Bright Blue
        default: return WHITE; // Default color for larger numbers
    }
}

// Function to print the game board with better alignment & colors
void print_board() {
    system("clear"); // For Linux/macOS; use "cls" for Windows

    printf("\n\t\t\t" BOLD WHITE "===========  2048  ===========\n" RESET);
    printf("\t\t\t" BOLD YELLOW "YOUR SCORE: %d\n" RESET, score);
    printf("\t\t\t" BOLD CYAN "HIGH SCORE: %d\n" RESET, highscore);
    printf("\t\t\t" BOLD WHITE "==============================\n" RESET);

    for (int i = 0; i < SIZE; i++) {
        printf("\t\t\t|"); // Left border
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 0) {
                printf("       |");  // Ensuring uniform spacing for empty cells
            } else {
                printf(" %s%5d%s |", get_color(arr[i][j]), arr[i][j], RESET);  // Color and bold numbers
            }
        }
        printf("\n\t\t\t------------------------------\n"); // Row separator
    }

    printf("\t\t\t" BOLD WHITE "CONTROLS: " RESET BOLD CYAN "W" RESET " (Up), " BOLD CYAN "S" RESET " (Down), " BOLD CYAN "A" RESET " (Left), " BOLD CYAN "D" RESET " (Right)\n");
    printf("\t\t\t" BOLD RED "RESTART: R | EXIT: U\n" RESET);
    printf("\t\t\t" BOLD WHITE "Enter your move: " RESET);
}

// Function to add a random number (2 or 4) to the board
void add_random_number() {
    int i, j;
    srand(time(NULL));

    do {
        i = rand() % SIZE;
        j = rand() % SIZE;
    } while (arr[i][j] != 0);

    arr[i][j] = (rand() % 10 < 9) ? 2 : 4; // 90% chance of 2, 10% chance of 4
}

// Function to copy board state
void copy_board(int src[SIZE][SIZE], int dest[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            dest[i][j] = src[i][j];
}

// Function to check if the board state has changed
int board_changed(int old_board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (old_board[i][j] != arr[i][j])
                return 1; // Board changed
    return 0; // No change
}


// Function to move and merge tiles left
void move_left() {
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = {0}, pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] != 0) {
                if (temp[pos] == 0) {
                    temp[pos] = arr[i][j];
                } else if (temp[pos] == arr[i][j]) {
                    temp[pos] *= 2;
                    score += temp[pos];
                    pos++;
                } else {
                    pos++;
                    temp[pos] = arr[i][j];
                }
            }
        }
        for (int j = 0; j < SIZE; j++) arr[i][j] = temp[j];
    }
}

// Function to move and merge tiles right
void move_right() {
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = {0}, pos = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (arr[i][j] != 0) {
                if (temp[pos] == 0) {
                    temp[pos] = arr[i][j];
                } else if (temp[pos] == arr[i][j]) {
                    temp[pos] *= 2;
                    score += temp[pos];
                    pos--;
                } else {
                    pos--;
                    temp[pos] = arr[i][j];
                }
            }
        }
        for (int j = 0; j < SIZE; j++) arr[i][j] = temp[j];
    }
}

// Function to move and merge tiles up
void move_up() {
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = {0}, pos = 0;
        for (int i = 0; i < SIZE; i++) {
            if (arr[i][j] != 0) {
                if (temp[pos] == 0) {
                    temp[pos] = arr[i][j];
                } else if (temp[pos] == arr[i][j]) {
                    temp[pos] *= 2;
                    score += temp[pos];
                    pos++;
                } else {
                    pos++;
                    temp[pos] = arr[i][j];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) arr[i][j] = temp[i];
    }
}

// Function to move and merge tiles down
void move_down() {
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = {0}, pos = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (arr[i][j] != 0) {
                if (temp[pos] == 0) {
                    temp[pos] = arr[i][j];
                } else if (temp[pos] == arr[i][j]) {
                    temp[pos] *= 2;
                    score += temp[pos];
                    pos--;
                } else {
                    pos--;
                    temp[pos] = arr[i][j];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) arr[i][j] = temp[i];
    }
}


// Function to check if the game is over
int is_game_over() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 0) return 0;
            if (j < SIZE - 1 && arr[i][j] == arr[i][j + 1]) return 0;
            if (i < SIZE - 1 && arr[i][j] == arr[i + 1][j]) return 0;
        }
    }
    return 1;
}

// Reset the game
void reset_game() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            arr[i][j] = 0;
    score = 0;
    add_random_number();
}

// Main function
int main() {
    add_random_number();
    print_board();

    while (1) {
        int old_board[SIZE][SIZE];
        copy_board(arr, old_board); // Save old state

        char move = get_input();
        if (move == 'R' || move == 'r') reset_game();
        else if (move == 'U' || move == 'u') exit(0);
        else if (move == 'A' || move == 'a') move_left();
        else if (move == 'D' || move == 'd') move_right();
        else if (move == 'W' || move == 'w') move_up();
        else if (move == 'S' || move == 's') move_down();

        if (board_changed(old_board)) add_random_number(); // Only add if board changed
        print_board();

        if (is_game_over()) printf("\n\t\t\t" BOLD RED "GAME OVER! Press R to Restart or U to Exit.\n" RESET);
    }
    return 0;
}
