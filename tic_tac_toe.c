#include <stdio.h>
#include <stdlib.h>


char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

int choice, player = 1;

/****** Function prototypes ******/
int checkWin(char board[3][3]);
void drawBoard(char board[3][3]);
int markBoard(char board[3][3], int choice, int player);
int isDraw(char board[3][3]);


int main() {
    int win = 0, draw = 0;
    while (!win && !draw) {
        drawBoard(board);
        printf("Player %d, enter a number (1-9): ", player);
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting.\n");
            break;
        }
        if (!markBoard(board, choice, player)) {
            printf("Invalid move! Try again.\n");
            continue;
        }
        win = checkWin(board);
        draw = isDraw(board);
        if (!win && !draw) {
            player = (player % 2) ? 2 : 1;
        }
    }
    drawBoard(board);
    if (win) {
        printf("==> Player %d wins!\n", player);
    } else if (draw) {
        printf("==> It's a draw!\n");
    }
    return 0;
}


/****** Function implementations ******/
// Check for a win condition
int checkWin(char board[3][3]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1; // Row win
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1; // Column win
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1; // Diagonal win
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1; // Anti-diagonal win
    }
    return 0; // No win
}

// Mark the board with the player's choice
int markBoard(char board[3][3], int choice, int player) {
    char mark = (player == 1) ? 'X' : 'O';
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    if (choice < 1 || choice > 9)
        return 0;
    if (board[row][col] == 'X' || board[row][col] == 'O')
        return 0;
    board[row][col] = mark;
    return 1;
}

// Draw the current state of the board
void drawBoard(char board[3][3]) {
    printf("\nCurrent board:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Check if the game is a draw
int isDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return !checkWin(board);
}
