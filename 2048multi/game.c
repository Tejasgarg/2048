#include "game.h"

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
    if (ch == '\033') {
        getchar(); 
        ch = getchar();
        if (ch == 'A') ch = 'W';
        else if (ch == 'B') ch = 'S';
        else if (ch == 'C') ch = 'D';
        else if (ch == 'D') ch = 'A';
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void load_highscore() {
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file) {
        fscanf(file, "%d", &highscore);
        fclose(file);
    }
}

void save_highscore() {
    FILE *file = fopen(HIGHSCORE_FILE, "w");
    if (file) {
        fprintf(file, "%d", highscore);
        fclose(file);
    }
}

const char* get_color(int num) {
    switch (num) {
        case 2: return GREEN;
        case 4: return YELLOW;
        case 8: return BLUE;
        case 16: return MAGENTA;
        case 32: return CYAN;
        case 64: return RED;
        case 128: return WHITE;
        case 256: return GREEN;
        case 512: return YELLOW;
        case 1024: return BLUE;
        case 2048: return MAGENTA;
        default: return RESET;
    }
}

void print_board() {
    system("clear");
    printf("\n\t\t\t===========  " BOLD "2048" RESET "  ===========\n");
    printf("\t\t\tYOUR SCORE: %d\n", score);
    printf("\t\t\tHIGH SCORE: %d\n", highscore);
    printf("\t\t\t==============================\n");

    for (int i = 0; i < SIZE; i++) {
        printf("\t\t\t|");
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 0) {
                printf("      |");
            } else {
                printf(" %s%4d%s |", get_color(arr[i][j]), arr[i][j], RESET);
            }
        }
        printf("\n\t\t\t------------------------------\n");
    }
    printf("\t\t\tCONTROLS: Use Arrow Keys to Move\n");
    printf("\t\t\tRESTART: " BOLD "R" RESET " | EXIT: " BOLD "U" RESET "\n");
    printf("\t\t\tEnter your move: ");
}

void add_random_number() {
    int i, j;
    srand(time(NULL));
    do {
        i = rand() % SIZE;
        j = rand() % SIZE;
    } while (arr[i][j] != 0);
    arr[i][j] = (rand() % 10 < 9) ? 2 : 4;
}

void copy_board(int src[SIZE][SIZE], int dest[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            dest[i][j] = src[i][j];
}

int board_changed(int old_board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (old_board[i][j] != arr[i][j])
                return 1;
    return 0;
}

void move_left() {
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = {0}, pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] != 0) {
                if (temp[pos] == 0) temp[pos] = arr[i][j];
                else if (temp[pos] == arr[i][j]) {
                    temp[pos] *= 2;
                    score += temp[pos];
                    pos++;
                } else temp[++pos] = arr[i][j];
            }
        }
        for (int j = 0; j < SIZE; j++) arr[i][j] = temp[j];
    }
}


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

void reset_game() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            arr[i][j] = 0;
    score = 0;
    add_random_number();
}
