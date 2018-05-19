/*
 * FILE NAME: ListCreation.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions declarations.
 */

#ifndef SHORTEST_PATH_LISTCREATION_H
#define SHORTEST_PATH_LISTCREATION_H

#include "ErrorCodes.h"
#include "ListRepresentation.h"
#include <stdio.h>

/* Declarations */

void addConnectionToTheList(ConnectionsList_t*, const char*, const char*, double);
void addUniqueCitiesToTheList(ConnectionsList_t*, size_t, UniqueCitiesList_t*);
void addUniqueCityToTheList(UniqueCitiesList_t*, const char*);
programError_t checkIfNameIsCorrect(const char*);
programError_t checkIfAlreadyOnTheList(ConnectionsList_t*, const char*, const char*);
programError_t checkIfConnectionsAreUndirected(const ConnectionsList_t*);
programError_t checkIfDistancesAreOK(const ConnectionsList_t*);
programError_t checkIfNamesAreIdentical(const char*, const char*);
void checkMemory(void*);
void createLists(ConnectionsList_t*, UniqueCitiesList_t*);
ConnectionsListNode_t* makeConnectionsListNode(const char*, const char*, double);
UniqueCitiesListNode_t* makeUniqueCityNode(const char*);
void printDataBaseError(programError_t);
void printSystemError(systemError_t);
int stringCmp(const void*, const void*);

#endif //SHORTEST_PATH_LISTCREATION_H
