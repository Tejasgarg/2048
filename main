#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For usleep()
#include <termios.h> // For handling keypresses without Enter

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

void add_random_number() {
    int i, j;
    srand(time(NULL));

    do {
        i = rand() % SIZE;
        j = rand() % SIZE;
    } while (arr[i][j] != 0);

    arr[i][j] = (rand() % 10 < 9) ? 2 : 4; // 90% chance of 2, 10% chance of 4
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

// Function to reset the game
void reset_game() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            arr[i][j] = 0;
    score = 0;
    add_random_number();
}

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
        char move = get_input();

        if (move == 'R' || move == 'r') {
            reset_game();
        } else if (move == 'U' || move == 'u') {
            exit(0);
        } else if (move == 'A' || move == 'a') {
            move_left();
        } else if (move == 'D' || move == 'd') {
            move_right();
        } else if (move == 'W' || move == 'w') {
            move_up();
        } else if (move == 'S' || move == 's') {
            move_down();
        }

        add_random_number();
        print_board();

        if (is_game_over()) {
            printf("\n\t\t\t\tGAME OVER! Press R to Restart or U to Exit.\n");
        }
    }
    return 0;
}
