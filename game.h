extern void create_map(int size, int bMap[][size], int nBomb, int clickEmplacement[2]){
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


extern void discover(int size, int bMap[][size], int uMap[][size], int clickEmplacement[2]){
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
    int nFlags = bomb_count(size, uMap, clickEmplacement, -2);
    if (nFlags >= uMap[clickEmplacement[1]][clickEmplacement[0]]){
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
