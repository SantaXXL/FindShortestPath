/*
 * FILE NAME: ListRepresentation.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 21.04.2016
 *
 * DESCRIPTION:
 *
 * Here are definitions of structures that are used
 * to create lists connections_list and unique_cities_list
 */

#ifndef SHORTEST_PATH_LIST_REPRESENTATION_H
#define SHORTEST_PATH_LIST_REPRESENTATION_H

/* Following 2 structures will be used to create ConnectionsList_t *connections_list. */

typedef struct ConnectionsListNode
{
    struct ConnectionsListNode *next;
    char *from;
    char *to;
    double distance;
}ConnectionsListNode_t;

typedef struct ConnectionsList
{
    struct ConnectionsListNode *head;
}ConnectionsList_t;


/* Following 2 structures will be used to create unique_cities list. */

typedef struct UniqueCitiesListNode
{
    struct UniqueCitiesListNode *next;
    char *city;
}UniqueCitiesListNode_t;

typedef struct citiesList
{
    struct UniqueCitiesListNode *head;
}UniqueCitiesList_t;

#endif //SHORTEST_PATH_LIST_REPRESENTATION_H
