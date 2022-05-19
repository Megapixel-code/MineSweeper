extern void clearBuffer() {
	char c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}


extern int bomb_count(int size, int map[][size], int clickEmplacement[2], int n){
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


extern int check(int size, int uMap[][size]){
  //function that determine if the user lost
  //size : int of the size of the map
  //uMap : 2d array of int of the user map (see begining of the program)
  //return a int -1 if the user did not lost, 0 if the user lost, 1 if the user won.

  int win = 1;
  for (int y = 0; y < size; y++){
    for (int x = 0; x < size; x++){
      if (uMap[y][x] == -3){
        return 0;
      }
      if (uMap[y][x] == -1){
        win = -1;
      }
    }
  }
  return win;
}
