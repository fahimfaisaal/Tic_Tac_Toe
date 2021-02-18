#include <stdio.h>

//* Print the tic_tac_to board__________________
void show_board(char tic_tac_to_board[3][3]) {
    printf("\n\t*TicTacToe Board*\n");
    printf("\t     |     |     \n");

    for (int i = 0; i < 3; i++) {
        i && printf("\t_____|_____|_____\n\t     |     |     \n");

        printf("\t");
        for (int j = 0; j < 3; j++)
            if (j != 2) printf("  %c  |", tic_tac_to_board[i][j]);
            else printf("  %c\n", tic_tac_to_board[i][j]);
    }

    printf("\t     |     |     \n");
}