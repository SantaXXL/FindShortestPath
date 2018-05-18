/*
 * FILE NAME: GraphCreation.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions's declarations.
 */

#ifndef SHORTEST_PATH_GRAPHCREATION_H
#define SHORTEST_PATH_GRAPHCREATION_H

#include "ErrorCodes.h"
#include "GraphRepresentation.h"
#include "ListRepresentation.h"

/* Declarations */

void createLists(ConnectionsList_t*, UniqueCitiesList_t*);
void addNodeToAdjacencyList(AdjacencyList_t*, const char*, double);
void addEdgesToGraph(Graph_t*, ConnectionsList_t, UniqueCitiesList_t*);
void addAdjacencyList(Graph_t*, const char*);
void checkMemory(void*);
Graph_t* createGraph(void);
Graph_t* graphCreation(void);
AdjacencyList_t* makeAdjacencyList(const char*);
AdjacencyListNode_t* makeAdjacencyListNode(const char*, double);
void printDataBaseError(programError_t);
void printSystemError(systemError_t);
void removeAdjacencyListNodes(AdjacencyListNode_t*);
void removeGraph(Graph_t*);
void removeConnectionsList(ConnectionsList_t*);
void removeUniqueCitiesList(UniqueCitiesList_t*);
void updateDataBaseFile(const Graph_t*);
void updateOrdinalNumbers(Graph_t*);

#endif //SHORTEST_PATH_GRAPHCREATION_H
