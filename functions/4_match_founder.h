#include <stdbool.h>

/** 
 * @param {integer} Number of player 1 or 2
 * @return {boolean} if found match then -> true if not then -> false__________________
*/
bool found_match(int player, char tic_tac_to_board[3][3]) {
    int input = player == 1 ? 'X' : 'O',
        row_match = 0,
        col_match = 0,
        max = 2, right_diagonal_match = 0,
        left_diagonal_match = 0;

    for (int i = 0; i < 3; i++) {
        /*
        * check row match__________________
        #    * * *
        #    - - -
        #    + + +
        */
        for (int j = 0; j < 3; j++) if (input == tic_tac_to_board[i][j]) {
            row_match++;
            if (row_match == 3) return true;
        }
        row_match = 0;

        /*
        * check column match________________
        #    * - +
        #    * - +
        #    * - +
        */
        for (int j = 0; j < 3; j++) if (input == tic_tac_to_board[j][i]) {
            col_match++;
            if (col_match == 3) return true;
        }
        col_match = 0;
            
        /*
        * check right -> left diagonal angle match__________________
        #    * * /
        #    * / *
        #    / * *
        */
        if (max >= 0) if (input == tic_tac_to_board[i][max]) {
            right_diagonal_match++;
            if (right_diagonal_match == 3) return true;
        }
        max--;

        /*
        * check left -> right diagonal match__________________
        #    \ * *
        #    * \ *
        #    * * \
        */
        if (input == tic_tac_to_board[i][i]) {
            left_diagonal_match++;
            if (left_diagonal_match == 3) return true;
        }
    }

    return false;
}