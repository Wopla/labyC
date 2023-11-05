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
 * @file play.h
 * @brief the main file of the play exec
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _MAIN_H_
#define  _MAIN_H_

#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "game.h"
#include "display.h"
#include "dataExtractor.h"

/**
 * @brief main function, charge the game, if the game is correctly charged play until the player reach the end or interruption
 * @param argc number of argument
 * @param argv list of argument given, excpecting 1 arg that is the save to load
 */
int main(int argc, char **argv);

#endif
