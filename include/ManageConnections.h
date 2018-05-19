/*
 * FILE NAME: ManageConnections.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions declarations.
 */

#ifndef SHORTEST_PATH_MANAGECONNECTIONS_H
#define SHORTEST_PATH_MANAGECONNECTIONS_H

#include "GraphCreation.h"
#include "ProgramInterface.h"

/* Declarations */

void addConnection(Graph_t*);
void addNoCityToTheGraph(Graph_t*, const char*, const char*, double);
void addOneCityToTheGraph(Graph_t*, const char*, const char*, double);
void addTwoCitiesToTheGraph(Graph_t*, const char*, const char*, double);
void changeDistance(Graph_t*, const char*, const char*, double);
void changeDistanceMenu(Graph_t*);
programError_t checkIfIsInGraph(const Graph_t*, const char*);
programError_t checkIfNameIsCorrect(const char*);
programError_t checkIfConnectionIsInGraph(const Graph_t*, const char*, const char*);
programError_t checkIfDistanceIsCorrect(double);
programError_t checkIfNamesAreIdentical(const char*, const char*);
void printErrorUsersActions(programError_t);
void removeCity(Graph_t*, const char*);
void removeConnection(Graph_t*, const char*, const char*);
void removeConnectionMenu(Graph_t*);

#endif //SHORTEST_PATH_MANAGECONNECTIONS_H
