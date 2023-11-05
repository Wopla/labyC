#include "dataExtractor.h"

int charge(board* game, char* saveName){
    char chem[CHAR_MAX] = "../saves/";
	int t;
	FILE* file;
	strcat(chem,saveName);
	strcat(chem,".cfg");
    
	file = fopen(chem, "r");
	if(file==NULL){
		printf("Error with the saving the file\n");
		return -1;
	}
	else{
		fread(&game->p, sizeof(player), 1, file);
		fread(&game->iMax, sizeof(int), 1, file);
		fread(&game->jMax, sizeof(int), 1, file);
		game->maze = (int**)malloc(sizeof(int*)*game->iMax);
		for(t=0;t<game->iMax;t++){
			game->maze[t] = (int*)malloc(sizeof(int)*game->jMax);
			fread(game->maze[t], sizeof(int), game->jMax, file);
		}
			
		fclose(file);
	}
	return 0;
}