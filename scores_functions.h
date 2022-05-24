void add_score(int size, int time, char name[]){
  //verify there is no * in name and no space and len name < 30 
  
  char fileName[20] = "";
  if (size == 9){
    strcpy(fileName, "scores9x9.txt");
  }
  else if (size == 16){
    strcpy(fileName, "scores16x16.txt");
  }
  else{
    printf("Wrong size, cant save...");
    exit(1);
  }
  
  FILE *file;

  //reading the content of the scores
  file = fopen(fileName, "r");
  if (file == NULL){
    printf("Error opening file\n");
    exit(1);
  }
  
  char buffer[500];
  fgets(buffer, 500, file);
  
  int scores[10] = {0};
  char names[10][30];
  for (int i = 0; i < 10; i++){
    strcpy(names[i], "_");
  }

  {//using private variable that we dont want to acces later
    char iName[30];
    char iCharNum[10];
    char temp[2];
    temp[1] = '\0';
    int i = 0;
    for (int j = 0; j < 10; j++){
      strcpy(iName, "");
      for (i; buffer[i] != ' '; i++){
        temp[0] = buffer[i];
        strcat(iName, temp);
      }
      strcpy(names[j], iName);
      i++;
      strcpy(iCharNum, "");
      for (i; buffer[i] != '*'; i++){
        temp[0] = buffer[i];
        strcat(iCharNum, temp);
      }
      i++;
      
      //transform the iCharnum into int
      int power = 1;
      for (int i = 0; i < strlen(iCharNum) - 1; i++){
        power *= 10;
      }
      int iIntNum = 0;
      for (int x = 0; iCharNum[x] != '\0'; x++){
        iIntNum += (((int)(iCharNum[x])) - 48) * power;
        power /= 10;
      }
      scores[j] = iIntNum;
    }
  }
  fclose(file);

  //insert player in the scores if he has a good enough score
  if (scores[9] > time){
    return;
  }
  
  int place;
  for (int i = 0; scores[i] > time; i++){
    place = i + 1;
  }

  int timeTemp1 = time;
  int timeTemp2;
  char nameTemp1[30];
  char nameTemp2[30];
  strcpy(nameTemp1, name);
  for (int i = place; i < 10; i++){
    timeTemp2 = scores[i];
    scores[i] = timeTemp1;
    timeTemp1 = timeTemp2;
    strcpy(nameTemp2, names[i]);
    strcpy(names[i], nameTemp1);
    strcpy(nameTemp1, nameTemp2);
  }

  //writing to file  
  
  file = fopen(fileName, "w");
  char output[500] = "";
  char temp[40];
  for (int i = 0; i < 10; i++){
    strcpy(temp, "");
    sprintf(temp,"%s %d*", names[i], scores[i]);
    strcat(output, temp);
  }
  strcat(output, "\n");
  
  for (int i = 0; output[i] != '\n'; i++) {
    fputc(output[i], file);
  }
  fclose(file);
}



/* 

Utiliser fread avec un tableau(de chaine de caractere)  = dinguerie faut juste convertir des chaines de caractere en float/long faudra aussi faire un truc avec les \0 a priori = faire des tests


fprintf pour rentrer pseudo etc ça a l'air pas mal


ducoup a priori on met a la suite chaine de caractère + ptete séparer d'un espace 
mais en vrai meme pas normalement a la suite séparer des \0 c'est bon et ducoup on les releve toute, on prend les paires (pour prendre que les temps) et on les convertis en long, on trouve le plus petit et c'est l'highscore

ptete pour faire plus clean on met un \n dans les chaine de caractere mais faut trouver un moyen de l'enlever quand on convertit en long
*/