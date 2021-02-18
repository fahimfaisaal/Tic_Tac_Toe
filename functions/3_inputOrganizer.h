/**
 * @param {Number} number from user
 * @param {Number} player number 1 or 2
 * organize the number by user input__________________
 */
void players_input_organizer(int number, int player, char tic_tac_to_board[3][3]) {
    int row = number / 3, col;

    if (number % 3)
     col = (number % 3) - 1;
    else {
        row--;
        col = 2;
    }

    tic_tac_to_board[row][col] = (player == 1) ? 'X' : 'O';
}