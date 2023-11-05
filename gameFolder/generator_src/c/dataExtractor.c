#include "dataExtractor.h"

static hashMap lookuptable[5] = {
    { "saveName", SAVEN }, { "iSize", ISIZE }, { "jSize", JSIZE }, { "labyGamemode", GAMEMODE }
};

#define NKEYS (sizeof(lookuptable)/sizeof(hashMap))

int countLine(FILE* file){
	int nbLine=1;
	char c;
	while (!feof(file)){
		c = fgetc(file);
		if(c=='\n')
			nbLine++;
	}
	return nbLine;
}

char* getfield(char* line, int n){
    char* r;
    for (r = strtok(line, ":"); r && *r; r = strtok(NULL, ":\n")){
        if (!--n)
            return r;
    }
    return NULL;
}

void save(board game, char* saveName){
	char chem[CHAR_MAX] = "../saves/";
	FILE* file;
	int t;
	strcat(chem,saveName);
	strcat(chem,".cfg");
	file = fopen(chem, "w");
	if(file==NULL){
		printf("Error with the saving the file\n");
	}
	else{
		printf("Read5 %d : %d, 0.0 : %d\n",game->p.x,game->p.y,game->maze[1][1]);
		fwrite(&game->p, sizeof(player), 1, file);
		fwrite(&game->iMax, sizeof(int), 1, file);
		fwrite(&game->jMax, sizeof(int), 1, file);
		for(t=0;t<game->iMax;t++)
			fwrite(game->maze[t], sizeof(int), game->jMax, file);
		printf("Read5 %d : %d, 0.0 : %d\n",game->p.x,game->p.y,game->maze[1][1]);

		fclose(file);
	}
}

int digit2int(char * input){
	return (int) strtol(input,NULL,10);
}

int implementGenSettings(genSettings genS, FILE *file){
	char *tmp;
	char *value;
	char *stringSettingsValue;
	char line[1024];

	fgets(line, 1024, file);
	tmp = (char*) malloc(sizeof(char)*strlen(line));
	strcpy(tmp,line);
	
	if(strcmp(tmp, "\n")!=0){
		value = getfield(tmp,2);
		stringSettingsValue = getfield(tmp,1);
		if(stringSettingsValue != NULL && value != NULL){
			switch (keyfromstring(stringSettingsValue)) {
				case SAVEN:
					genS->saveName = (char*) malloc(sizeof(char)*strlen(value));
					strcpy(genS->saveName,value);
					break;
				case ISIZE:
					genS->i=digit2int(value);
					if(genS->i>99 || genS->i<5){
						free(tmp);
						return -1;
					}
					break;
				case JSIZE:
					genS->j=digit2int(value);
					if(genS->j>99 || genS->j<5){
						free(tmp);
						return -1;
					}
					break;
				case GAMEMODE:
					genS->difficulty=digit2int(value);
					if(genS->difficulty>2 || genS->difficulty<0){
						free(tmp);
						return -1;
					}
					break;
				case BADKEY: 
					free(tmp);
					return -1;
			}
		}else{
			free(tmp);
			return -1;
		}
	}
	free(tmp);
	return 0;
}

int loadGeneratorSettings(genSettings genS){
	int nbLine;
	int t;
	FILE* file;
	file = fopen("../settings/generator.txt","r");
	if(file==NULL){
		return -1;
	}else{
		nbLine = countLine(file);
		rewind(file);
		if(nbLine<4)
			return -1;
		else{
			for(t=0; t<5;t++){
				if(implementGenSettings(genS, file)!=0){
					fclose(file);
					return -1;
				}
			}
		}
	}
	fclose(file);
	return 0;
}

int keyfromstring(char *key){
    int i;
	int nkeys;
	nkeys = (int) NKEYS;
    for (i=0; i < nkeys; i++) {
        hashMap sym = lookuptable[i];
        if (strcmp(sym.key, key) == 0)
            return sym.val;
    }
    return BADKEY;
}