#include <stdio.h>
#include <stdbool.h>
#include <math.h>

char player_one_name[15],
    player_two_name[15],
    tic_tac_to[3][3];
int players_input[9];

void collect_players_name() {
   printf("\nInput player one name: ");
   scanf("%s", player_one_name);

   printf("Input player two name: ");
   scanf("%s", player_two_name);
}

void tic_tac_to_board(int number, int player) {

    int temp = number,
        row, col;
    
    temp /= 3;

    if (number % 3 != 0) {
        row = ceil(temp);
        col = (number % 3) - 1;
    } else {
        row = --temp;
        col = 2;
    }

    tic_tac_to[row][col] = (player == 1) ? 'X' : 'O';

    printf("\n\t **TicTacTo Board**\n");
    for (int i = 0; i < 3; i++) {
        printf("\t| ");

        for (int j = 0; j < 3; j++) {
            if (j != 2) printf("[ %c ] ", tic_tac_to[i][j]);
            else printf("[ %c ] |\n", tic_tac_to[i][j]);
        }
    }
}

bool is_exist_number(int number) {

    for (int i = 0; i < 9; i++) {
        if (number == players_input[i]) {
            tic_tac_to_board(0, 0);
            printf("\nOops :(, your number is already exist.\n");
            return true;
        }
    }

    return false;
}

bool validate_input_range(int number) {

    if (number < 1 || number > 9) {
        tic_tac_to_board(0, 0);
        printf("\n__Your number %d is not valid! Please input a valid number__\n", number);
       return false;
    }

    return true;
}

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

bool is_winner(int player) {

    if (found_match(player)) return true;

    return false;
}

void main() {
    int player_one_input,
        player_two_input,
        count = 9,
        count_draw = 0,
        continue_or_end;

    while (count) {

        if (count == 9) {
            for (int i = 0; i < 3; i++)  for (int j = 0; j < 3; j++) {
                    tic_tac_to[i][j] = ' ';
            }
            for (int i = 0; i < 9; i++) players_input[i] = 0;
            
            tic_tac_to_board(0, 0);

	        collect_players_name();
        }

        while (count) {
            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_one_name);
            scanf("%d", &player_one_input);

            if (!validate_input_range(player_one_input)) continue;

            if (is_exist_number(player_one_input)) continue;
            
            tic_tac_to_board(player_one_input, 1);

            if (count < 6) {
                if (is_winner(1)) {
                    printf("\n**WINNER WINNER CHICKEN DINNER - %s**\n", player_one_name);
                    count = 0; break;
                } else count_draw++;
            }

            players_input[player_one_input - 1] = player_one_input;
            count--; break;
        }

        while (count) {
            printf("\n\t__%s's Turn__\nInput a number from 1-9: ", player_two_name);
            scanf("%d", &player_two_input);

            if (!validate_input_range(player_two_input)) continue;

            if (is_exist_number(player_two_input)) continue;

            tic_tac_to_board(player_two_input, 2);

            if (count < 6) if (is_winner(2)) {
                printf("\n**WINNER WINNER CHICKEN DINNER - %s**\n", player_two_name);
                count = 0;
                break;
            } else count_draw++;

            players_input[player_two_input - 1] = player_two_input;
            count--;
            break;
        }

        while (!count) {
            count_draw == 5 && printf("\n\t____MATCH DRAW____\n");
            printf("\n\nEnter 1 for Continue or 0 for End:");

            scanf("%d", &continue_or_end);
            printf("\n");

            if (continue_or_end == 1 || continue_or_end == 0) if (!continue_or_end) {
                printf("\t___GAME OVER___\n");
                break;
            } else {
                count = 9;
                count_draw = 0;
            }
        }
    }
}