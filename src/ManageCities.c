/*
 * FILE NAME: ManageCities.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 02.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of functions, that
 * are used to remove a city from a graph or rename it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ManageCities.h"
#include "Constants.h"

/**********************************************************************************************************************/

/* Definitions */

/**********************************************************************************************************************/

/* Remove city */

/*
 * FUNCTION NAME: removeCityMenu
 *
 * DESCRIPTION:
 * Function gets user's input and calls removeCity() function.
 */

void removeCityMenu(Graph_t *graph)
{
    if(graph->head == NULL)
    {
        printErrorUsersActions(EMPTY_GRAPH);
        return;
    }
    char city[G_CITYS_NAME_LENGTH];
    programError_t what_error = NO_ERROR;
    int counter = 2;

    do
    {
        if(counter % 4 == 1)
            showCityList(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(REMOVE_CITY, city);
        what_error = checkIfNameIsCorrect(city);
        if (what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city);
    }
    while(what_error != NO_ERROR);
    removeCity(graph, city);
}


/*
 * FUNCTION NAME: removeCity
 *
 * DESCRIPTION:
 * Function does remove given city from a graph.
 */

void removeCity(Graph_t *graph, const char *city)
{
    AdjacencyList_t *upper, *previous_upper;
    AdjacencyListNode_t *lower;
    size_t how_many_connections = 0;
    char **connections_array;
    size_t i;
    previous_upper = graph->head;

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        /* Firstly, search for adjacency list that city creates. */

        if(strcmp(upper->from, city) == 0)
        {
            /* When you find it, count how many nodes (i.e. how many connections there
             * is between given city and other cities) are in its adjacency list. */

            for(lower = upper->head; lower != NULL; lower = lower->next)
                ++how_many_connections;

            /* When you have done it, then create an array and copy connected cities
             * to created array. */

            connections_array = (char **)malloc(how_many_connections * sizeof(char *));
            checkMemory(connections_array);
            for(i = 0; i < how_many_connections; ++i)
            {
                connections_array[i] = (char *)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
                checkMemory(connections_array[i]);
            }
            i = 0;
            for(lower = upper->head; lower != NULL; lower = lower->next)
                strcpy(connections_array[i++], lower->to);

            /* Now, 2 cases: if given city creates a first adjacency list in the graph... */

            if(upper == graph->head)
            {
                /* Remove adjacency list from the graph.  */

                graph->head = upper->next;
                removeAdjacencyListNodes(previous_upper->head);
                free(previous_upper->from);
                free(previous_upper);
            }

            /* ... or it does not. */

            else if(upper != graph->head)
            {
                /* Remove adjacency list from the graph. */

                previous_upper->next = upper->next;
                removeAdjacencyListNodes(upper->head);
                free(upper->from);
                free(upper);
            }
            break;
        }
        previous_upper = upper;
    }

    /* Now, remove every connection between given city cities
     * connected to it. */

    for(i = 0; i < how_many_connections; ++i)
        removeConnection(graph, city, connections_array[i]);

    /* And now free memory after array. */

    for(i = 0; i < how_many_connections; ++i)
        free(connections_array[i]);
    free(connections_array);
}

/**********************************************************************************************************************/

/* Rename city */

/*
 * FUNCTION NAME: renameCityMenu
 *
 * DESCRIPTION:
 * Function gets city's name and then calls a function to
 * rename it.
 */

void renameCityMenu(Graph_t *graph)
{
    if(graph->head == NULL)
    {
        printErrorUsersActions(EMPTY_GRAPH);
        return;
    }
    char city[G_CITYS_NAME_LENGTH];
    char new_citys_name[G_CITYS_NAME_LENGTH];
    programError_t what_error = NO_ERROR;
    int counter = 2;

    do
    {
        if((counter % 4) == 1)
            showCityList(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(RENAME_CITY, city);
        what_error = checkIfNameIsCorrect(city);
        if (what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city);
    }
    while(what_error != NO_ERROR);

    counter = 2;
    do
    {
        if((counter % 4) == 1)
            showCityList(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(NEW_CITYS_NAME, new_citys_name);
        what_error = checkIfNameIsCorrect(new_citys_name);
        if(what_error == NO_ERROR)
            what_error = checkIfNamesAreTheSame(city, new_citys_name);
        if(what_error == NO_ERROR)
        {
            what_error = checkIfIsInGraph(graph, new_citys_name);
            if(what_error != NO_SUCH_CITY)
                what_error = CITY_ALREADY_IN_GRAPH;
            else
                what_error = NO_ERROR;
        }
    }
    while(what_error != NO_ERROR);

    renameCity(graph, city, new_citys_name);
}


/*
 * FUNCTION NAME: renameCity
 *
 * DESCRIPTION:
 * Function changes city's name to new_citys_name.
 */

void renameCity(Graph_t *graph, const char *old_citys_name, const char *new_citys_name)
{
    AdjacencyList_t *upper;
    AdjacencyListNode_t *lower;
    char **connections_array = NULL;
    double *distances_array = NULL;
    size_t how_many_connections = 0;
    size_t i, j;

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        if(strcmp(upper->from, old_citys_name) == 0)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
                ++how_many_connections;

            /* When it is done, then create an array and copy connected cities
             * to created array. */

            connections_array = (char **)malloc(how_many_connections * sizeof(char *));
            checkMemory(connections_array);
            distances_array = (double *)malloc(how_many_connections * sizeof(double));
            checkMemory(distances_array);
            for(i = 0; i < how_many_connections; ++i)
            {
                connections_array[i] = (char *)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
                checkMemory(connections_array[i]);
            }

            /* And now copy data from adjacency list to the arrays. */

            i = 0;
            j = 0;
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                strcpy(connections_array[i++], lower->to);
                distances_array[j++] = lower->distance;
            }

            break;
        }
    }
    removeCity(graph, old_citys_name);

    if(graph->head != NULL)
        addOneCityToTheGraph(graph, new_citys_name, connections_array[0], distances_array[0]);
    else
        addTwoCitiesToTheGraph(graph, new_citys_name, connections_array[0], distances_array[0]);

    for(i = 1; i < how_many_connections; ++i)
        addNoCityToTheGraph(graph, new_citys_name, connections_array[i], distances_array[i]);

    for(i = 0; i < how_many_connections; ++i)
        free(connections_array[i]);
    free(connections_array);
    free(distances_array);
}
