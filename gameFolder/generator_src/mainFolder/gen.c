#include "gen.h"

void gen(board game){
	int t,l;
	game->maze = (int**)malloc(sizeof(int*)*game->iMax);
	for(t=0;t<game->iMax;t++)
		game->maze[t]=(int*)malloc(sizeof(int)*game->jMax);

	for(t=0;t<game->iMax;t++){
		for(l=0;l<game->jMax;l++){
			game->maze[t][l] = 1;
		}
	}
	
	game->maze[1][1] = 0;
	/* carveDaMaze(game->maze,1,1,game->iMax,game->jMax); */
	randomFuse(game->maze, game->iMax, game->jMax);
	game->maze[0][1] = 0;
	game->maze[game->iMax-1][game->jMax-2] = 0;
	game->p.x=0;
	game->p.y=1;
}

void freeGame(board game){
	int t;
	for(t=0;t<game->iMax;t++)
		free(game->maze[t]);
	free(game->maze);
}

int main(){
	time_t rT;
	genSettings genS;
	board game;
	srand((unsigned) time(&rT));
	genS = malloc(sizeof(struct genSettings_s));
	game = malloc(sizeof(struct boardS));
	if(loadGeneratorSettings(genS)!=0){
		printf("echec du chargement des settings !\n");
		free(genS);
		free(game);
		return 0;
	}
	else{
		game->iMax = (genS->i%2==0) ? (genS->i+1) : (genS->i);
		game->jMax = (genS->j%2==0) ? (genS->j+1) : (genS->j);
		gen(game);
		save(game, genS->saveName);

		printf("SUCCESS ! du chargement des settings ! :\n %s\n %d\n %d\n %d\n",genS->saveName, genS->i, genS->j, genS->difficulty);
	}
	freeGame(game);
	free(game);
	free(genS->saveName);
	free(genS);

	return 0;
}