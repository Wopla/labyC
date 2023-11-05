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
 * @file dataExtractor.h of the game itself
 * @brief dataExtractor of the maze game, will do everyting related to file gesture etc
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _DATAEXTRACTOR_H_
#define  _DATAEXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "dependency.h"

/**
 * @brief load the data of the given file inside the given board
 * @param game the game board
 * @param saveName the name of the save to load
 */
int charge(board* game, char* saveName);

#endif