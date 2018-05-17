/*
 * FILE NAME: GraphCreation.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions declarations.
 */


#ifndef SHORTEST_PATH_GRAPHCREATION_H
#define SHORTEST_PATH_GRAPHCREATION_H

#include "ListRepresentation.h"
#include "GraphRepresentation.h"
#include "ErrorCodes.h"

/* Declarations */

void createLists(ConnectionsList_t *, UniqueCitiesList_t *);
void addNodeToAdjacencyList(AdjacencyList_t *, const char *, double);
void addEdgesToGraph(Graph_t *, ConnectionsList_t, UniqueCitiesList_t *);
void addAdjacencyList(Graph_t *, const char *);
void checkMemory(void *);
Graph_t *createGraph(void);
Graph_t *graphCreation(void);
AdjacencyList_t *makeAdjacencyList(const char *);
AdjacencyListNode_t *makeAdjacencyListNode(const char *, double);
void printErrorDataBase(programError_t);
void printErrorSystem(systemError_t);
void removeAdjacencyListNodes(AdjacencyListNode_t *);
void removeGraph(Graph_t *);
void removeConnectionsList(ConnectionsList_t *);
void removeUniqueCitiesList(UniqueCitiesList_t *);
void updateDataBaseFile(const Graph_t *);
void updateOrdinalNumbers(Graph_t *);

#endif //SHORTEST_PATH_GRAPHCREATION_H
