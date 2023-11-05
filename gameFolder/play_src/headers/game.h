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
 * @file game.h
 * @brief game action on each turn
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _GAME_H_
#define  _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "display.h"
#include "dependency.h"

#define ESC_KEY 27
#define EOF_KEY 4

#define ARROWUP 1
#define ARROWDOWN 2
#define ARROWRIGHT 3
#define ARROWLEFT 4
#define CRETURN 5
#define ALPHABET 6
#define NUMBER 7
#define SPACE 8
#define DELETE 9
#define ESC 10

/**
 * @brief function that return the key that was typed, include arrow key
 * @param charTyped the char that that has been typed if it's alphabet or number 
 * @return the key type defined
 */
int getKeyboardInput(char *charTyped);

/**
 * @brief move the player in the maze according to a key typed
 * call getKeyboardInput
 * @param game the current board
 * @param hasMoved boolean like int that say if the player did move or not
 */
void gameTurn(board* game,int *hasMoved);

#endif