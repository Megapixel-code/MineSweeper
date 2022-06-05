extern void display(int size, int map[][size]){  
  //function that display the map passed in the argument
  //size : int of the size of the map
  //map : 2d array of int of the map that we want to display

  printf("\e[1;1H\e[2J");
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
        printf("\x1B[36m");
        printf("X"); //flags
        printf("\x1B[0m");
        printf(" | "); 
      }
      else if(map[y][x]==-3){
        printf("\x1B[31m");
        printf("#"); //bombs touched
        printf("\x1B[0m");
        printf(" | "); 
      }
      else{
        printf("\x1B[33m");
        printf("%d", map[y][x]); //number of bombs around
        printf("\x1B[0m");
        printf(" | "); 
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


extern void display_scores(){
  //function that display all the scores
  //doesn't return anything
  FILE *scores9;
  FILE *scores16;

  //reading the content of the scores
  scores9 = fopen("scores9x9.txt", "r");
  scores16 = fopen("scores16x16.txt", "r");
  if (scores9 == NULL || scores16 == NULL){
    printf("Error opening file\n");
    exit(1);
  }
  
  char buffer9[500];
  char buffer16[500];
  fgets(buffer9, 500, scores9);
  fgets(buffer16, 500, scores16);

  fclose(scores9);
  fclose(scores16);
  
  int caret9 = 0;
  int caret16 = 0;
  int lineSize;
  printf("\e[1;1H\e[2J");
  printf("SCORES 9x9 :");
  for (int i = 0; i < 30; i++){
    printf(" ");
  }
  printf("SCORES 16x16 :\n\n");
  for (int i = 0; i < 10; i++){
    lineSize = 0;
    for (caret9; buffer9[caret9] != '*'; caret9++){
      printf("%c", buffer9[caret9]);
      lineSize++;
    }
    caret9++;
    
    printf("s");
    lineSize++;
    
    for (lineSize; lineSize < 42; lineSize++){
      printf(" ");
    }
    
    for (caret16; buffer16[caret16] != '*'; caret16++){
      printf("%c", buffer16[caret16]);
    }
    caret16++;
    printf("s\n");
  }
}