/*
 * FILE NAME: ListCreation.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 21.04.2016
 *
 * DESCRIPTION:
 *
 * Here are definitions of functions that are used to check if DataBase.txt
 * file is properly filled, counts how many unique cities there are and
 * from how many nodes will graph be made of.
 * Creates connections_list and unique_cities_list.
 */

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
#include "ErrorCodes.h"
#include "ListCreation.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: createLists
 *
 * DESCRIPTION:
 * This function main task is to fill list unique_cities_list and
 * connections_list with proper data.
 */

void createLists(ConnectionsList_t* connections_list, UniqueCitiesList_t* unique_cities_list)
{
    /* Arrays needed to compare strings (cities names) read from DataBase.txt. */

    char city1[G_CITYS_NAME_LENGTH], city2[G_CITYS_NAME_LENGTH];

    /* Number of connections between cities in the DataBase.txt file.*/

    size_t number_of_connections = 0;

    /* Distance between two cites */

    double distance;
    FILE* fp;

    if ((fp = fopen("../res/DataBase.txt", "r")) == NULL) {
        printDataBaseError(CANT_OPEN_FILE);
        return;
    }

    /* Scan DataBase.txt and if file is wrongly filled (f.e. "city1 distance" - missing city2) then quit.
     * Otherwise check if connection was or was not on the list - if was, then return.
     * If was not, then add connection to the list lst and increase number of connections in the graph. */

    int result;
    while ((result = fscanf(fp, "%s %s %lf\n", city1, city2, &distance)) != EOF) {
        if (result == 0 or result == 1 or result == 2) {
            printDataBaseError(BAD_FORMAT);
            fclose(fp);
            return;
        }
        if (checkIfNameIsCorrect(city1) != NO_ERROR) {
            printDataBaseError(INCORRECT_NAME);
            fclose(fp);
            return;
        }
        if (checkIfNameIsCorrect(city2) != NO_ERROR) {
            printDataBaseError(INCORRECT_NAME);
            fclose(fp);
            return;
        } else if (checkIfNamesAreIdentical(city1, city2) != NO_ERROR) {
            printDataBaseError(IDENTICAL_NAMES);
            fclose(fp);
            return;
        } else if (distance <= 0) {
            printDataBaseError(INCORRECT_DISTANCE);
            fclose(fp);
            return;
        } else if (checkIfAlreadyOnTheList(connections_list, city1, city2) != NO_ERROR) {
            printDataBaseError(ALREADY_ON_THE_LIST);
            fclose(fp);
            return;
        }
        addConnectionToTheList(connections_list, city1, city2, distance);
        ++number_of_connections;
    }

    if (0 == number_of_connections) {
        printDataBaseError(NO_CONNECTIONS);
        fclose(fp);
        return;
    }

    /* Now check if for every City1-City2 connection there is
     * City2-City1 connection. */

    if (checkIfConnectionsAreUndirected(connections_list) != NO_ERROR) {
        printDataBaseError(DIRECTED_CONNECTION);
        fclose(fp);
        return;
    }

    /* And check, if distance from City1->City2 is the same like
     * from City2->City1. */

    if (checkIfDistancesAreOK(connections_list) != NO_ERROR) {
        printDataBaseError(DIFFERENT_DISTANCE);
        fclose(fp);
        return;
    }

    /* If everything is fine then fill all_cities list. */

    addUniqueCitiesToTheList(connections_list, number_of_connections, unique_cities_list);
    fclose(fp);
}

/*
 * FUNCTION NAME: checkIfAlreadyOnTheList
 *
 * DESCRIPTION:
 * This function checks, if connection city1-city2 was earlier on the
 * list *connections_list.
 *
 * RETURNS:
 * ALREADY_ON_THE_LIST, if connection was already on the list.
 * NO_ERROR, if otherwise.
 */

programError_t checkIfAlreadyOnTheList(ConnectionsList_t* connections_list, const char* city1, const char* city2)
{
    ConnectionsListNode_t* current;
    size_t counter = 0;
    for (current = connections_list->head; current != NULL; current = current->next) {
        if ((strcmp(city1, current->from) == 0) and ((strcmp(city2, current->to)) == 0)) {
            ++counter;
        }
    }
    if (counter != 0) {
        return ALREADY_ON_THE_LIST;
    } else {
        return NO_ERROR;
    }
}

/*
 * FUNCTION NAME: addConnectionToTheList
 *
 * DESCRIPTION:
 * This function adds a node to the ConnectionsList_t *connections_list.
 * Note: it's addHead, not addTail way of adding a node.
 */

void addConnectionToTheList(ConnectionsList_t* connections_list, const char* city1, const char* city2, double distance)
{
    ConnectionsListNode_t* temp = makeConnectionsListNode(city1, city2, distance);
    if (connections_list->head != NULL) {
        temp->next = connections_list->head;
    }
    connections_list->head = temp;
}

/*
 * FUNCTION NAME: makeConnectionsListNode
 *
 * DESCRIPTION:
 * This function creates cityListNode (node of a ConnectionsList_t *lst)
 * and fills it with proper values.
 *
 * RETURNS:
 * node - created node that will be added to ConnectionsList_t *lst.
 */

ConnectionsListNode_t* makeConnectionsListNode(const char* city1, const char* city2, double distance)
{
    ConnectionsListNode_t* node;

    node = (ConnectionsListNode_t*)malloc(sizeof(ConnectionsListNode_t));
    checkMemory(node);
    node->from = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->from);
    node->to = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->to);

    strcpy(node->from, city1);
    strcpy(node->to, city2);
    node->distance = distance;
    node->next = NULL;

    return node;
}

/*
 * FUNCTION NAME: addUniqueCitiesToTheList
 *
 * DESCRIPTION:
 * Unique cities from DataBase.txt file are being added to unique_cities list.
 */

void addUniqueCitiesToTheList(ConnectionsList_t* connections_list, size_t number_of_connections, UniqueCitiesList_t* unique_cities)
{
    /* Variables used in loop. */

    size_t i, j;

    /* Since finding unique strings in a singly linked
     * list in a C language is a pain in the ass, let's make it
     * in a simpler way...
     * First, create arrays for cities from DataBase.txt file.
     * IF CITY'S NAME IS MULTIPLE TIMES IN A FILE, IT WILL
     * BE ADDED MULTIPLE TIMES TO THE ARRAY.
     * Dynamics arrays are needed, because strCmp function won't
     * work otherwise. */

    /* Array that will contain name of every city
     * that is in DataBase.txt file. */

    char** tab_all = malloc(2 * number_of_connections * sizeof(char*));
    checkMemory(tab_all);

    for (i = 0; i < 2 * number_of_connections; ++i) {
        tab_all[i] = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
        checkMemory(tab_all[i]);
    }

    /* Copy cities' names to tab_all array. */

    ConnectionsListNode_t* city_node;
    j = 0;
    for (city_node = connections_list->head; city_node != NULL; city_node = city_node->next) {
        strcpy(tab_all[j++], city_node->from);
        strcpy(tab_all[j++], city_node->to);
    }

    /* Now sort the array in descending alphabetical order.
     * The reason for descending order is the way how we add nodes
     * to the list - function addUniqueCityToTheList adds head to the list, not tail.
     * So the first element from tab_all will end as the last one
     * on the list.
     * Sorting is being done by built-in qsort function. */

    qsort(tab_all, 2 * number_of_connections, sizeof(char*), stringCmp);

    /* Now add cities to the list.
     * First, add city from tab[0] and then search for
     * unique cities. If one is found, then add it to the list. */

    addUniqueCityToTheList(unique_cities, tab_all[0]);
    for (i = 0; i < 2 * number_of_connections - 1; ++i) {
        if (0 != strcmp(tab_all[i], tab_all[i + 1])) {
            addUniqueCityToTheList(unique_cities, tab_all[i + 1]);
        }
    }

    /* Remove dynamic arrays from the memory. */

    for (i = 0; i < 2 * number_of_connections; ++i) {
        free(tab_all[i]);
    }
    free(tab_all);
}

/*
 * FUNCTION NAME: addUniqueCityToTheList
 *
 * DESCRIPTION:
 * This function adds a new node to city_list list.
 * It adds a new head to the list, so previous first
 * element is now second, previous second is third, and
 * so on.
 */

void addUniqueCityToTheList(UniqueCitiesList_t* unique_city_list, const char* city)
{
    UniqueCitiesListNode_t* node = makeUniqueCityNode(city);
    if (unique_city_list->head == NULL) {
        unique_city_list->head = node;
    } else {
        node->next = unique_city_list->head;
        unique_city_list->head = node;
    }
}

/*
 * FUNCTION NAME: makeUniqueCityNode
 *
 * DESCRIPTION:
 * This function allocates memory for a new node and
 * fills it with the name of a city being added to the list.
 *
 * RETURNS:
 * node - created UniqueCitiesListNode_t type node.
 */

UniqueCitiesListNode_t* makeUniqueCityNode(const char* city)
{
    UniqueCitiesListNode_t* node = (UniqueCitiesListNode_t*)malloc(sizeof(UniqueCitiesListNode_t));
    checkMemory(node);
    node->city = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->city);
    node->next = NULL;
    strcpy(node->city, city);
    return node;
}

/*
 * FUNCTION NAME: stringCmp
 *
 * ARGUMENTS:
 * *p1, *p2 - pointers to arrays that contain cities names.
 *
 * DESCRIPTION:
 * This function compares two strings and returns value
 * depending on which one is bigger (in alphabetical order).
 *
 * RETURNS:
 * 0 if strings are exactly the same,
 * positive value, if p1 contains string that is lesser (in alphabetical order) than p2,
 * negative value, if otherwise.
 *
 * Note: This function is case-sensitive, f.e. york and York are not the same.
 */

int stringCmp(const void* p1, const void* p2)
{
    return strcmp(*(char* const*)p1, *(char* const*)p2);
}

/*
 * FUNCTION NAME: checkIfConnectionsAreUndirected
 *
 * DESCRIPTION:
 * Functions checks, if connections are undirected, i.e.
 * checks, if there is A-B and B-A for every connection in
 * DataBase.txt
 *
 * RETURNS:
 * NO_ERROR - if everything is fine.
 *
 * DIRECTED_CONNECTION - if there is A-B connection
 * and there is not B-A connection in DataBase.txt file.
 */

programError_t checkIfConnectionsAreUndirected(const ConnectionsList_t* connections_list)
{
    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    ConnectionsListNode_t *outer, *inner;
    unsigned int number_of_connections;

    for (outer = connections_list->head; outer != NULL; outer = outer->next) {
        number_of_connections = 0;
        strcpy(city1, outer->from);
        strcpy(city2, outer->to);
        for (inner = connections_list->head; inner != NULL; inner = inner->next) {
            if (strcmp(city2, inner->from) == 0 and strcmp(city1, inner->to) == 0)
                ++number_of_connections;
        }
        if (number_of_connections == 0)
            return DIRECTED_CONNECTION;
    }
    return NO_ERROR;
}

/*
 * FUNCTION NAME: checkIfDistancesAreOK
 *
 * DESCRIPTION:
 * Function checks, if distance from city1 to city2
 * is exactly the same like from city2 to city1.
 *
 * RETURNS:
 * NO_ERROR - if everything is alright.
 *
 * DIFFERENT_DISTANCE - if it ain't.
 */

programError_t checkIfDistancesAreOK(const ConnectionsList_t* connections_list)
{
    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    ConnectionsListNode_t *outer, *inner;
    double distance;

    for (outer = connections_list->head; outer != NULL; outer = outer->next) {
        strcpy(city1, outer->from);
        strcpy(city2, outer->to);
        distance = outer->distance;
        for (inner = connections_list->head; inner != NULL; inner = inner->next) {
            if (strcmp(city2, inner->from) == 0 and strcmp(city1, inner->to) == 0) {
                if (distance != inner->distance) {
                    return DIFFERENT_DISTANCE;
                }
            }
        }
    }
    return NO_ERROR;
}
