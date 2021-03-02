#include <stdio.h>

//* Get input names from user__________________
void collect_players_name(char *player_one_name, char *player_two_name) {
   printf("\nInput player one name: ");
   scanf("%s[^\n]", player_one_name);

   printf("Input player two name: ");
   scanf("%s[^\n]", player_two_name);
}
