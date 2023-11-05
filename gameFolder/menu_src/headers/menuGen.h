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
 * @file menuGen.h
 * @brief specific traitment for the menu generation that is "3D"
 */

/**
 * @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
 *
 * @version 01.00
 *
 * @date 30/10/2022
 */

#ifndef _MENUGEN_H_
#define  _MENUGEN_H_

#include <stdio.h>

/**
 * @brief make the ubuntu bell sound 
 */
void bell (int n);


/**
 * @brief update the value of caseA according to the arrowkey pressed
 * @param fleche int value corresponding to arrowkey pressed
 * @param caseA value correspond to the cursor position
 * @param max maximim value for the cursor
 */
int traitement(int fleche, int caseA, int max);


/**
 * @brief update the value of caseA, i, j and gameMode according to the generation menu (3d mouvement possible)
 * @param fleche int value corresponding to arrowkey pressed
 * @param caseA value correspond to the cursor position
 * @param max maximim value for the cursor
 * @param i value of the i choosen
 * @param j value of the j choosen
 * @param gameMode value of the gameMode choosen
 */
void ActuGen(int fleche, int *caseA, int max, int *i, int *j, int *gameMode);

#endif