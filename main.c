#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h> 
#define SIZE 4

int arr[SIZE][SIZE] = {0}, score = 0, highscore = 0;

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

// Function to print the game board with uniform spacing
void print_board() {
    system("clear"); // For Linux/macOS; use "cls" for Windows
    printf("\n\t\t\t\t=============== 2048 ===============\n");
    printf("\t\t\t\tYOUR SCORE: %d\n", score);
    printf("\t\t\t\tHIGH SCORE: %d\n", highscore);
    printf("\t\t\t\t---------------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        printf("\t\t\t\t|");
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 0) {
                printf("      |");  // Empty cell
            } else {
                printf(" %4d |", arr[i][j]);  // Right-aligned within 6 spaces
            }
        }
        printf("\n\t\t\t\t---------------------------------\n");
    }

    printf("\t\t\t\tCONTROLS: W (Up), S (Down), A (Left), D (Right)\n");
    printf("\t\t\t\tRESTART: R | EXIT: U\n");
    printf("\t\t\t\tEnter your move: ");
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

// Move and merge tiles left
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

// Move right
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

// Move up
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

// Move down
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
    printf("=============== 2048 ===============\n");
    printf("WELCOME TO 2048\n");
    printf("> CONTROLS: W (Up), S (Down), A (Left), D (Right)\n");
    printf("  RESTART: R | EXIT: U\n");
    printf("Press any key to start...");
    get_input();

    system("clear");
    printf("\nLoading...\n");
    for (int i = 0; i < 35; i++) {
        printf("#");
        usleep(50000);
    }
    system("clear");

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

        if (board_changed(old_board)) add_random_number(); // Add only if a move happened
        print_board();

        if (is_game_over()) printf("\n\t\t\t\tGAME OVER! Press R to Restart or U to Exit.\n");
    }
    return 0;
}
