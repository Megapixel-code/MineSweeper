#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define BOMBS 10
//DO NOT USE IN FUNCTIONS

//bombMap is the map with:
//bomb emplacement marked as -3
//and 0 when there is nothing

//userMap is the map that the user see with:
// 0 to revelated cells with no bombs
//-1 to the unrevealed cells
//-2 to your flags
//-3 to bombs that you touched


void display(int size, int uMap[size][size]){   //display of the map that the user can see
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
      if(uMap[y][x]==0){
        printf("~ | "); //revelated cells with no bombs
      }
      else if(uMap[y][x]==-1){
        printf("  | "); //unrevealed cells
      }
      else if(uMap[y][x]==-2){
        printf("X | "); //flags
      }
      else if(uMap[y][x]==-3){
        printf("# | "); //bombs touched
      }
      else{
        printf("%d | ", uMap[y][x]); //number of bombs around
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


void create_map(int *bMap, int size, int nBomb, int click_emplacement[2]){//to create the bombs emplacements 
  //bMap is the bomb map empty
  //size is the size of the map
  //nBomb is the number of bombs 
  //click_emplacement is a array with the coordinates of the user first click
  srand(time(NULL));
  int bombGenerated = 0;
  *((bMap+click_emplacement[1]*size)+click_emplacement[0]) = -3;//place a temporary bomb at the user click emplacement
  while(bombGenerated != nBomb){
    int x = rand()%size;
    int y = rand()%size;
    if (*((bMap+y*size)+x) == 0){
      *((bMap+y*size)+x) = -3;
      bombGenerated ++;
      }
  }
  *((bMap+click_emplacement[1]*size)+click_emplacement[0]) = 0;//remove the temporary bomb
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
  int u_click[2] = {0, 0};
  create_map(bombMap, SIZE, BOMBS, u_click);
	display(SIZE, bombMap);
	return 0;
}
