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
 * @file display.h
 * @brief everything relate to the display
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */
 
#ifndef _DISPLAY_H_
#define  _DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 *	@brief Display method on the maze 
 * 	Will display the player above the maze
 * 	Corresponding maze value
 * 		0 is a path
 * 		1 is a wall
 * @param maze the current maze
 * @param iJ the current raw of the player
 * @param yJ the current column of the player
 * @param iMax the max size of the raws of the maze
 * @param jMax the max size of the column of the maze
 */
void displayMaze(int** maze,int xJ, int yJ,int iMax, int jMax);

#endif