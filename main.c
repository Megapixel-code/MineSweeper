#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "init.h"
#include "game.h"


//bombMap is the map with:
//bomb emplacement marked as -3
//and 0 when there is nothing
//1, 2, 3... when there is 1, 2, 3... bombs around

//userMap is the map that the user see with:
// 1, 2, 3... to revelated cells with 1, 2, 3... bombs around
// 0 to revelated cells with no bomb
//-1 to the unrevealed cells
//-2 to your flags
//-3 to bombs that you touched


int play(){
  //choosing difficulty
  int difficulty = -1;
  while (!(difficulty == 0 || difficulty == 1)){
    printf("\e[1;1H\e[2J");//clear console
    printf("Minesweeper Game\n\nChoose difficulty:\nEasy : 0 | Medium : 1\nYour answer : ");
    scanf("%d", &difficulty);
    clearBuffer();
  }

  //initialize game 
  int size, bombs;
  if (difficulty == 0){
    size = 9;
    bombs = 10;
  }
  else if (difficulty == 1){
    size = 16;
    bombs = 40;
  }

  int bombMap[size][size];
  int userMap[size][size];

  for (int y = 0; y < size; y++){
    for (int x = 0; x < size; x++){
      userMap[y][x] = -1;
    }
  }

  int number = -1;
  char letter = -1;
  display(size, userMap);//display empty screen
  while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
    display(size, userMap);
    printf("Choose your first move (e.g. : A1, K4, ...) : ");
    scanf(" %c%d", &letter, &number);
    clearBuffer();
  }
  
  int first_move[2] = {letter - 65, number - 1};
  create_map(size, bombMap, bombs, first_move);
  discover(size, bombMap, userMap, first_move);

  while((check(size, userMap)) == -1){
    int discover_or_flag = -1;
    while(!(discover_or_flag == 0 || discover_or_flag == 1)){
      display(size, userMap);
      printf("What do you want to do : \n0 : discover a emplacement    1 : place/remove a flag\nYour answer : ");
      scanf(" %d", &discover_or_flag);
      clearBuffer();
    }

    if (discover_or_flag == 0){
      letter = -1;
      number = -1;
      while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
        display(size, userMap);
        printf("Choose your move (e.g. : A1, K4, ...) : ");
        scanf(" %c%d", &letter, &number);
        clearBuffer();
      }
      int move[2] = {letter - 65, number - 1};
      discover(size, bombMap, userMap, move);
    }
    else {
      letter = -1;
      number = -1;
      while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
        display(size, userMap);
        printf("Choose the case you want to flag (e.g. : A1, K4, ...) : ");
        scanf(" %c%d", &letter, &number);
        clearBuffer();
      }
      int move[2] = {letter - 65, number - 1};
      //place flag if there is undiscovered cell else if there is alerady a flag place undiscovered terrain back
      if (userMap[move[1]][move[0]] == -1){
        userMap[move[1]][move[0]] = -2;
      }
      else if(userMap[move[1]][move[0]] == -2){
        userMap[move[1]][move[0]] = -1;
      }
    }
  }

  if ((check(size, userMap)) == 0){
    display(size, userMap);//display the bomb that killed the player
    printf("You lost! ¯\\_(ツ)_/¯\n");
  }
  else{
    display(size, userMap);//display the map completed
    printf("you win!\n");
  }

  int play_again = -1;
  while(!(play_again == 0 || play_again == 1)){
    printf("Do you want to play again?\n0 : No   1 : Yes\nYour answer : ");
    scanf(" %d", &play_again);
    clearBuffer();
  }  
  return play_again;
}


int main(){
  
  while(play()){}
  return 0;
}

