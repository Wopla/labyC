#include <play.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int main(int argc, char **argv){
    board* game = malloc(sizeof(struct boardS));
	int hasMoved;
	if(argc==2){
		if(charge(game,argv[1])==0){

			displayMaze(game->maze,game->p.x,game->p.y,game->iMax,game->jMax);
			
			hasMoved=1;

			while(game->p.x!=game->iMax-1 || game->p.y!=game->jMax-2){
				gameTurn(game,&hasMoved);
				/* if the first value is esc, 27 or 1B or '\033'*/
			}
			displayMaze(game->maze,game->p.x,game->p.y,game->iMax,game->jMax);

			printf(" End of the game !!\n\r\n\r");
		}
	}
	return 0;
}