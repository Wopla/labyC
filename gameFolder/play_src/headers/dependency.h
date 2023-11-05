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
 * @file dependency.h
 * @brief headers file giving the definition 
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _DEPENDENCY_H_
#define  _DEPENDENCY_H_

/**
 * @brief structure player, contain the current position of the player
 */
typedef struct playerS {
	int x;
	int y;
}player;

/**
 * @brief structure board, contain everything related to the a game session, a play, the size of the maze and the maze itself
 */
typedef struct boardS {
	player p;
	int iMax;
    int jMax;
	int **maze;
}board;

#endif