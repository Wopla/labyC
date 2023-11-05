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
 * @file dataExtractor.h of the menu
 * @brief dataExtractor of the menu, will do everyting related to file gesture etc
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
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

/**
 * @brief structure genSettings, contain all settings usefull to the generation, according to settings/generator.txt
 */
typedef struct genSettings_s{
	char *saveName;
	int i;
	int j;
	int difficulty;
}genSettings;

extern genSettings settings;

/**
 * @brief structure menu_item, define a menu by it's name and it's destination
 */
typedef struct menu_item_s{
	char *menu_name;
	char *menu_direction;
}menu_item;

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
 * @brief function that return the list of menu according to a given file
 * @param menuCSVName the name of the file that contain the menu(s)
 * @param max will be implement as the number of menu found
 * @return the list of menu found
 */
menu_item* getMenu(char *menuCSVName, int *max);

/**
 * @brief function that write inside generator.txt the current generation settings
 */
void createSettings();

/**
 * @brief delete the wanted file
 * @param fileToDelete the name of the file to delete
 */
void deleteFile(char *fileToDelete);

/**
 * @brief display the data of a given file
 * @param sFile the name of the input file
 */
void afficheInfo(char *sFile);

/**
 * @brief method that check if the folder given is indeed a folder
 * @return 0 if is a folder
 */
int isDirectory(const char *path);

/**
 * @brief get the list of file inside the saves folder
 * @param listLenght will be implement by the number of file founded
 * @return the list of file found
 */
struct dirent** getSavesList(int *listLenght);

/**
 * @brief free the allocated space given to the menu list
 * @param menu the list of menu
 * @param max the size of the list
 */
void free_menuList(menu_item *menu,int max);

#endif