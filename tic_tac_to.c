#include <stdio.h>
#include <stdbool.h>

char player_one_name[15],
    player_two_name[15],
    tic_tac_to[3][3];
int players_input[9];

//# For Clear Terminal
void clear(void) {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

//* Get input names from user
void collect_players_name(void) {
   printf("\nInput player one name: ");
   scanf("%s", player_one_name);

   printf("Input player two name: ");
   scanf("%s", player_two_name);
}

/**
 * @param {Number} number from user
 * @param {Number} player number 1 or 2
 * organize the number by user input
 */
void players_input_organizer(int number, int player) {

    int row = number / 3, col;

    if (number % 3 != 0) {
        col = (number % 3) - 1;
    } else {
        row--;
        col = 2;
    }

    tic_tac_to[row][col] = (player == 1) ? 'X' : 'O';
}

//* Print the tic_tac_to board
void show_board(void) {

    printf("\n\t **TicTacTo Board**\n");
    for (int i = 0; i < 3; i++) {
        printf("\t| ");

        for (int j = 0; j < 3; j++) {
            if (j != 2) printf("[ %c ] ", tic_tac_to[i][j]);
            else printf("[ %c ] |\n", tic_tac_to[i][j]);
        }
    }
}

/** 
 * @param {integer} number form user
 * @return {boolean} if exist number then -> true if not then -> false
*/
bool is_exist_number(int number) {

    for (int i = 0; i < 9; i++) {
        if (number == players_input[i]) {
            clear();
            show_board();

            printf("\nOops :(, your number is already exist.\n");
            return true;
        }
    }

    return false;
}

//* Validation user input range (1 - 9)
bool validate_input_range(int number) {

    if (number < 1 || number > 9) {
        clear();
        show_board();

        printf("\n__Your number %d is not valid! Please input a valid number__\n", number);
       return false;
    }

    return true;
}

/** 
 * @param {integer} Number of player 1 or 2
 * @return {boolean} if found match then -> true if not then -> false
*/
bool found_match(int player) {

    int input = player == 1 ? 'X' : 'O',
        row_match = 0,
        col_match = 0,
        max = 2, right_angle_match = 0,
        left_angle_match = 0;

    for (int i = 0; i < 3; i++) {
        //* check row match
        for (int j = 0; j < 3; j++) if (input == tic_tac_to[i][j]) {
            row_match++;
            if (row_match == 3) return true;
        }
        row_match = 0;

        //* check column match
        for (int j = 0; j < 3; j++) if (input == tic_tac_to[j][i]) {
            col_match++;
            if (col_match == 3) return true;
        }
        col_match = 0;
            
        //* check right angle match
        if (max >= 0) if (input == tic_tac_to[i][max]) {
            right_angle_match++;
            if (right_angle_match == 3)  return true;
        }
        max--;

        //* check left angle match
        if (input == tic_tac_to[i][i]) {
            left_angle_match++;
            if (left_angle_match == 3) return true;
        }
    }

    return false;
}

/** 
 * @param {integer} Number of player 1 or 2
 * @return {boolean} if have found any match then -> true otherwise -> false
*/
bool is_winner(int player) {

    if (found_match(player)) {
         printf("\n**WINNER WINNER CHICKEN DINNER - %s**\n", player == 1 ? player_one_name : player_two_name);
         return true;
    }

    return false;
}

void main(void) {

    int player_one_input,
        player_two_input,
        count = 9,
        count_draw = 0,
        continue_or_end,
        name_change_permission = 1;

    while (count) {

        if (count == 9) {
            clear();

            for (int i = 0; i < 3; i++)  for (int j = 0; j < 3; j++) {
                tic_tac_to[i][j] = ' ';
            }
            for (int i = 0; i < 9; i++) players_input[i] = 0;

            show_board();

            if (name_change_permission) collect_players_name();
        }

        //* Player One Turn
        while (count) {

            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_one_name);
            scanf("%d", &player_one_input);

            if (!validate_input_range(player_one_input)) continue;

            if (is_exist_number(player_one_input)) continue;
            
            clear();

            players_input_organizer(player_one_input, 1);
            show_board();

            if (count < 6) if (is_winner(1)) {
                count = 0; break;
            } else count_draw++;

            players_input[player_one_input - 1] = player_one_input;
            count--; break;
        }

        //* Players Two Turn
        while (count) {

            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_two_name);
            scanf("%d", &player_two_input);

            if (!validate_input_range(player_two_input)) continue;

            if (is_exist_number(player_two_input)) continue;

            clear();

            players_input_organizer(player_two_input, 2);
            show_board();

            if (count < 6) if (is_winner(2)) {
                count = 0; break;
            } else count_draw++;

            players_input[player_two_input - 1] = player_two_input;
            count--; break;
        }

        //* End the game, When count = 0
        while (!count) {

            count_draw == 5 && printf("\n\t____MATCH DRAW____\n");
            printf("\n\nEnter 1 for Continue or 0 for End: ");

            scanf("%d", &continue_or_end);
            printf("\n");

            if (continue_or_end == 1 || continue_or_end == 0) if (!continue_or_end) {
                printf("\t___GAME OVER___\n");
                break;
            } else {
                count = 9;
                count_draw = 0;

                //* Name Change Permission
                while (1) {
                    clear();
                    
                    printf("Would you like to change names? Yes(1) No(0)\n");
                    scanf("%d", &name_change_permission);
                    if (name_change_permission == 1 || name_change_permission == 0) break;
                }
            }
        }
    }
}