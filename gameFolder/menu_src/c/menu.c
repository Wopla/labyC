#include "menu.h"

char *currentMenu;

void Actu(int fleche, int *caseA, int max){
	*caseA=traitement(fleche, *caseA, max);
	switch(fleche){
		case 1:*caseA-=1;break;
		case 2:*caseA+=1;break;
	}
}

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
		else if (key == 127){
            return DELETE;
        }
		/* CTRL+C */
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

int BrowseCreate(){
	int caseA=1,fleche=0,retour=-1;
	int keyboardInput;
	char saveName[17]="";
	char firstChar;
	char cToCat[2];
	cToCat[1]='\0';

	while(caseA!=-1){
		affichMenuCreate(caseA,saveName);
		keyboardInput = getKeyboardInput(&firstChar);
		switch(keyboardInput){
			case ARROWUP: 
				fleche=1;
				Actu(fleche,&caseA,2);
				break;
			case ARROWDOWN: 
				fleche=2;
				Actu(fleche,&caseA,2);
				break;
			case CRETURN:
				if(caseA == 3){
					retour = -1;
					caseA = -1;
				}else if(caseA == 2){
					if(strcmp(saveName,"")){
						settings.saveName = (char*) malloc(sizeof(char)*strlen(saveName));
						strcpy(settings.saveName,saveName);
						createSettings();
						if(loadedSave!= NULL)
							free(loadedSave);
						loadedSave = (char*) malloc(sizeof(char)*strlen(saveName));
						strcpy(loadedSave,saveName);
						system("./generator");
						retour = 0;
						caseA = -1;
					}
				}
				break;
			case ALPHABET:
				if(caseA == 1){
					if(strlen(saveName)<16){
						cToCat[0]=firstChar;
						strcat(saveName,cToCat);
					}
				}
				break;
			case NUMBER:
				if(caseA == 1){
					if(strlen(saveName)<16){
						cToCat[0]=firstChar;
						strcat(saveName,cToCat);
					}
				}
				break;
			case SPACE:
				if(caseA == 1){
					if(strlen(saveName)<16){
						cToCat[0]=firstChar;
						strcat(saveName,cToCat);
					}
				}
				break;
			case DELETE:
				if(caseA == 1)
					if(strlen(saveName)>0)
						saveName[strlen(saveName)-1]='\0';
				break;
			case -1:
				retour = -1;
				caseA = -1;
			break;
		}
	}
	return retour;
}

int BrowseSave(int createOption){
	int caseA=1,fleche=0,retour=-1;
	int max,max2;
	int refresh=0;
	int keyboardInput;
	char **menuNameList;
	char firstChar;
	struct dirent **list;
	int i;
	max=0;
	list =getSavesList(&max);
	max2=max;
	if(createOption==1)
		max2++;
	if(max2>0){
		menuNameList = (char**)malloc(sizeof(char*)*max2);
		for(i=max2-max;i<max2;i++){
			menuNameList[i] = (char*)malloc(sizeof(char)*strlen(list[i-(max2-max)]->d_name));
			strcpy(menuNameList[i],list[i-(max2-max)]->d_name);
			if(strlen(menuNameList[i])>4)
				menuNameList[i][strlen(menuNameList[i])-4]='\0';
		}
	}
	if(createOption==1){
		menuNameList[0] = (char*)malloc(sizeof(char)*16);
		strcpy(menuNameList[0],"create new save");
	}

	while(caseA!=-1){
		if(refresh!=0){
			refresh=0;
			list =getSavesList(&max);
			max2=max;
			menuNameList = (char**)malloc(sizeof(char*)*max2);
			for(i=0;i<max;i++){
				menuNameList[i] = (char*)malloc(sizeof(char)*strlen(list[i]->d_name));
				strcpy(menuNameList[i],list[i]->d_name);
				if(strlen(menuNameList[i])>4)
					menuNameList[i][strlen(menuNameList[i])-4]='\0';
			}
		}
		affichMenu(caseA, max2, menuNameList,"load");
		keyboardInput = getKeyboardInput(&firstChar);
		switch(keyboardInput){
			case ARROWUP: 
				fleche=1;
				Actu(fleche,&caseA,max2);
				break;
			case ARROWDOWN: 
				fleche=2;
				Actu(fleche,&caseA,max2);
				break;
			case CRETURN:
				/* if previous/exit has been choosed */
				if(caseA == max2+1){
					retour = -1;
					caseA = -1;
				}else {
					if(max != max2){
						/* Create selected */
						if(caseA == 1){
							retour = BrowseCreate();
							if(retour==0)
								caseA = -1;
						}else{
							settings.saveName  = (char*) malloc(sizeof(char)*strlen(menuNameList[caseA-1]));
							strcpy(settings.saveName ,menuNameList[caseA-1]);
							createSettings();
							loadedSave = (char*) malloc(sizeof(char)*strlen(menuNameList[caseA-1]));
							strcpy(loadedSave,menuNameList[caseA-1]);
							system("./generator");
							retour = 0;
							caseA = -1;
						}
					}else{
						if(createOption==2){
							if(loadedSave!=NULL)
								if(!strcmp(loadedSave,menuNameList[caseA-1]))
									loadedSave=NULL;
							refresh=1;
							deleteFile(menuNameList[caseA-1]);
						}else{
							if(loadedSave!= NULL)
								free(loadedSave);
							loadedSave = (char*) malloc(sizeof(char)*strlen(menuNameList[caseA-1]));
							strcpy(loadedSave,menuNameList[caseA-1]);
							retour = -1;
							caseA = -1;
						}
					}
				}
				break;
			case -1:
				retour = -1;
				caseA = -1;
			break;
		}
	}
	if(max2>0){
		printf("crash AVANT FREE ! \r\n");
		for(i=0;i<max2;i++){
			printf("crash %d\r\n",i);
			free(menuNameList[i]);
		}
		printf("crash APRES FREE ! \r\n");
		free(menuNameList);
	}

	return retour;
}

int BrowseGen(){
	int caseA=1,fleche=0,retour=-1;
	int i=21,j=21;
	int playMode=0;
	int keyboardInput;
	char firstChar;

	while(caseA!=-1){
		affichMenuGen(caseA,i,j,playMode);
		keyboardInput = getKeyboardInput(&firstChar);
		switch(keyboardInput){
			case ARROWUP: 
				fleche=1;
				ActuGen(fleche,&caseA,6,&i,&j,&playMode);
				break;
			case ARROWDOWN: 
				fleche=2;
				ActuGen(fleche,&caseA,6,&i,&j,&playMode);
				break;
			case ARROWRIGHT: 
				fleche=3;
				ActuGen(fleche,&caseA,6,&i,&j,&playMode);
				break;
			case ARROWLEFT: 
				fleche=4;
				ActuGen(fleche,&caseA,6,&i,&j,&playMode);
				break;
			case CRETURN:
			/* if previous/exit has been choosed */
				if(caseA == 7){
					retour = 0;
					caseA = -1;
				}else if(caseA == 6){
					settings.i = i;
					settings.j = j;
					settings.difficulty = playMode;
					retour = BrowseSave(1);
					if(retour == 0)
						caseA = -1;
				}
				break;
			case -1:
				retour = -1;
				caseA = -1;
			break;
		}
	}
	return retour;
}

int customCommandExec(char *commandName){
	int retour = 0;
	int size;
	char *commandBuffer;
    if(!strcmp(commandName,"play")){
		if(loadedSave != NULL){
			size = (10+strlen(loadedSave));
			commandBuffer=(char*)malloc(sizeof(char)*size);
			snprintf(commandBuffer, size, "./play \"%s\"",loadedSave);
			system(commandBuffer);
			free(commandBuffer);
		}
    }
	else if(!strcmp(commandName,"load")){
		retour = BrowseSave(0);
    }
	else if(!strcmp(commandName,"delete")){
        retour=BrowseSave(2);
    }
	else if(commandName[0]=='g'){
        switch(commandName[2]){
            case '0' : retour = BrowseGen();
                break;
        }
    }
	/* cursoff(); */
	return retour;
}

int BrowseMenu(char *selectedMenu, char *menuName){
	int caseA=1,fleche=0,retour=-1;
	int max;
    char firstChar;
	int keyboardInput;
	int tmpLenght;
	int isPrevious;
	char **menuNameList;
	char *tmp;
	int i;
	menu_item* currentMenu;
	currentMenu = getMenu(selectedMenu,&max);

	if(max>0){
		menuNameList = malloc(sizeof(char*)*max);
		for(i=0;i<max;i++)
			menuNameList[i]=currentMenu[i].menu_name;
	}

	while(caseA!=-1){
		affichMenu(caseA, max, menuNameList,menuName);
		keyboardInput = getKeyboardInput(&firstChar);
		switch(keyboardInput){
			case ARROWUP: 
				fleche=1;
				Actu(fleche,&caseA,max);
				break;
			case ARROWDOWN: 
				fleche=2;
				Actu(fleche,&caseA,max);
				break;
			case CRETURN:
			/* if previous/exit has been choosed */
				if(caseA == max+1){
					retour = 0;
					caseA = -1;
				}else{
					tmpLenght = strlen(currentMenu[caseA-1].menu_direction);
					if(tmpLenght>=4){
						tmp=currentMenu[caseA-1].menu_direction;
						if(tmp[tmpLenght-4] == '.' && tmp[tmpLenght-3] == 'c' && tmp[tmpLenght-2] == 's' && tmp[tmpLenght-1] == 'v'){
							isPrevious = BrowseMenu(currentMenu[caseA-1].menu_direction,currentMenu[caseA-1].menu_name);
							if(strcmp(menuName,"main")!=0)
								isPrevious == -1 ? (caseA=-1) : (caseA=1);
							else
								caseA=1;
						}
						else{
							retour = customCommandExec(currentMenu[caseA-1].menu_direction);
							if(retour != 0)
								caseA = -1;
						}
					}else{
						retour = customCommandExec(currentMenu[caseA-1].menu_direction);
						if(retour != 0)
								caseA = -1;
					}
				}
				break;
			case -1:
				return -1;
			break;
		}
	}

	free_menuList(currentMenu,max);
	return retour;
}