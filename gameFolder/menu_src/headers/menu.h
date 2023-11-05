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
 * @file menu.h
 * @brief file that does evering according to which menu you are
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _MENU_H_
#define  _MENU_H_

#include <termios.h>
#include <unistd.h>

#include "menuGen.h"
#include "dataExtractor.h"
#include "display.h"

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
 * @brief update the value of caseA according to the generation menu (3d mouvement possible)
 * @param fleche int value corresponding to arrowkey pressed
 * @param caseA value correspond to the cursor position
 * @param max maximim value for the cursor
 */
void Actu(int fleche, int *caseA, int max);

/**
 * @brief function that return the key that was typed, include arrow key
 * @param charTyped the char that that has been typed if it's alphabet or number 
 * @return the key type defined
 */
int getKeyboardInput(char *charTyped);

/**
 * @brief function that drive through the save creation menu
 * @return 0 if you go back to previous menu, -1 otherwise
 */
int BrowseCreate();

/**
 * @brief function that drive through the save menu, load if option is 0, delete if 2, 1 if create
 * @param createOption option corresponding to load, delete or create menu
 * @return 0 if you go back to previous menu, -1 otherwise
 */
int BrowseSave(int createOption);

/**
 * @brief function that drive through the maze generation menu
 * @return 0 if you go back to previous menu, -1 otherwise
 */
int BrowseGen();

/**
 * @brief execute some commands according to the string given
 * @param commandName string corresponding to the wanted command
 * @return 0 if you go back to previous menu, -1 otherwise
 */
int customCommandExec(char *commandName);

/**
 * @brief function that drive through the classic menu
 * @return 0 if you go back to previous menu, -1 otherwise
 */
int BrowseMenu(char *selectedMenu, char *menuName);

#endif