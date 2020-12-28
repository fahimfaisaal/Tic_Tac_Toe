#include <stdio.h>
#include <stdbool.h>

char player_one_name[15],
     player_two_name[15],
     tic_tac_to_board[3][3];

int players_input[9],
    player_one_win_count = 0,
    player_two_win_count = 0,
    draw = 0;

//# For Clear Terminal
void clear(void) {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

/** 
 * @param {integer}
 * for show_winner_count function
*/
void clear_and_show(int num) {
    clear();
    show_winner_count(num);
    show_board();
}

//* Get input names from user__________________
void collect_players_name(void) {
   printf("\nInput player one name: ");
   scanf("%[^\n]%*c", player_one_name);

   printf("Input player two name: ");
   scanf("%[^\n]%*c", player_two_name);
}

/**
 * @param {Number} number from user
 * @param {Number} player number 1 or 2
 * organize the number by user input__________________
 */
void players_input_organizer(int number, int player) {

    int row = number / 3, col;

    if (number % 3 != 0) {
        col = (number % 3) - 1;
    } else {
        row--;
        col = 2;
    }

    tic_tac_to_board[row][col] = (player == 1) ? 'X' : 'O';
}

//* Print the tic_tac_to board__________________
void show_board(void) {

    printf("\n\t **TicTacTo Board**\n");
    for (int i = 0; i < 3; i++) {
        printf("\t| ");

        for (int j = 0; j < 3; j++) {
            if (j != 2) printf("[ %c ] ", tic_tac_to_board[i][j]);
            else printf("[ %c ] |\n", tic_tac_to_board[i][j]);
        }
    }
}

/** 
 * @param {Integer} is_end
 * if the game ends then it'll compare & show the final winner__________________
*/
void show_winner_count(int is_end) {
    printf("%s = %d\n%s = %d\nDraw = %d\n", player_one_name, player_one_win_count, player_two_name, player_two_win_count, draw);

    //* if is_end = 0 mean the game has ended, then it'll compare the winner count of players and show the final winner
    if (!is_end) if (player_one_win_count > player_two_win_count) {
        printf("\nFinal Winner is %s\n\n", player_one_name);
    } else if (player_two_win_count > player_one_win_count) {
        printf("\nFinal Winner is %s\n\n", player_two_name);                    
    } else printf("\n\t___MATCH DRAW___\n\n");
}

/** 
 * @param {integer} number form user
 * @return {boolean} if exist number then -> true if not then -> false__________________
*/
bool is_exist_number(int number) {

    for (int i = 0; i < 9; i++) {
        if (number == players_input[i]) {
            clear_and_show(1);

            printf("\nOops :(, your number is already exist.\n");
            return true;
        }
    }

    return false;
}

//* Validation user input range 1 to 9__________________
bool validate_input_range(int number) {

    if (number < 1 || number > 9) {
        clear_and_show(1);

        printf("\n__Your number %d is not valid! Please input a valid number__\n", number);
       return false;
    }

    return true;
}

/** 
 * @param {integer} Number of player 1 or 2
 * @return {boolean} if found match then -> true if not then -> false__________________
*/
bool found_match(int player) {

    int input = player == 1 ? 'X' : 'O',
        row_match = 0,
        col_match = 0,
        max = 2, right_angle_match = 0,
        left_angle_match = 0;

    for (int i = 0; i < 3; i++) {
        //* check row match__________________
        for (int j = 0; j < 3; j++) if (input == tic_tac_to_board[i][j]) {
            row_match++;
            if (row_match == 3) return true;
        }
        row_match = 0;

        //* check column match__________________
        for (int j = 0; j < 3; j++) if (input == tic_tac_to_board[j][i]) {
            col_match++;
            if (col_match == 3) return true;
        }
        col_match = 0;
            
        //* check right angle match__________________
        if (max >= 0) if (input == tic_tac_to_board[i][max]) {
            right_angle_match++;
            if (right_angle_match == 3)  return true;
        }
        max--;

        //* check left angle match__________________
        if (input == tic_tac_to_board[i][i]) {
            left_angle_match++;
            if (left_angle_match == 3) return true;
        }
    }

    return false;
}

/** 
 * @param {integer} Number of player 1 or 2
 * @return {boolean} if have found any match then -> true otherwise -> false__________________
*/
bool is_winner(int player) {

    if (found_match(player)) {
         printf("\n**WINNER WINNER CHICKEN DINNER - %s**\n", player == 1 ? player_one_name : player_two_name);
         return true;
    }

    return false;
}

//* Main Body -------------------------------------------- Start
void main(void) {

    int player_one_input,
        player_two_input,
        count = 9,
        count_draw = 0,
        continue_or_end = 0;

    while (count) {

        if (count == 9) {

            for (int i = 0; i < 3; i++)  for (int j = 0; j < 3; j++) {
                tic_tac_to_board[i][j] = ' ';
            }
            for (int i = 0; i < 9; i++) players_input[i] = 0;

            if (!continue_or_end) collect_players_name();

            clear_and_show(1);
        }

        //* Player One Turn__________________
        while (count) {

            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_one_name);
            scanf("%d", &player_one_input);

            if (!validate_input_range(player_one_input)) continue;

            if (is_exist_number(player_one_input)) continue;
            
            players_input_organizer(player_one_input, 1);
            clear_and_show(1);

            if (count < 6) if (is_winner(1)) {
                player_one_win_count++;
                count = 0;
                break;
            } else count_draw++;

            players_input[player_one_input - 1] = player_one_input;
            count--; break;
        }

        //* Players Two Turn__________________
        while (count) {

            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_two_name);
            scanf("%d", &player_two_input);

            if (!validate_input_range(player_two_input)) continue;

            if (is_exist_number(player_two_input)) continue;

            players_input_organizer(player_two_input, 2);
            clear_and_show(1);

            if (count < 6) if (is_winner(2)) {
                player_two_win_count++;
                count = 0; break;
            } else count_draw++;

            players_input[player_two_input - 1] = player_two_input;
            count--; break;
        }

        //* End the game, When count = 0__________________
        while (!count) {
            clear_and_show(1);

            if (count_draw == 5) {
                clear_and_show(1);
                draw++;
                printf("\n\t____MATCH DRAW____\n");
            }
            printf("\n\nEnter 1 for Continue or 0 for End: ");

            scanf("%d", &continue_or_end);
            printf("\n");

            /** 
             * if continue_or_end = 1 then the game will start again with existing players
             * else the whole process will end and show the final winner__________________
            */
            if (continue_or_end == 1 || continue_or_end == 0) if (!continue_or_end) {
                clear_and_show(0);
                printf("\t___GAME OVER___\n");
                break;
            } else {
                count = 9;
                count_draw = 0;
            }
        }
    }
}