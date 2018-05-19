/*
 * FILE NAME: ManageCities.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 24.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions declarations.
 */

#ifndef SHORTEST_PATH_MANAGECITIES_H
#define SHORTEST_PATH_MANAGECITIES_H

#include "ErrorCodes.h"
#include "GraphRepresentation.h"
#include "ProgramInterface.h"

/* Declarations */

void addNoCityToTheGraph(Graph_t*, const char*, const char*, double);
void addOneCityToTheGraph(Graph_t*, const char*, const char*, double);
void addTwoCitiesToTheGraph(Graph_t*, const char*, const char*, double);
programError_t checkIfIsInGraph(const Graph_t*, const char*);
programError_t checkIfNameIsCorrect(char*);
programError_t checkIfNamesAreIdentical(const char*, const char*);
void checkMemory(void*);
void printErrorUsersActions(programError_t);
void printSystemError(systemError_t);
void removeAdjacencyListNodes(AdjacencyListNode_t*);
void removeCity(Graph_t*, const char*);
void removeCityMenu(Graph_t*);
void removeConnection(Graph_t*, const char*, const char*);
void renameCityMenu(Graph_t*);
void renameCity(Graph_t*, const char*, const char*);

#endif //SHORTEST_PATH_MANAGECITIES_H
