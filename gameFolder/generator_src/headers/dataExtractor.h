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
 * @file dataExtractor.h of the generator
 * @brief dataExtractor of the maze generator, will do everyting related to file gesture etc
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

#define BADKEY -1
#define SAVEN 0
#define ISIZE 1
#define JSIZE 2
#define GAMEMODE 3

/**
 * @brief structure hashMap, that contain a key and a value corresponding to eachother
 */
typedef struct hashMap_s{
	char *key;
	int val;
}hashMap;

/**
 * @brief structure genSettings, contain all settings usefull to the generation, according to settings/generator.txt
 */
typedef struct genSettings_s{
	char *saveName;
	int i;
	int j;
	int difficulty;
}*genSettings;

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
}*board;


/**
 * @brief Simple function that return the number of line in a file
 * @param file the wanted file
 * @return the number of line in file
 */
int countLine(FILE* file);

/**
 * @brief function that return the wanted string according to a column number in a line, column are separated by ':', source :ideone.com
 * @param line string corresponding to the line
 * @param n the number of the wanted column
 * @return if find, return the string corresponding to the given column, else return NULL
 */
char* getfield(char* line, int n);

/**
 * @brief function that create or replace a save in ../saves/ with the current game value
 * @param game the current board that has been generated
 * @param saveName the name of the file you want to save
 */
void save(board game, char* saveName);

/**
 * @brief convert a string in int
 * @param input the string to convert
 * @return the int value
 */
int digit2int(char * input);

/**
 * @brief get the value in a given file in genSettings struct
 * @param genS the structur to fill
 * @param file the file to read (should be generator.txt)
 * @return 0 if everything went well, -1 otherwise
 */
int implementGenSettings(genSettings genS, FILE *file);

/**
 * @brief open the file ../settings/generator.txt and call implementGenSettings to fill the genSettings struct
 * @param genS the structur to fill
 * @return 0 if everything went well, -1 otherwise
 */
int loadGeneratorSettings(genSettings genS);

/**
 * @brief function using hashmap struct, return the int key according to the char key
 * @param key the char key
 * @return the int key
 */
int keyfromstring(char *key);

#endif
