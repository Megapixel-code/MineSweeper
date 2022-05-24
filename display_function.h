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
