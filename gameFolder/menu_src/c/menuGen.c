#include"menuGen.h"


void bell(int n){
	do{
		printf ("%c" , 7);
		n-- ;
	}while (n>0);
}

int traitement(int fleche, int caseA, int max){
	if((caseA==1)&&(fleche==1)){
		bell(1);
		caseA+=1;;
	}
	else if((caseA==max+1)&&(fleche==2)){
		bell(1);
		caseA-=1;
	}
	return  caseA;
}

void ActuGen(int fleche, int *caseA, int max, int *i, int *j, int *gameMode){
	switch(*caseA){
		case 1:
			if(fleche==2)
				*caseA+=2;
			else if(fleche==3)
				(*caseA)++;
			break;
		case 2:
			switch(fleche){
				case 1:
					if(*i<99)
						*i+=2;
					(*caseA)++;
					break;
				case 2:
					if(*i>5)
						*i-=2;
					(*caseA)--;
					break;
				case 3:
					(*caseA)++;
					break;
				case 4:
					(*caseA)--;
					break;
			}
			break;
		case 3:
			switch(fleche){
				case 1:
					if(*j<99)
						*j+=2;
					(*caseA)++;
					break;
				case 2:
					if(*j>5)
						*j-=2;
					(*caseA)--;
					break;
				case 4:
					(*caseA)--;
					break;
			}
			break;
		case 4:
			if(fleche==2 || fleche==3)
				(*caseA)++;
			else if(fleche==1)
				*caseA-=2;
			break;
		case 5:
			switch(fleche){
				case 1:
					if(*gameMode<2)
						(*gameMode)++;
					(*caseA)++;
					break;
				case 2:
					if(*gameMode>0)
						(*gameMode)--;
					(*caseA)--;
					break;
				case 4:
					(*caseA)--;
					break;
			}
			break;
		case 6:
			if(fleche==1)
				(*caseA)--;
			break;
	}
	*caseA = traitement(fleche, *caseA, max);
	switch(fleche){
		case 1:*caseA-=1;break;
		case 2:*caseA+=1;break;
	}
}