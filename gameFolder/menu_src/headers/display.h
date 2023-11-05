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
 * @brief everything related to the display of the menu
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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define esc 27

extern char *loadedSave;

/**
 * @brief switch the color of what's displaying the terminal
 * @param c the color you want to display
 */
void color (char c);

/**
 * @brief but the displaying of the terminal back to normal
 */
void normal();


/**
 * @brief but the displaying of the terminal in bold
 */
void bold();

/**
 * @brief hide the cursor
 */
void cursoff ();

/**
 * @brief show the cursor
 */
void curson  ();


/**
 * @brief Display the title in ascii art
 */
void titre();


/**
 * @brief display the menu when creating a save
 * @param caseA the position on the made up cursor
 * @param saveName the name of the save your writing
 */
void affichMenuCreate(int caseA, char *saveName);

/**
 * @brief display the menu when generating a maze
 * @param caseA the position on the made up cursor
 * @param i value of the max raws of the maze
 * @param j value of the max column of the maze
 * @param playMode the gamemode chosen
 */
void affichMenuGen(int caseA, int i,int j,int playMode);

/**
 * @brief display the given menu list
 * @param caseA the position on the made up cursor
 * @param max size of the menulist
 * @param currentMenu the list of menu
 * @param menuName the name of the current menu we're in
 */
void affichMenu(int caseA, int max, char** currentMenu,char *menuName);

#endif