#include "display.h"

void displayMaze(int** maze,int xJ, int yJ,int iMax, int jMax){
	int t, l;
	system("clear");
	printf("Move with arrow key !\n\r\n\r");
	for(t=0;t<iMax;t++){
		printf("\n\r ");
		for(l=0;l<jMax;l++){
			if(xJ == t && yJ ==l)
				printf("\033[22;32m%s\033[0m","🧙");
			else
				if(maze[t][l]==1)
					printf("%s","▓▓");
				else if(maze[t][l]==0)
					printf("%s","  ");
				else
					printf("%02d",maze[t][l]);
		}
	}printf("\n\r\n\r");
}