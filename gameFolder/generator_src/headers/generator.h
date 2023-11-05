/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @file generator.h
 * @brief contains the 2 method to generate a perfectmaze, one with backtrack recursive and the other with randomfuse
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _GENERATOR_H_
#define  _GENERATOR_H_

#include <stdlib.h>
#include <time.h>

struct cell_s {
	int x;
	int y;
};
typedef struct cell_s* cell;

/**
 *	This method give i2 & j2 new value acording to the wanted direction
 **/
void getSurrounding(int direction, int *i2, int *j2, int i, int j);

/**
 * @brief According to a maze made of 1 & 0, with 1 being a wall and 0 a path, this method will give you the number of path around a certain cell, exculding border
 * @param maze the current maze
 * @param i the current raw
 * @param j the current column
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
int countAround(int** maze,int i, int j, int iMax, int jMax);

/**
 * @brief This method will tell you if a cell is a candidate to be carved
 * To tranlate a 2d thin wall to thick one (1 cell thick) we have to exclude all 2k-i && 2k-j cells
 * If the cell isn't already a path and the previous condition has been meet, then we check that the cells have only 1 path around herself
 * @param maze the current maze
 * @param i the current raw
 * @param j the current column
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
int candidates(int** maze,int i, int j, int iMax, int jMax);

/**
 * @brief This method is the bactrack recursive method called to generate the maze
 * @param i the current raw
 * @param j the current column
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void carveDaMaze(int** maze, int i, int j, int iMax, int jMax);

/**
 * @brief Initialize the first carved cells with a decreasing value
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void initRdmFuse(int** maze, int iMax, int jMax);

/**
 * @brief spread the value of the current cells to the cells around it if their values isn't the same, recursive method
 * @param i the current raw
 * @param j the current column
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void spreadValue(int** maze,int i, int j, int iMax, int jMax);

/**
 * @brief check if the given cell is breakable : check if the value around it are different
 * @param i the current raw
 * @param j the current column
 */
int isDestroyable(int** maze,int i, int j);

/**
 * @brief initialise the list of the cells that are breakable
 * @param breakableWallList list of cell that will be breakable
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void initBreakableWallList(cell* breakableWallList, int iMax, int jMax);

/**
 * @brief free the allocated space given to the breakable list
 * @param breakableWallList list of cell that will be breakable
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void freeCellList(cell* breakableWallList, int iMax, int jMax);

/**
 * @brief place the element a the end of the list et reduce maxWall that will be the limit of the list
 * @param breakableWallList list of cell that will be breakable
 * @param i the value of the cells to "remove"
 * @param maxWall the max size of the list
 */
void removeElement(cell *breakableWallList,int i ,int * maxWall);

/**
 * @brief this method carve the walls until the perfect maze is completed
 * call initBreakableWallList, isDestroyable, removeElement, spreadValue and freeCellList
 * @param maze the current maze
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void carveRdmFuse(int** maze, int iMax, int jMax);

/**
 * @brief put every negative value of the maze to 0
 * @param maze the current maze
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void redefineRdmFuseWay(int **maze, int iMax, int jMax);

/**
 *	
 **/
 /**
 * @brief This method generate a perfect labyrinth using random paths fuse
 * First we initialise the maze by pre-carving it with initRdmFuse
 * then we carve eache wall needed
 * @param maze the current maze
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void randomFuse(int** maze, int iMax, int jMax);

#endif