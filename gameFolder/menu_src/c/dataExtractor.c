#include "dataExtractor.h"

genSettings settings;

int compareSize(const void *const A, const void *const B){
    return strcmp((*(struct dirent **) A)->d_name, (*(struct dirent **) B)->d_name);
}

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
    for (r = strtok(line, ","); r && *r; r = strtok(NULL, ",\n")){
        if (!--n)
            return r;
    }
    return NULL;
}

menu_item* getMenu(char *menuCSVName, int *max){
	char chem[CHAR_MAX] = "../menu_csv/";
	FILE* file;
	menu_item* menu;
	char line[1024];
	int t;
	char *tmp, *temp_menu_direction, *temp_menu_name, *menu_direction, *menu_name;
	strcat(chem,menuCSVName);
	file = fopen(chem, "r");
	if(file==NULL){
		printf("ERROR FILE DOES NOT EXIST\n\r");
		return NULL;
	}else{
		*max = countLine(file);
		rewind(file);
		menu = malloc(sizeof(menu_item)* *max);
		t=0;
		/* coupe tmp donc doit prendre indice orde decroissant*/
		while (fgets(line, 1024, file)){
			tmp = strdup(line);
			if(strcmp(tmp, "\n")!=0){
				temp_menu_direction = getfield(tmp,2);
				temp_menu_name = getfield(tmp,1);
				
				if(temp_menu_direction != NULL && temp_menu_name != NULL){
					menu_direction = strdup(temp_menu_direction);
					menu_name = strdup(temp_menu_name);
					menu[t].menu_direction = menu_direction;
					menu[t].menu_name = menu_name;
					t++;
				}
			}
			free(tmp);
		}
		fclose(file);
		*max = t;
		if(t==0)
			return NULL;
		else{
			menu = realloc(menu,sizeof(menu_item)* *max);
			return menu;
		}
	}
}

void createSettings(){
	char chem[CHAR_MAX] = "../settings/";
	FILE *file;
	strcat(chem,"generator.txt");
	file = fopen(chem,"w");
	if(file != NULL){
		fprintf(file,"saveName:%s\n",settings.saveName);
		fprintf(file,"iSize:%d\n",settings.i);
		fprintf(file,"jSize:%d\n",settings.j);
		fprintf(file,"labyGamemode:%d",settings.difficulty);
	}
	fclose(file);
}

void deleteFile(char *fileToDelete){
	char chem[CHAR_MAX] = "../saves/";
	strcat(chem,fileToDelete);
	strcat(chem,".cfg");
	if(remove(chem)!=0){
		printf("Error while deleting %s!\r\n",fileToDelete);
	}
}

void afficheInfo(char *sFile){
	FILE *file;
 	char chemin[CHAR_MAX] = "../settings/";
 	char buffer[CHAR_MAX];
 	strcat(chemin,sFile);
  
 	file = fopen(chemin, "r");

 	if(file == NULL) {
		printf("pas de %s trouvé\n\r\n\r",sFile);
 	}
	else{
		while(fgets(buffer, CHAR_MAX, file)) {
			printf(" %s\r", buffer);
		}
		printf("\r\n");
		fclose(file);
  }
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

struct dirent** getSavesList(int *listLenght){
	const char *const path = "../saves";
	int count;
	DIR *dir;
	struct dirent **list;
	struct dirent *entry;

	dir = opendir(path);
	if (dir == NULL){
		printf("impossible de trouver '%s'\n\r", path);
		return NULL;
	}
	count = 0;
	while ((entry = readdir(dir)) != NULL)
		++count;
	list = malloc(count * sizeof(*list));
	if (list == NULL){
		closedir(dir);
		printf("  pb allocation memoire\n\r\n\r");
		return list;
	}
	rewinddir(dir);
	count = 0;
	while ((entry = readdir(dir)) != NULL){
		if(isDirectory(entry->d_name)==0)
			if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
				list[count++] = entry;
	}
	qsort(list, count, sizeof(*list), compareSize);
	closedir(dir);
	*listLenght = count;
	return list;
}

void free_menuList(menu_item *menu,int max){
	int i;
	for(i= 0;i<max;i++){
		free(menu[i].menu_direction);
		free(menu[i].menu_name);
	}
	free(menu);
}