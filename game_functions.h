int play(int size, int uMap[][size], int bMap[][size], int gameMod){
  //function that plays the game once the game started
  //size : int of the size of the map
  //uMap : 2d array of int of the user map empty (see begining of main)
  //bMap : 2d array of int of the bomb map empty (see begining of main)
  //gameMod : int 1 if the auto-discover is on (see begining of main.c), 0 if desactivated
  //return int 0 if the user lost and 1 if the user won
  
  while(check(size, uMap) == -1){
    char letter;
    int number;
    int discover_or_flag = -1;
    while(!(discover_or_flag == 0 || discover_or_flag == 1)){
      display(size, uMap);
      printf("\n\nWhat do you want to do : \n\n0 : discover a emplacement    1 : place/remove a flag\n\nYour answer : ");
      scanf(" %d", &discover_or_flag);
      clearBuffer();
    }

    //user want to discover a case
    if (discover_or_flag == 0){
      letter = -1;
      number = -1;
      while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
        display(size, uMap);
        printf("\nChoose your move (e.g. : A1, K4, ...) : ");
        scanf(" %c%d", &letter, &number);
        clearBuffer();
      }
      int move[2] = {letter - 65, number - 1};
      discover(size, bMap, uMap, move, gameMod);
    }
    //user want to place or remove a flag somewhere
    else {
      letter = -1;
      number = -1;
      while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
        display(size, uMap);
        printf("\nChoose the case you want to flag (e.g. : A1, K4, ...) : ");
        scanf(" %c%d", &letter, &number);
        clearBuffer();
      }
      int move[2] = {letter - 65, number - 1};
      //place flag if there is undiscovered cell else if there is alerady a flag place undiscovered terrain back
      if (uMap[move[1]][move[0]] == -1){
        uMap[move[1]][move[0]] = -2;
      }
      else if(uMap[move[1]][move[0]] == -2){
        uMap[move[1]][move[0]] = -1;
      }
    }
  }
  return check(size, uMap);
}


extern int ask(int a, int b, char question[]){
  int answer=-1;
  while(!(answer >= a && answer <= b)){
    printf("\e[1;1H\e[2J");//clear console
    printf("%s", question);
    printf("\n\nYour answer : ");
    scanf(" %d", &answer);
    clearBuffer();
  }
  return answer;
}


extern void first_move(int size, int bMap[][size], int uMap[][size], int nBombs, int gameMod){
  for (int y = 0; y < size; y++){
    for (int x = 0; x < size; x++){
      uMap[y][x] = -1;
    }
  }

  int number = -1;
  char letter = -1;
  display(size, uMap);//display empty map
  while (letter - 65 < 0 || letter - 65 >= size || number - 1 < 0 || number - 1 >= size){
    display(size, uMap);
    printf("Choose your first move (e.g. : A1, K4, ...) : ");
    scanf(" %c%d", &letter, &number);
    clearBuffer();
  }
  int posFirstMove[2] = {letter - 65, number - 1};
  create_map(size, bMap, nBombs, posFirstMove);
  discover(size, bMap, uMap, posFirstMove, gameMod);
}


extern void menu(){
  char question[1000];
  int answer;

  while (answer != 3){
    strcpy(question, "====================  Welcome to MineSweeper!  ====================\n\n\nPlay : 0    Look at the best scores : 1    Options : 2    Leave : 3");
    answer = ask(0, 3, question);

    //---------------------------user want to play
    if (answer == 0){
      strcpy(question, "==============================  Please choose difficulty!  ==============================\n\n\nEasy (9x9 and 10 bombs) : 0    Hard (16x16 and 40 bombs) : 1    Custom : 2    Go back : 3");
      answer = ask(0, 3, question);
      //if the user dont want to go back
      if (answer != 3){
        int size;
        int nBombs;
        //if difficulty is Easy
        if (answer == 0){
          size = 9;
          nBombs = 10;
        }
        //if difficulty is Hard
        else if (answer == 1){
          size = 16;
          nBombs = 40;
        }
        //if difficulty is Custom
        else{
          strcpy(question, "====  Please choose the size of the map (between 4 and 30)  ====\n\n");
          size = ask(4, 30, question);
          
          snprintf(question, 1000, "====  Please choose the number of bombs (between 0 and %d)  ====\n\n", ((size * size) - 9));
          nBombs = ask(0, ((size * size) - 9), question);
        }
        int bombMap[size][size];
        int userMap[size][size];

        //set the game
        int gameMod = get_mod();
        first_move(size, bombMap, userMap, nBombs, gameMod);

        //set timer
        struct timeval  begin, end;
        gettimeofday(&begin, NULL);
        
        //lunch the game
        int win = play(size, userMap, bombMap, gameMod);

        //get the time elapsed during the solving
        gettimeofday(&end, NULL);
        int time = (double)(end.tv_sec - begin.tv_sec);
        
        if (win && ((size == 9 && nBombs == 10) || (size == 16 && nBombs == 40))){
          //win message
          snprintf(question, 1000, "========  You won in %d seconds!  ========\n", time);
          strcat(question, "=====  Do you want to save your time?  =====\n\n\nYes : 0    No : 1");
          answer = ask(0, 1, question);
          //if user want to save
          if (answer == 0){
            char name[30];
            strcpy(name, "*");
            while (strchr(name, '*') != NULL){
              printf("\e[1;1H\e[2J");//clear console
              printf("=============================  Save score  =============================");
              printf("\n\nEnter your name (no * and no space in the name, max 30 char) : ");
              scanf(" %s", name);
            }
            add_score(size, time, name);
          }
        }
        else if (win){
          //win custom message
          display(size, userMap);
          char message[100];
          strcpy(message, "\n");
          for (int i = 0; i < (size-2)/2; i++){
            strcat(message, "====");
          }
          strcat(message, "  You won!  ");
          for (int i = 0; i < (size-2)/2; i++){
            strcat(message, "====");
          }
          strcat(message, "\n");
          printf("%s", message);
          printf("\n\npress enter to continue...");
          char a;
          scanf("%c", &a);
        }
        else{
          //lose message
          display(size, userMap);
          char message[100];
          strcpy(message, "\n==");
          for (int i = 0; i < (size-2)/2; i++){
            strcat(message, "====");
          }
          strcat(message, "  You lost  ");
          for (int i = 0; i < (size-2)/2; i++){
            strcat(message, "====");
          }
          strcat(message, "==\n");
          printf("%s", message);
          printf("\n\npress enter to continue...");
          char a;
          scanf("%c", &a);
        }
      }
    }

    //---------------------------user want to look at the best scores
    
    else if(answer == 1){
      display_scores();
      printf("\n\npress enter to continue...");
      char a;
      scanf("%c", &a);
    }

    //---------------------------user want to see options
    
    else if(answer == 2){
      strcpy(question, "=====  Settings  =====\n\n\nActivate auto-discover mode : 0    Deactivate auto-discover mode : 1    Reset best scores : 2");
      answer = ask(0, 2, question);
      //user want to activate auto-discover mode
      if (answer == 0){
        FILE *file;
        file = fopen("settings.txt", "w");
        fputs("1", file);
        fclose(file);
      }
      //user want to deactivate auto-discover mode
      else if (answer == 1){
        FILE *file;
        file = fopen("settings.txt", "w");
        fputs("0", file);
        fclose(file);
      }
      //user want to reset all the scores saved
      else{
        strcpy(question, "Are you sure you want to do that? You will lose every score you saved.\n\n0 : Yes    1 : Return to menu");
        answer = ask(0, 1, question);
        if (answer == 0){
          reset_scores();
        }
      }
    }

    //---------------------------user want to quit the program

    else{
      printf("\e[1;1H\e[2J");//clear console
      printf("User has left the game\n");
      return;
    }
  }
}
