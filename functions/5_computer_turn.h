#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool isEmpty(int randNumber, char *board) {
   if (board[randNumber] != '*') return false;

   return true;
}

int computer(char *board) {
   srand(time(NULL));

   int random = rand() % 9 + 1,
      step = 1;

   while (!isEmpty(random, board)) {
      if (random == 9) step = -1;

      random += step;
   }

   return random;
}