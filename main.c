#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "display_function.h"
#include "init_functions.h"
#include "run_functions.h"
#include "scores_functions.h"
#include "game_functions.h"


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

//auto-discover mod : if you click on a discovered case, discover the cells around where you clicked if there is the same amount of 
//                    flags than bombs around the cell, if you missplaced a flag you may lose


int main(){
  menu();
  return 0;
}