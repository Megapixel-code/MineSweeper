extern void menu(){
  int end=0;
  int choice=-1;
  int next=-1;
  while(end!=1){
    while(choice!=0 || choice!=1 || choice!=2){
      printf(" Faire un affichage joli");
      scanf(" %d",&choice);
      clearBuffer();
    }
    if(choice == 0){
      while(next!=1){

        /*

        L'utilisateur choisit les dimensions de la map et le nombre de bombes

        */
        
        int difficulty = -1;
        while (!(difficulty == 0 || difficulty == 1)){
          printf("\e[1;1H\e[2J");//clear console
          printf("Minesweeper Game\n\nChoose difficulty:\nEasy : 0 | Medium : 1 | Custom : 2\nYour answer : ");
          scanf("%d", &difficulty);
          clearBuffer();
        }
        int size, bombs;
        size = -1;
        bombs = -1;
        if (difficulty == 0){
          size = 9;
          bombs = 10;
        }
        else if (difficulty == 1){
          size = 16;
          bombs = 40;
        }
        else{
          while (size>30 || size<4){
            printf("\e[1;1H\e[2J");//clear console
            printf("Choose the size of the map (between 4 and 30) : ");
            scanf("%d", &size);
            clearBuffer();
          }
          while (bombs>size*size-9 || bombs<0){
            printf("\e[1;1H\e[2J");//clear console
            printf("Choose the number of bombs (between 0 and %d) : ",size*size-9);
            scanf("%d", &bombs);
            clearBuffer();
          }
        }

        /*

        L'utilisateur choisit le mode de jeu (avec triche ou non)

        */

        int gameMod=-1;
        while (gameMod !=0 || gameMod !=1){
            printf("\e[1;1H\e[2J");//clear console
            printf("Choose the gamemod (0 for classic and 1 for cheatmod): ");
            scanf("%d", &gameMod);
            clearBuffer();
        }
        
        /*

        Initialisation de la Map

        */
        
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
        
        /*

        initialisation d'un chronomètre

        */

        clock_t debut, fin ;
        long clk_tck = CLOCKS_PER_SEC ;
        double difference ;
        
        /*

        Place au Gaming !!!

        */

        int result;
        debut=clock();
        result = play(size,bombs,uMap,bMap,gameMod);
        fin=clock() ;
        difference = (double)(fin-debut)/(double)clk_tck ;
        if(result == 0){
          printf("You lose");
        }
        else{
          printf("You win, votre score est : %.3f",difference);
        }
        
        /*

        Restart or not a game

        */
        
        next=-1;
        while(!(next == 0 || next == 1)){
          printf("Do you want to play again?\n0 : No   1 : Yes\nYour answer : ");
          scanf(" %d", &next);
          clearBuffer();
        }
      }
    }
    else if(choice == 1){
      
    }
    else{
      end=1;
    }
    choice=-1;
  }
}

//menu (jouer => choix difficulté / retour, choix quitter, options => triche?, scores) faits 1/2
//debut jeux (cree les maps et premier coup) faits
//jeu (appeler play) faits
//affichage win lose + rejouer faits
//Timer + enregistre le score + affiche meilleurs score


int play(int size, int nBombs, int uMap[][size], int bMap[][size], int gameMod){
  //function that plays the game once the game started
  //size : int of the size of the map
  //nBomb : int of the number of bombs 
  //uMap : 2d array of int of the user map empty (see begining of main)
  //bMap : 2d array of int of the bomb map empty (see begining of main)
  //gameMod : int 1 if the auto-discover is on (see begining of main.c), 0 if desactivated
  //return int 0 if the user lost and 1 if the user won
}