#include "game.h"


int getKeyboardInput(char *charTyped){
    char key;
	int stop;
	int selret;
    key=0;
	stop=0;
    while(stop<99){
        if (read(STDIN_FILENO, &key, 1) != 1){
            fprintf(stderr, "read error or EOF\n\r");
            return-1;
        }
		*charTyped = key;
        if (key == EOF_KEY){
            fprintf(stderr, "%d (control-D or EOF)\n\r", key);
            return -1;
        }
        else if (key == ESC_KEY){
            fd_set set;
            struct timeval timeout;
            FD_ZERO(&set);
            FD_SET(STDIN_FILENO, &set);
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;
            selret = select(1, &set, NULL, NULL, &timeout);
            if (selret == 1){
                if (getchar() == '['){
                    switch(getchar()) {
                        case 'A': return ARROWUP;
                            break;
                        case 'B': return ARROWDOWN;
                            break;
						case 'C': return ARROWRIGHT;
                            break;
						case 'D': return ARROWLEFT;
                    }
                }
            }
            else
				return ESC;
        }
		else if (key == '\r'){
            return CRETURN;
        }
		else if ((key>='a' && key<='z') || (key>='A' && key<='Z')){
            return ALPHABET;
        }
		else if (key>='0' && key<='9'){
            return NUMBER;
        }
		else if (key == ' '){
            return SPACE;
        }
		/* CTRL + C*/
        else if (key == 3){
			fprintf(stderr, "%d control-C pressed\n\r", key);
            return -1;
        }
		else{
			stop++;
		}
    }
    return -1;
}

void gameTurn(board* game,int *hasMoved){
	int keyboardInput;
	char firstGetChar;

	if(*hasMoved==1){
		displayMaze(game->maze,game->p.x,game->p.y,game->iMax,game->jMax);
		*hasMoved=0;
	}
	keyboardInput = getKeyboardInput(&firstGetChar);
	switch(keyboardInput){
		case ARROWUP:
			if(game->p.x-1!=-1)
				if(game->maze[game->p.x-1][game->p.y]==0){
					*hasMoved=1;
					game->p.x-=1;
				}
			break;
		case ARROWDOWN:
			if(game->p.x+1!=game->iMax)
				if(game->maze[game->p.x+1][game->p.y]==0){
					*hasMoved=1;
					game->p.x+=1;
				}
			break;
		case ARROWRIGHT:
			if(game->p.y+1!=game->jMax)
				if(game->maze[game->p.x][game->p.y+1]==0){
					*hasMoved=1;
					game->p.y+=1;
				}
			break;
		case ARROWLEFT:
			if(game->p.y-1!=-1)
				if(game->maze[game->p.x][game->p.y-1]==0){
					*hasMoved=1;
					game->p.y-=1;
				}
			break;
		case CRETURN:
			break;
		case ALPHABET:
			break;
		case NUMBER:
			break;
		case SPACE:
			break;
		case ESC:
			break;
		case -1:
			game->p.x =game->iMax-1;
			game->p.y =game->jMax-2;
		break;
	}
}