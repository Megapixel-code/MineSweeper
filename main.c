#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define BOMBS 10

//bombMap is the map with:
//bomb emplacement marked as -3
//and 0 when there is nothing
//1, 2, 3.. when there is 1, 2, 3.. bombs around

//userMap is the map that the user see with:
// 0 to revelated cells with no bombs
//-1 to the unrevealed cells
//-2 to your flags
//-3 to bombs that you touched


void display(int size, int Map[size][size]){  
  //function that display the map passed in the argument
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
      if(Map[y][x]==0){
        printf("~ | "); //revelated cells with no bombs
      }
      else if(Map[y][x]==-1){
        printf("  | "); //unrevealed cells
      }
      else if(Map[y][x]==-2){
        printf("X | "); //flags
      }
      else if(Map[y][x]==-3){
        printf("# | "); //bombs touched
      }
      else{
        printf("%d | ", Map[y][x]); //number of bombs around
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


void create_map(int size, int bMap[][size], int nBomb, int clickEmplacement[2]){
  //function that create the bombs emplacements on a empty map
  //bMap is the bomb map empty
  //size is the size of the map
  //nBomb is the number of bombs 
  //clickEmplacement is a array with the coordinates of the user first click
  srand(time(NULL));
  int bombGenerated = 0;
  bMap[clickEmplacement[1]][clickEmplacement[0]] = -3;//place a temporary bomb at the user click emplacement

  //add bombs until there is nBomb in the 2d array
  while(bombGenerated != nBomb){
    int x = rand()%size;
    int y = rand()%size;
    if (bMap[y][x] == 0){
      bMap[y][x] = -3;
      bombGenerated ++;
      }
  }
  
  bMap[clickEmplacement[1]][clickEmplacement[0]] = 0;//remove the temporary bomb

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


int bomb_count(int size, int uMap[][size], int clickEmplacement[2]){
  //function that counts the number of bombs around 
  int tot = 0;
  for (int j = -1; j < 2; j++){
    for (int i = -1; i < 2; i++){
      if (clickEmplacement[0] + i >= 0 && clickEmplacement[0] + i < size && clickEmplacement[1] + j >= 0 && clickEmplacement[1] + j < size){//if the case is inside the map
        if (uMap[clickEmplacement[1] + j][clickEmplacement[0] + i] == -2){//and is a flag add 1
          tot++;
        }
      }
    }
  }
  return tot;
}


void discover(int size, int bMap[][size], int uMap[][size], int clickEmplacement[2]){
  //function that discover the cases around and where you clicked

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
    int nBombs = bomb_count(size, uMap, clickEmplacement);
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


int main(){
	int bombMap[SIZE][SIZE];
  int userMap[SIZE][SIZE];

  for (int y = 0; y < SIZE; y++){
    for (int x = 0; x < SIZE; x++){
      userMap[y][x] = -1;
      bombMap[y][x] = 0;
    }
  }
  int userClick[2] = {0, 0};
  create_map(SIZE, bombMap, BOMBS, userClick);

  //tests

  
  
	display(SIZE, userMap);
  
	discover(SIZE, bombMap, userMap, userClick);

  printf("\n\n");
  display(SIZE, userMap);
  
  int x, y;
  scanf("%d", &x);
  scanf("%d", &y);
  userMap[y][x] = -2;
  
  printf("\n\n");
  display(SIZE, userMap);

  scanf("%d", &x);
  scanf("%d", &y);
  int userClick2[2] = {x, y};
  discover(SIZE, bombMap, userMap, userClick2);
  
  printf("\n\n");
  display(SIZE, userMap);
  
  return 0;
}
