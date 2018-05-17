/*
 * FILE NAME: ErrorsHandling.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 25.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains functions that are used to check
 * if given city's name is correct or if typed in connection
 * can be removed from the graph, and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <iso646.h>
#include <string.h>

#include "ErrorCodes.h"
#include "ErrorsHandling.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: checkIfNameIsCorrect
 *
 * DESCRIPTION:
 * Function checks, if given name is or is not
 * a proper city's name (if contains signs other than
 * 'a'-"z' and 'A'-'Z' it is wrong).
 *
 * RETURNS:
 * INCORRECT_NAME - if name is wrong.
 * NO_ERROR - if name is correct.
 */

programError_t checkIfNameIsCorrect(const char *city)
{
    if(city[0] == '\n' or city[0] == '\0')
        return INCORRECT_NAME;
    for(int i = 0; city[i] != '\0'; ++i)
    {
        if ((city[i] < 'a' or city[i] > 'z') and (city[i] < 'A' or city[i] > 'Z'))
            return INCORRECT_NAME;
    }
    return NO_ERROR;
}


/*
 * FUNCTION NAME: checkIfIsInGraph
 *
 * DESCRIPTION:
 * Function checks, if given city is in the graph.
 *
 * RETURNS:
 * NO_ERROR - city is in the graph.
 *
 * NO_SUCH_CITY - there is no city in the graph.
 */

programError_t checkIfIsInGraph(const Graph_t *graph, const char *city)
{
    AdjacencyList_t *adjacency_list;
    for(adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next)
    {
        if(strcmp(adjacency_list->from, city) == 0)
            return NO_ERROR;
    }
    return NO_SUCH_CITY;
}


/*
 * FUNCTION NAME: checkIfDistanceIsCorrect
 *
 * DESCRIPTION:
 * Function checks, if given distance is greater
 * than 0.
 *
 * RETURNS:
 * INCORRECT_DISTANCE - if distance is <= 0.
 * NO_ERROR - if otherwise.
 */

programError_t checkIfDistanceIsCorrect(double distance)
{
    if(distance <= 0)
    {
        clearBuffer();
        return INCORRECT_DISTANCE;
    }
    else
        return NO_ERROR;
}


/*
 * FUNCTION NAME: checkIfConnectionIsInGraph
 *
 * DESCRIPTION:
 * Function checks, if connection is or is not already
 * in the graph.
 *
 * RETURNS:
 * NO_ERROR - connection can be added.
 * CONNECTION_ALREADY_IN_GRAPH - if otherwise.
 */

programError_t checkIfConnectionIsInGraph(const Graph_t *graph, const char *city1, const char *city2)
{
    AdjacencyList_t *upper;
    AdjacencyListNode_t *lower;

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        for(lower = upper->head; lower != NULL; lower = lower->next)
        {
            if(strcmp(city1, upper->from) == 0 and strcmp(city2, lower->to) == 0)
                return CONNECTION_ALREADY_IN_GRAPH;
        }
    }
    return NO_ERROR;
}


/*
 * FUNCTION NAME: checkUsersChoiceMainMenu
 *
 * DESCRIPTION:
 * Function is used to check, if user's input is correct.
 * User's input is wrong if:
 * - he didn't type only 1 sign (choice[1] != '\n');
 * - typed sign is not a number (!isdigit(choice[0]);
 *
 * RETURNS:
 * TOO_MANY_SIGNS, NO_DIGIT - error codes.
 * NO_ERROR - user's input is correct and there is no error.
 */

programError_t checkUsersChoiceMainMenu(const char *choice, int *number)
{
    if(choice[1] != '\n' and choice[2] != '\n')
    {
        clearBuffer();
        return TOO_MANY_SIGNS;
    }
    else
    {
        if(!isdigit(choice[0]))
            return NO_DIGIT;
        else
        {
            *number = atoi(&choice[0]);                 /* if everything is fine, number = atoi(...) */
            return NO_ERROR;
        }
    }
}


/*
 * FUNCTION NAME: checkIfNamesAreTheSame
 *
 * DESCRIPTION:
 * Function checks, if given names are the same or not.
 *
 * RETURNS:
 * SAME_NAME - if names are the same.
 * NO_ERROR - if they are not.
 */

programError_t checkIfNamesAreTheSame(const char *city1, const char *city2)
{
    if(strcmp(city1, city2) == 0)
        return SAME_NAME;
    else
        return NO_ERROR;
}


/*
 * FUNCTION NAME: checkMemory
 *
 * Description:
 * Function checks, if memory has been properly allocated.
 * If not, then quit the program.
 */

void checkMemory(void *memory)
{
    if(memory == NULL)
    {
        errno = ENOMEM;
        printErrorSystem(CANT_ALLOCATE_MEMORY);
        exit(EXIT_FAILURE);
    }
}

/*
 * FUNCTION NAME: clearBuffer
 *
 * DESCRIPTION:
 * Function clears input buffer.
 */

void clearBuffer(void)
{
    int c;
    while((c = getchar() != '\n') and (c != EOF));
}


