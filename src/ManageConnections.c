/*
 * FILE NAME: ManageConnections.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of addConnection function
 * and other functions needed to add a connection to the graph.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdbool.h>
#include <string.h>

#include "Constants.h"
#include "ErrorCodes.h"
#include "GraphRepresentation.h"
#include "ManageConnections.h"

/**********************************************************************************************************************/

/* Definitions */

/**********************************************************************************************************************/

/* Add Connection */

/*
 * FUNCTION NAME: addConnection
 *
 * DESCRIPTION:
 * Function gets from user names of a cities, that create a
 * connection that will be added to the graph. Then, it checks, if cities
 * typed in by the user are already in the graph.
 * Then it calls a proper function that adds a new connection.
 * Which function is called depends on number of cities
 * that are already in the graph.
 */

void addConnection(Graph_t *graph)
{
    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    double distance = 0;
    programError_t what_error = NO_ERROR;
    size_t number_of_cities_in_graph = 0;

    /* First, get cities names and a distance between them. */

    do
    {
        printErrorUsersActions(what_error);
        getCitysName(FIRST_CITY, city1);
        what_error = checkIfNameIsCorrect(city1);
    }
    while (what_error != NO_ERROR);

    do
    {
        printErrorUsersActions(what_error);
        getCitysName(SECOND_CITY, city2);
        what_error = checkIfNameIsCorrect(city2);
        if(what_error == NO_ERROR)
            what_error = checkIfNamesAreTheSame(city1, city2);

        /* Check if connection is or is not already in the graph */

        if(what_error == NO_ERROR)
            what_error = checkIfConnectionIsInGraph(graph, city1, city2);
    }
    while (what_error != NO_ERROR);

    do
    {
        printErrorUsersActions(what_error);
        getDistanceBetweenCities(&distance);
        what_error = checkIfDistanceIsCorrect(distance);
    }
    while (what_error != NO_ERROR);

    /* If everything is fine, then add a connection to the graph .*/

    AdjacencyList_t *adjacency_list;

    /* Check how many times given cities are in the graph. */

    for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
    {
        if(strcmp(adjacency_list->from, city1) == 0)
            ++number_of_cities_in_graph;
        else if(strcmp(adjacency_list->from, city2) == 0)
            ++number_of_cities_in_graph;
    }

    switch(number_of_cities_in_graph)
    {
        case NO_CITIES:
        {
            addTwoCitiesToTheGraph(graph, city1, city2, distance);
            break;
        }
        case ONE_CITY:
        {
            addOneCityToTheGraph(graph, city1, city2, distance);
            break;
        }
        case TWO_CITIES:
        {
            addNoCityToTheGraph(graph, city1, city2, distance);
            break;
        }
        default:
            break;
    }
    clearBuffer();
}


/*
 * FUNCTION NAME: addOneCityToTheGraph
 *
 * DESCRIPTION:
 * When one city is already in the graph,
 * and one is not -> then use this function.
 */

void addOneCityToTheGraph(Graph_t *graph, const char *city1, const char *city2, double distance)
{
    AdjacencyList_t *adjacency_list;
    bool is_city1_in_the_graph = false;

    /* First, check if city1 is already in the graph -> if it is not,
     * then it means that city2 is. */

    for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
    {
        if(strcmp(city1, adjacency_list->from) == 0)
        {
            is_city1_in_the_graph = true;
            break;
        }
    }

    /* Case, when city1 is already in the graph. */

    if(true == is_city1_in_the_graph)
    {
        /* This on is simple - search for adjacency list that city1
         * creates and add city2 to it. */

        for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
        {
            if(strcmp(city1, adjacency_list->from) == 0)
            {
                addNodeToAdjacencyList(adjacency_list, city2, distance);
                break;
            }
        }

        /* Now, the case if city2 will create adjacency list
         * that will be first in the graph. */

        if(strcmp(city2, graph->head->from) < 0)
        {
            addAdjacencyList(graph, city2);
            addNodeToAdjacencyList(graph->head, city1, distance);
        }

        /* If it ain't, then... */

        for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
        {
            /* Scan graph for a moment, when name1 < city's name < name2 (in alphabetical order) */

            if(NULL != adjacency_list->next and strcmp(city2, adjacency_list->from) > 0 and
               strcmp(city2, adjacency_list->next->from) < 0)
            {
                AdjacencyList_t *temp = makeAdjacencyList(city2);
                addNodeToAdjacencyList(temp, city1, distance);
                temp->next = adjacency_list->next;
                adjacency_list->next = temp;
                break;
            }

                /* And this 'else if' is for the situation, when city should be
                 * added to the end of a graph. */

            else if (strcmp(city2, adjacency_list->from) > 0 and adjacency_list->next == NULL)
            {
                AdjacencyList_t *temp = makeAdjacencyList(city2);
                adjacency_list->next = temp;
                addNodeToAdjacencyList(temp, city1, distance);
            }
        }
    }

    /* Case, when city2 is already in the graph. */

    else if(false == is_city1_in_the_graph)
    {
        for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
        {
            if(0 == strcmp(city2, adjacency_list->from))
            {
                addNodeToAdjacencyList(adjacency_list, city1, distance);
                break;
            }
        }

        if(strcmp(city1, graph->head->from) < 0)
        {
            addAdjacencyList(graph, city1);
            addNodeToAdjacencyList(graph->head, city2, distance);
        }

        /* If it ain't, then... */

        for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
        {
            /* Scan graph till name1 < city's name < name2 (in alphabetical order) */

            if (NULL != adjacency_list->next and strcmp(city1, adjacency_list->from) > 0 and
                strcmp(city1, adjacency_list->next->from) < 0)
            {
                AdjacencyList_t *temp = makeAdjacencyList(city1);
                addNodeToAdjacencyList(temp, city2, distance);
                temp->next = adjacency_list->next;
                adjacency_list->next = temp;
                break;
            }

                /* And this 'else if' is for the situation, when city should be
                 * added to the end of a graph. */

            else if (strcmp(city1, adjacency_list->from) > 0 and adjacency_list->next == NULL)
            {
                AdjacencyList_t *temp = makeAdjacencyList(city1);
                adjacency_list->next = temp;
                addNodeToAdjacencyList(adjacency_list->next, city2, distance);
            }
        }
    }
}


/*
 * FUNCTION NAME: addTwoCitiesToTheGraph
 *
 * DESCRIPTION:
 * If given cities don't exist in the graph,
 * then add them.
 */

void addTwoCitiesToTheGraph(Graph_t *graph, const char *city1, const char *city2, double distance)
{
    AdjacencyList_t *adjacency_list;

    /* If graph is empty, then add two adjacency lists in alphabetical
     * order. */

    if(NULL == graph->head)
    {
        /* If graph is empty and city2 < city1 (in alphabetical order). */

        if(strcmp(city1, city2) < 0)
        {
            addAdjacencyList(graph, city2);
            addNodeToAdjacencyList(graph->head, city1, distance);
            addAdjacencyList(graph, city1);
            addNodeToAdjacencyList(graph->head, city2, distance);
        }

            /* If graph is empty and city2 < city1 (in alphabetical order). */

        else if(strcmp(city1, city2) > 0)
        {
            addAdjacencyList(graph, city1);
            addNodeToAdjacencyList(graph->head, city2, distance);
            addAdjacencyList(graph, city2);
            addNodeToAdjacencyList(graph->head, city1, distance);
        }
    }

        /* If graph is not empty, then search when adjacency list
         * should be added. */

    else if(NULL != graph->head)
    {
        if(strcmp(city1, city2) < 0)
        {
            /* Case 1: city1 is before city2 (in alphabetical order) */

            /* If city1 should be first in the graph... */

            if(strcmp(city1, graph->head->from) < 0)
            {
                addAdjacencyList(graph, city1);
                addNodeToAdjacencyList(graph->head, city2, distance);
            }

            /* If it ain't, then... */

            for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
            {
                /* Scan graph for a moment, when name1 < city's name < name2 (in alphabetical order). */

                if(NULL != adjacency_list->next and strcmp(city1, adjacency_list->from) > 0 and
                   strcmp(city1, adjacency_list->next->from) < 0)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city1);
                    addNodeToAdjacencyList(temp, city2, distance);
                    temp->next = adjacency_list->next;
                    adjacency_list->next = temp;
                }
                else if(NULL != adjacency_list->next and strcmp(city2, adjacency_list->from) > 0 and
                        strcmp(city2, adjacency_list->next->from) < 0)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city2);
                    addNodeToAdjacencyList(temp, city1, distance);
                    temp->next = adjacency_list->next;
                    adjacency_list->next = temp;
                }

                    /* And this 'else if' is for the situation, when two cities should be
                     * added to the end of a graph. */

                else if(strcmp(city1, adjacency_list->from) > 0 and adjacency_list->next == NULL)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city1);
                    adjacency_list->next = temp;
                    addNodeToAdjacencyList(adjacency_list->next, city2, distance);

                    adjacency_list = adjacency_list->next;
                    AdjacencyList_t * temp1 = makeAdjacencyList(city2);
                    adjacency_list->next = temp1;
                    addNodeToAdjacencyList(adjacency_list->next, city1, distance);
                }
                else if(strcmp(city2, adjacency_list->from) > 0 and adjacency_list->next == NULL)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city2);
                    adjacency_list->next = temp;
                    addNodeToAdjacencyList(adjacency_list->next, city1, distance);
                }
            }
        }

            /* Case 2: city2 is before city1 (in alphabetical order)
             * Basically - it just copy paste of the case above, but with swapped
             * city1<->city2. */

        else if(strcmp(city1, city2) > 0)
        {

            /* If city2 should be first in the graph... */

            if(strcmp(city2, graph->head->from) < 0)
            {
                addAdjacencyList(graph, city2);
                addNodeToAdjacencyList(graph->head, city1, distance);
            }

            /* If it ain't, then... */

            for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
            {
                /* Scan graph for a moment, when name1 < city's name < name2 (in alphabetical order) */

                if(NULL != adjacency_list->next and strcmp(city2, adjacency_list->from) > 0 and
                   strcmp(city2, adjacency_list->next->from) < 0)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city2);
                    addNodeToAdjacencyList(temp, city1, distance);
                    temp->next = adjacency_list->next;
                    adjacency_list->next = temp;
                }
                else if(NULL != adjacency_list->next and strcmp(city1, adjacency_list->from) > 0 and
                        strcmp(city1, adjacency_list->next->from) < 0)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city1);
                    addNodeToAdjacencyList(temp, city2, distance);
                    temp->next = adjacency_list->next;
                    adjacency_list->next = temp;
                }

                    /* And this 'else if' is for the situation, when two cities should be
                     * added to the end of a graph. */

                else if(strcmp(city2, adjacency_list->from) > 0 and adjacency_list->next == NULL)
                {
                    AdjacencyList_t *temp = makeAdjacencyList(city2);
                    adjacency_list->next = temp;
                    addNodeToAdjacencyList(adjacency_list->next, city1, distance);

                    adjacency_list = adjacency_list->next;
                    AdjacencyList_t *temp1 = makeAdjacencyList(city1);
                    adjacency_list->next = temp1;
                    addNodeToAdjacencyList(adjacency_list->next, city2, distance);
                }
                else if(strcmp(city1, adjacency_list->from) > 0 and adjacency_list->next == NULL)
                {
                    AdjacencyList_t * temp = makeAdjacencyList(city1);
                    adjacency_list->next = temp;
                    addNodeToAdjacencyList(adjacency_list->next, city2, distance);
                }
            }
        }
    }
}


/*
 * FUNCTION: addNoCityToTheGraph
 *
 * DESCRIPTION:
 * Use this function when adding a connection -
 * and both cities are already in the graph.
 */

void addNoCityToTheGraph(Graph_t *graph, const char *city1, const char *city2, double distance)
{
    AdjacencyList_t *adjacency_list;

    for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
    {
        if(strcmp(city1, adjacency_list->from) == 0)
            addNodeToAdjacencyList(adjacency_list, city2, distance);
        else if(strcmp(city2, adjacency_list->from) == 0)
            addNodeToAdjacencyList(adjacency_list, city1, distance);
    }
}


/**********************************************************************************************************************/

/* Remove Connection */

/*
 * FUNCTION NAME: removeConnectionMenu
 *
 * DESCRIPTION:
 * Function gets from user two cities, then
 * removes a connection between 'em from graph.
 */

void removeConnectionMenu(Graph_t *graph)
{
    if(graph->head == NULL)
    {
        printErrorUsersActions(EMPTY_GRAPH);
        return;
    }
    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    programError_t what_error = NO_ERROR;
    int counter = 2;

    do
    {
        if((counter % 4) == 1)
            showCityList(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(FIRST_CITY, city1);
        what_error = checkIfNameIsCorrect(city1);
        if (what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city1);
    }
    while (what_error != NO_ERROR);

    counter = 2;
    do
    {
        if((counter % 4) == 1)
            showConnections(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(SECOND_CITY, city2);
        what_error = checkIfNameIsCorrect(city2);

        if (what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city2);

        if(what_error == NO_ERROR)
            what_error = checkIfNamesAreTheSame(city1, city2);

        /* Check if connection is or is not in the graph */

        if(what_error == NO_ERROR)
        {
            if(checkIfConnectionIsInGraph(graph, city1, city2) == CONNECTION_ALREADY_IN_GRAPH)
                what_error = NO_ERROR;
            else
                what_error = NO_SUCH_CONNECTION;
        }
    }
    while (what_error != NO_ERROR);

    /* If everything is fine, then remove connection. */

    removeConnection(graph, city1, city2);
}


/*
 * FUNCTION NAME: removeConnection
 *
 * DESCRIPTION:
 * Function removes connection between city1 and city2 from
 * the graph.
 */

void removeConnection(Graph_t *graph, const char *city1, const char *city2)
{
    AdjacencyList_t * upper, *previous_upper;
    AdjacencyListNode_t *lower, *previous_lower;

    previous_upper = graph->head;

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        previous_lower = upper->head;
        if(strcmp(city1, upper->from) == 0)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                /* Case 1: only city on the adjacency list. */

                if(upper->head->next == NULL and strcmp(city2, lower->to) == 0)
                {
                    free(lower->to);
                    free(lower);

                    /* Case 1-1: upper is first in the graph. */

                    if(upper == graph->head)
                    {
                        graph->head = graph->head->next;
                        free(upper->from);
                        free(upper);
                        upper = graph->head;
                        break;
                    }

                     /* Case 1-2: upper is not first in the graph. */

                    else if(upper != graph->head)
                    {
                        previous_upper->next = upper->next;
                        free(upper->from);
                        free(upper);
                        upper = previous_upper;
                        break;
                    }
                }

                 /* Case 2: more than one city on the adjacency list. */

                else if(upper->head->next != NULL and strcmp(city2, lower->to) == 0)
                {
                    /* Case 2-1: city is first on the adjacency list. */

                    if(lower == upper->head)
                    {
                        upper->head = upper->head->next;
                        free(lower->to);
                        free(lower);
                        break;
                    }

                     /* Case 2-2: city is not first on the adjacency list. */

                    else if(lower != upper->head)
                    {
                        previous_lower->next = lower->next;
                        free(lower->to);
                        free(lower);
                        break;
                    }
                }
                previous_lower = lower;
            }
        }
        previous_upper = upper;
    }

    previous_upper = graph->head;
    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        previous_lower = upper->head;
        if(strcmp(city2, upper->from) == 0)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                /* Case 1: only city on the adjacency list. */

                if(upper->head->next == NULL and strcmp(city1, lower->to) == 0)
                {
                    free(lower->to);
                    free(lower);

                    /* Case 1-1: upper is first in the graph. */

                    if(upper == graph->head)
                    {
                        graph->head = graph->head->next;
                        free(upper->from);
                        free(upper);
                        return;
                    }

                    /* Case 1-2: upper is not first in the graph. */

                    else if(upper != graph->head)
                    {
                        previous_upper->next = upper->next;
                        free(upper->from);
                        free(upper);
                        return;
                    }
                }

                    /* Case 2: more than one city on the adjacency list. */

                else if(upper->head->next != NULL and strcmp(city1, lower->to) == 0)
                {
                    /* Case 2-1: city is first on the adjacency list. */

                    if(lower == upper->head)
                    {
                        upper->head = upper->head->next;
                        free(lower->to);
                        free(lower);
                        return;
                    }

                        /* Case 2-2: city is not first on the adjacency list. */

                    else if(lower != upper->head)
                    {
                        previous_lower->next = lower->next;
                        free(lower->to);
                        free(lower);
                        return;
                    }
                }
                previous_lower = lower;
            }
        }
        previous_upper = upper;
    }
}

/**********************************************************************************************************************/

/* Change distance */

/*
 * FUNCTION NAME: changeDistanceMenu
 *
 * DESCRIPTION:
 * Function gets city1, city2 and a new distance
 * between these cities.
 * Then runs changeDistance() function.
 */

void changeDistanceMenu(Graph_t *graph)
{
    programError_t what_error = NO_ERROR;
    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    double distance = 0;
    int counter = 2;

    if(graph->head == NULL)
    {
        printErrorUsersActions(EMPTY_GRAPH);
        return;
    }

    do
    {
        if((counter % 4 ) == 1)
            showCityList(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(FIRST_CITY, city1);
        what_error = checkIfNameIsCorrect(city1);
        if(what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city1);
    }
    while (what_error != NO_ERROR);

    counter = 2;
    do
    {
        if((counter % 4) == 1)
            showConnections(graph);
        ++counter;
        printErrorUsersActions(what_error);
        getCitysName(SECOND_CITY, city2);
        what_error = checkIfNameIsCorrect(city2);
        if(what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city2);
        if(what_error == NO_ERROR)
            what_error = checkIfNamesAreTheSame(city1, city2);

        /* Check if connection is or is not already in the graph */

        if(what_error == NO_ERROR)
        {
            if(CONNECTION_ALREADY_IN_GRAPH == checkIfConnectionIsInGraph(graph, city1, city2))
                what_error = NO_ERROR;
            else
                what_error = NO_SUCH_CONNECTION;
        }
    }
    while (what_error != NO_ERROR);

    do
    {
        printErrorUsersActions(what_error);
        getDistanceBetweenCities(&distance);
        what_error = checkIfDistanceIsCorrect(distance);
    }
    while (what_error != NO_ERROR);

    changeDistance(graph, city1, city2, distance);
    clearBuffer();
}


/*
 * FUNCTION NAME: changeDistance
 *
 * DESCRIPTION:
 * Function changes a distance between city1 and city2.
 */

void changeDistance(Graph_t *graph, const char *city1, const char *city2, double distance)
{
    AdjacencyList_t *upper;
    AdjacencyListNode_t *lower;

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        if(strcmp(city1, upper->from) == 0)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                if(strcmp(city2, lower->to) == 0)
                    lower->distance = distance;
            }
        }
        else if(strcmp(city2, upper->from) == 0)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                if(strcmp(city1, lower->to) == 0)
                    lower->distance = distance;
            }
        }
    }
}

