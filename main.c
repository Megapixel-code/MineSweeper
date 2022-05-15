#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define BOMBS 10

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


void display(int size, int map[][size]){  
  //function that display the map passed in the argument
  //size : int of the size of the map
  //map : 2d array of int of the map that we want to display

  ////////////////////////////////////////////////////////////////////////////////////////////printf("\e[1;1H\e[2J");
  //first line with the letters 
	printf("    ");
	for (int i = 0; i<size; i++){
		printf(" %c  ", i+65);
	}
  //first line under the letters
  printf("\n    ");
    for (int i = 0; i < size; i++){
      printf("--- ");
    }
  printf("\n");

  //display of the numbers on the side
  for (int y = 0; y < size; y++){
    printf("%d ", y+1);  
    if (y+1 < 10){
      printf(" ");
    }
    printf("| ");

    //display inside of the tab
    for (int x = 0; x < size; x++){
      if(map[y][x]==0){
        printf("~ | "); //revelated cells with no bombs
      }
      else if(map[y][x]==-1){
        printf("  | "); //unrevealed cells
      }
      else if(map[y][x]==-2){
        printf("X | "); //flags
      }
      else if(map[y][x]==-3){
        printf("# | "); //bombs touched
      }
      else{
        printf("%d | ", map[y][x]); //number of bombs around
      }
    }

    //lines in between
    printf("\n    ");
    for (int i = 0; i < size; i++){
      printf("--- ");
    }
    printf("\n");
  }
}


int bomb_count(int size, int map[][size], int clickEmplacement[2], int n){
  //function that counts the number of element n around 
  //size : int of the size of the map
  //map : 2d array of int of the map we are searching in
  //clickEmplacement : array of int with 2 numbers with the coordinates of the case we are searching around
  //n : int of the element we are searching
  //return a int of the number of element n around
  
  int tot = 0;
  for (int j = -1; j < 2; j++){
    for (int i = -1; i < 2; i++){
      if (clickEmplacement[0] + i >= 0 && clickEmplacement[0] + i < size && clickEmplacement[1] + j >= 0 && clickEmplacement[1] + j < size){//if the case is inside the map
        if (map[clickEmplacement[1] + j][clickEmplacement[0] + i] == n){//and is a flag add 1
          tot++;
        }
      }
    }
  }
  return tot;
}


void create_map(int size, int bMap[][size], int nBomb, int clickEmplacement[2]){
  //function that create the bombs emplacements on a empty map
  //size : int of the size of the map
  //bMap : 2d array of int of the bomb map empty (see begining of the program)
  //nBomb : int of the number of bombs 
  //clickEmplacement : array of int with 2 numbers with the coordinates of the user first click

  srand(time(NULL));
  do{
    //fill the map with 0
    for (int y = 0; y < size; y++){
      for (int x = 0; x < size; x++){
        bMap[y][x] = 0;
      }
    }
    int bombGenerated = 0;
    //add bombs until there is nBomb in the 2d array
    while(bombGenerated != nBomb){
      int x = rand()%size;
      int y = rand()%size;
      if (bMap[y][x] == 0){
        bMap[y][x] = -3;
        bombGenerated ++;
      }
    }
  }while (bomb_count(size, bMap, clickEmplacement, -3) != 0);//verify that there is no bomb around the user first click
  

  //add the numbers
  for (int y = 0; y < size; y++){
    for (int x = 0; x < size; x++){
      if (bMap[y][x] == -3){
        //if there is a bomb at the emplacement increment the cases around by one unless the case incrementing is a bomb
        for (int j = -1; j < 2; j++){
          for (int i = -1; i < 2; i++){
            if (x + i >= 0 && x + i < size && y + j >= 0 && y + j < size && bMap[y + j][x + i] != -3){
              bMap[y + j][x + i] += 1;
            }
          }
        }
      }
    }
  }
}


void discover(int size, int bMap[][size], int uMap[][size], int clickEmplacement[2]){
  //function that discover the cases around and where you clicked
  //size : int of the size of the map
  //bMap : 2d array of int of the bomb map (see begining of the program)
  //uMap : 2d array of int of the user map (see begining of the program)
  //clickEmplacement : array of int with 2 numbers with the coordinates of the case we are dicovering

  //if its outside the map return
  if (clickEmplacement[0] < 0 || clickEmplacement[0] >= size || clickEmplacement[1] < 0 || clickEmplacement[1] >= size){
    return;
  }

  //if its undiscovered discover it
  if (uMap[clickEmplacement[1]][clickEmplacement[0]] == -1){
    uMap[clickEmplacement[1]][clickEmplacement[0]] = bMap[clickEmplacement[1]][clickEmplacement[0]];
  }

  //if all the cases around are discovered return
  int next = 1;
  for (int j = -1; j < 2; j++){
    for (int i = -1; i < 2; i++){
      if (clickEmplacement[0] + i >= 0 && clickEmplacement[0] + i < size && clickEmplacement[1] + j >= 0 && clickEmplacement[1] + j < size && uMap[clickEmplacement[1] + j][clickEmplacement[0] + i] == -1){
        next = 0;
      }
    }
  }
  if (next){
    return;
  }

  //else look at all the undiscovered cases around where you clicked if there is more or the 
  //same amounts of flags as bombs around the case
  if (uMap[clickEmplacement[1]][clickEmplacement[0]] >= 0){
    int nBombs = bomb_count(size, uMap, clickEmplacement, -2);
    if (nBombs >= uMap[clickEmplacement[1]][clickEmplacement[0]]){
      for (int j = -1; j < 2; j++){
        for (int i = -1; i < 2; i++){
          if (!(i == 0 && j == 0) && uMap[clickEmplacement[1] + j][clickEmplacement[0] + i] == -1){
            int temp[2];
            temp[0] = clickEmplacement[0] + i;
            temp[1] = clickEmplacement[1] + j;
            discover(size, bMap, uMap, temp);
          }
        }
      }
    }
  }
}


int game(int size, int uMap[][size]){
  //function that determine if the user lost
  //size : int of the size of the map
  //uMap : 2d array of int of the user map (see begining of the program)
  //return a int 0 if the user did not lost, -1 if the user lost, 1 if the user won.

  int win = 1;
  for (int y = 0; y < size; y++){
    for (int x = 0; x < size; x++){
      if (uMap[y][x] == -3){
        return -1;
      }
      if (uMap[y][x] != -1){
        win = 0;
      }
    }
  }
  return win;
}


int play(){
  //choosing difficulty
  int dificulty = -1;

  //printf("\e[1;1H\e[2J");//clear console
  printf("Minesweeper Game\n\nChoose dificulty:\nEasy : 0 | Medium : 1\nYour answer : ");
  scanf("%d", &dificulty);
  printf("\n\n");
  while (!(dificulty == 0 || dificulty == 1)){
    //printf("\e[1;1H\e[2J");
    printf("Wrong input\n");
    printf("Minesweeper Game\n\nChoose dificulty:\nEasy : 0 | Medium : 1\nYour answer : ");
    scanf("%d", &dificulty);
  }
  //printf("\e[1;1H\e[2J");

  //initialize game 
  int size, bombs;
  if (dificulty == 0){
    size = 9;
    bombs = 10;
  }
  else if (dificulty == 1){
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

  
  display(size, userMap);//display empty screen
  char letter;
  int number;
  printf("Choose your first move (e.g. : A1, B3, ...) : ");
  scanf("%c", &letter);
  
  printf("%c", letter);
  
  //printf("%d%d", x-65, y-1);
  
  return 0;
}


int main(){
	int bombMap[SIZE][SIZE];
  int userMap[SIZE][SIZE];

  for (int y = 0; y < SIZE; y++){
    for (int x = 0; x < SIZE; x++){
      userMap[y][x] = -1;
    }
  }
  int userClick[2] = {0, 0};
  

  while(play()){}
  
  return 0;
}
