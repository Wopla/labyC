#include "generator.h"

void getSurrounding(int direction, int *i2, int *j2, int i, int j){
	*i2=i;
	*j2=j;
	switch(direction){
		case 0 : *j2 = j+1;
			break;
		case 1 : *i2 = i+1;
			break;
		case 2 : *j2 = j-1;
			break;
		case 3 : *i2 = i-1;
			break;
	}
}

int countAround(int** maze,int i, int j, int iMax, int jMax){
	int retour =4;
	int i2,j2;
	int t;
	for(t=0;t<4;t++) {
		getSurrounding(t, &i2, &j2, i, j);
		if(i2!=0 || j2!=0 || i2!=iMax-1 || j2!=jMax-1)
			retour -= maze[i2][j2];
		else
			retour -= 1;
	}
	return retour;
}

int candidates(int** maze,int i, int j, int iMax, int jMax){
	if(maze[i][j]==0){
		return 1;
	}else{
		if(!((i-1)%2!=0 && (j-1)%2!=0))
			return countAround(maze,i,j, iMax, jMax) !=1 ? 1 : 0;
		else
			return 1;
	}
}

void carveDaMaze(int** maze, int i, int j, int iMax, int jMax){
	int tab[4];
	int i2, j2;
	int l,t;
	int direction;
	for(l=0;l<4;l++)
		tab[l]=1;
	for (l =0;l<4;l++){
		direction = rand()%(4-l);
		for (t =0;t<3;t++)
			if(tab[t]!=1 && direction >=t)
				direction= direction +1;
		tab[direction]=0;
		getSurrounding(direction,&i2,&j2,i,j);
		if((i2!=iMax-1 && j2!=jMax-1) && (i2!=0 && j2!=0)){
			if(!(i2==i && j2 ==j)){
				if(candidates(maze,i2,j2,iMax,jMax)==0){
					maze[i2][j2]=0;
					carveDaMaze(maze, i2,j2,iMax,jMax);
				}
			}
		}
	}
}


void initRdmFuse(int** maze, int iMax, int jMax){
	int step;
	int i,j;
	int incr;
	step=0;
	i=1;
	j=1;
	for(incr = jMax+1; incr< iMax*jMax- jMax;
	(i%2==0) ? (incr+=jMax+1) : (incr+=2)){
		i = incr/jMax;
		j = incr%jMax;
		if(i%2==1)
			maze[i][j]= -- step;
	}
}

void spreadValue(int** maze,int i, int j, int iMax, int jMax){
	int i2,j2;
	int l;
	for (l =0;l<4;l++){
		getSurrounding(l,&i2,&j2,i,j);
		if(i2>0 && j2>0 && i2<iMax-1 && j2<jMax-1){
			if(maze[i2][j2]<1){
				if(maze[i2][j2]!=maze[i][j]){
					maze[i2][j2] = maze[i][j];
					spreadValue(maze,i2,j2,iMax,jMax);
				}
			}
		}
	}
}

int isDestroyable(int** maze,int i, int j){
	int returnValue=1;
	if(i%2==0){
		if(maze[i-1][j]!=maze[i+1][j]){
			returnValue=0;
			maze[i][j]=maze[i+1][j];
		}
	}
	else{
		if(maze[i][j-1]!=maze[i][j+1]){
			returnValue=0;
			maze[i][j]=maze[i][j+1];
		}
	}
	return returnValue;
}

void initBreakableWallList(cell* breakableWallList, int iMax, int jMax){
	int i,j;
	int t=0;
	int incr;
	for(incr=jMax+2; incr<(iMax*jMax-(jMax+1)); 
	(j==jMax-2 || j==jMax-3) ? (incr+=4) : (incr+=2)){
		i = incr/jMax;
		j = incr%jMax;
		breakableWallList[t] = malloc(sizeof(struct cell_s));
		breakableWallList[t]->x=i;
		breakableWallList[t]->y=j;
		t++;
	}
}

void freeCellList(cell* breakableWallList, int iMax, int jMax){
	int j;
	int t=0;
	int incr;
	for(incr=jMax+2; incr<(iMax*jMax-(jMax+1)); 
	(j==jMax-2 || j==jMax-3) ? (incr+=4) : (incr+=2)){
		j = incr%jMax;
        free(breakableWallList[t]);
		t++;
	}
    free(breakableWallList);
}

void removeElement(cell *breakableWallList,int i ,int * maxWall){
	breakableWallList[i]->x = breakableWallList[*maxWall-1]->x;
	breakableWallList[i]->y = breakableWallList[*maxWall-1]->y;
	(*maxWall)--;
}

void carveRdmFuse(int** maze, int iMax, int jMax){
	int maxWall=(iMax-2)*(jMax-2)/2;
	int wallToDestroy;
	int i,j;
	int t;
	cell *breakableWallList;
	breakableWallList = malloc(sizeof(cell*)*maxWall);
	initBreakableWallList(breakableWallList, iMax, jMax);
	for(t=0;t<(iMax/2)*(jMax/2)-1;t++){
		wallToDestroy = rand()%maxWall;
		i = breakableWallList[wallToDestroy]->x;
		j = breakableWallList[wallToDestroy]->y;
		while(isDestroyable(maze,i,j)!=0){
			removeElement(breakableWallList,wallToDestroy,&maxWall);
			wallToDestroy = rand()%maxWall;
			i = breakableWallList[wallToDestroy]->x;
			j = breakableWallList[wallToDestroy]->y;
		}
		removeElement(breakableWallList,wallToDestroy,&maxWall);
		spreadValue(maze,i,j, iMax, jMax);
	}
    freeCellList(breakableWallList, iMax, jMax);
}

void redefineRdmFuseWay(int **maze, int iMax, int jMax){
	int i;
	for(i=0;i<iMax*jMax;i++)
		maze[i/jMax][i%jMax] = maze[i/jMax][i%jMax]<1 ? 0 : 1;
}

void randomFuse(int** maze, int iMax, int jMax){
	initRdmFuse(maze,iMax,jMax);
	carveRdmFuse(maze,iMax,jMax);
	redefineRdmFuseWay(maze,iMax,jMax);
}