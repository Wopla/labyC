#include "display.h"

char *loadedSave;

void color (char c)     {printf("%c[%dm",esc,c);} /* color from 30 to 47 */
void bold ()              {printf ("%c[1m",esc) ;} /* -- bold -- */
void cursoff ()           {printf ("%c[?25l",esc) ;}
void curson  ()           {printf ("%c[?25h",esc) ;}
void normal ()            {printf ("%c[0;24m",esc) ;}  /* cancel : bold , overstrike , underline */
void underline ()         {printf ("%c[4m",esc) ;}
void blink ()             {printf ("%c[5m",esc);}

void titre(){
	bold();
	color(34);
	printf("\n\r  o      ooooo  oooo   o     o\n\r");
  	printf("  o      o   o  o   o   o   o\n\r");
	color(36);
  	printf("  o      ooooo  oooo     o o\n\r");
	color(32);
  	printf("  o      o   o  o   o     o\n\r");
  	printf("  ooooo  o   o  oooo      o\n\r\n\r");
	normal();
}

void additionalTitleInfo(char *menuName){
	printf(" ");bold();underline();printf("%s menu",menuName);
	normal();  printf(" (Use arrow key to move and enter to select)\n\r\n\r");
	if(strcmp(menuName,"main")==0 || strcmp(menuName,"load")==0 ||strcmp(menuName,"play")==0 ){
		if(loadedSave== NULL){
			printf(" No game loaded !\n\r\n\r");
		}else{
			printf(" \"%s\" is loaded and ready to play !\n\r\n\r",loadedSave);
		}
	}
}

char *listMenuCreate[] = {"save name", "create", "previous"};
void affichMenuCreate(int caseA, char *saveName){
	int max;
	int i;
	max =3;
	system("clear");
	titre();
	additionalTitleInfo("Save Creation");

	for (i = 0 ; i < max ; i++){
		if(caseA==i+1){
			printf("->");
			underline();
		}
		else{
			printf("  ");
		}
		printf("%s",listMenuCreate[i]);
		if(i==0){
			normal();
			printf(" : %s",saveName);
			if(caseA==1){
				blink();
				printf("▓");
				normal();
			}
		}
		printf("\n\r\n\r");
		if(caseA==i+1)
			normal();
	}
}

char *listMenuGen[] = {"laby size", "row:", "column:", "laby mode","", "generate", "previous"};
char *listPlayMode[] = {"Easy", "Medium", "Hard"};
void affichMenuGen(int caseA,int i, int j,int playMode){
	int max;
	int t;

	listMenuGen[4]=listPlayMode[playMode];
	system("clear");
	titre();
	additionalTitleInfo("Generate");
	max=7;
	for (t = 0 ; t < max ; t++){
		if(t==(max-1))
			printf("\n\r");
		if(t==1 || t==2 || t==4){
			printf("  ");blink();
		}
		if(caseA==t+1){
			printf("->");
			normal();
			underline();
		}else{
			normal();
			printf("  ");
		}
		if(t==1 || t==2){
			if(caseA==t+1)
				normal();
			printf("%s[%02d]",listMenuGen[t],(t==1?i:j));
			(caseA!=t+1) ? printf("  ") : printf("△▽");
		}else
			if(t==4){
				normal();
				printf("[%s]",listMenuGen[t]);
				if(caseA==t+1){
					printf("△▽");
				}
			}
			else
				printf("%s",listMenuGen[t]);
		if(caseA==t+1)
			normal();
		if(t!=0 && t!=1 && t!=3)
			printf("\n\r\n\r");
	}
}

void affichMenu(int caseA, int max, char** currentMenu,char *menuName){
	int i;
	char *back;
	system("clear");
	titre();
	additionalTitleInfo(menuName);
	if(max>0){
		for (i = 0 ; i < max ; i++){

			if(caseA==i+1){
				printf("->");
				underline();
			}
			else{
				printf("  ");
			}
			if(!strcmp(currentMenu[i],"play")){
				printf("%s",currentMenu[i]);
				normal();
				if(loadedSave==NULL){
					color(31);
					printf(" (need loaded game !)\r\n");
					normal();
				}else
					printf("\r\n");
			}else
				printf("%s\n\r",currentMenu[i]);
			if(!strcmp(currentMenu[i],"create new save"))
				printf("\n\r");
			if(caseA==i+1)
				normal();
		}
	}
	else{
		color(31);bold();
		if(!strcmp(menuName,"load"))
			printf("  No saves found\n\r");
		else
			printf("  Menu does not exist .. \n\r  Please check corresponding csv.\n\r");
		normal();
	}
	printf("\n\r");
	if(caseA==max+1){
		if(max==0)
			blink();
		printf("->");
		if(max==0)
			normal();
		underline();
	}else{
		printf("  ");
	}
	back=(strcmp(menuName,"main")==0)? "leave":"previous";
	printf("%s\n\r",back);
	
	normal();
}
