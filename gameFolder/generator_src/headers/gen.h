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
 * @file gen.h
 * @brief main file of the generator
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _GEN_H_
#define  _GEN_H_

#include "generator.h"
#include "dataExtractor.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

/**
 * @brief generate the maze of the given board
 * @param game the board where we will generate the maze 
 */
void gen(board game);

/**
 * @brief free the memory that was allocated for the maze
 * @param game the board that contain the maze
 */
void freeGame(board game);

/**
 * @brief load a board according to a save name and then play until the end of the maze has been reached by the player
 * @return 0 at the end
 */
int main();

#endif