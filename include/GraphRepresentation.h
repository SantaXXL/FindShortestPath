/*
 * FILE NAME: GraphRepresentation.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 21.04.2016
 *
 * DESCRIPTION:
 *
 * Here are defined structures that create graph.
 */

#ifndef SHORTEST_PATH_GRAPHREPRESANTATION_H
#define SHORTEST_PATH_GRAPHREPRESANTATION_H

typedef struct AdjacencyListNode {
    struct AdjacencyListNode* next;
    char* to;
    double distance;
    unsigned int ordinal_number;
} AdjacencyListNode_t;

typedef struct AdjacencyList {
    char* from;
    struct AdjacencyList* next;
    struct AdjacencyListNode* head;
    unsigned int ordinal_number;
} AdjacencyList_t;

typedef struct Graph {
    struct AdjacencyList* head;
} Graph_t;

#endif //SHORTEST_PATH_GRAPHREPRESANTATION_H
