#include <stdio.h>
#define SIZE 9 //DO NOT USE IN FUNCTIONS

//BombMap is the map with only the bomb emplacement marked as -1
//and a numbers for the amont of bombs around

//userMap is the map that the user see with -1 to the unrevealed terrain


void display(int bMap[], int uMap[], int size){
	printf("   ");
	for (int i = 0; i<size; i++){
		printf("%c ", i+65);
	}
}


int main(){
	int bombMap[SIZE][SIZE];
	int userMap[SIZE][SIZE];
	display(bombMap, userMap, SIZE);
	return 0;
}
