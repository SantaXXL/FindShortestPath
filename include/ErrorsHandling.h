/*
 * FILE NAME: ErrorsHandling.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions declarations.
 */


#ifndef SHORTEST_PATH_ERRORSHANDLING_H
#define SHORTEST_PATH_ERRORSHANDLING_H

#include "GraphRepresentation.h"

/* Declarations */

programError_t checkIfConnectionIsInGraph(const Graph_t *, const char *, const char *);
programError_t checkIfIsInGraph(const Graph_t *, const char *);
programError_t checkIfNameIsCorrect(const char *);
programError_t checkIfDistanceIsCorrect(double);
programError_t checkIfNamesAreTheSame(const char *, const char *);
programError_t checkUsersChoiceMainMenu(const char *, int *);
void checkMemory(void *);
void clearBuffer(void);
void printErrorSystem(systemError_t);

#endif //SHORTEST_PATH_ERRORSHANDLING_H
