/*
 * FILE NAME: GraphCreation.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 20.04.2016
 *
 * DESCRIPTION:
 *
 * Here are the definitions of functions used
 * to create our graph, add edges and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"
#include "ErrorCodes.h"
#include "GraphCreation.h"

/**********************************************************************************************************************/

/* Definitions*/

/*
 * FUNCTION NAME: graphCreation
 *
 * DESCRIPTION:
 * Main task of this function is to create a graph that will be
 * passed to Dijkstra's algorithm function. Firstly, it gets the number
 * of adjacency lists and allocates memory for it.
 * Then adds edges to the adjacency lists.
 *
 * RETURNS:
 * graph - created list of adjacency lists.
 */

Graph_t* graphCreation(void)
{
    Graph_t* graph; /* Graph that contains all edges and vertices. */
    ConnectionsList_t connections_list; /* Singly linked list contains every connection from DataBase.txt. */
    UniqueCitiesList_t unique_cities_list; /* Singly linked list that contains every unique city. */

    /* Allocate memory for graph and set initial values
     * of lists to NULL. */

    graph = createGraph();
    connections_list.head = NULL;
    unique_cities_list.head = NULL;

    /* Now fill unique_cities_list and connections_list with proper data.
     * Cities from unique_cities_list will create nodes
     * for adjacency lists. Then add edges to the adjacency lists'
     * nodes. */

    createLists(&connections_list, &unique_cities_list);

    /* If DataBase.txt is correctly filled... */

    if (unique_cities_list.head != NULL) {
        addEdgesToGraph(graph, connections_list, &unique_cities_list);
        removeUniqueCitiesList(&unique_cities_list);
    }

    /* Free the memory and return created graph. */

    removeConnectionsList(&connections_list);
    return graph;
}

/*
 * FUNCTION NAME: createGraph
 *
 * DESCRIPTION:
 * Function allocates memory for a graph and set its
 * initial values to NULL.
 *
 * RETURNS:
 * graph - created graph.
 */

Graph_t* createGraph(void)
{
    Graph_t* graph;
    graph = (Graph_t*)malloc(sizeof(Graph_t));
    checkMemory(graph);
    graph->head = NULL;
    return graph;
}

/*
 * FUNCTION NAME: addEdgesToGraph
 *
 * DESCRIPTION:
 * Function adds edges to the graph, i.e. elements of unique_cities_list list
 * will create nodes that will contain heads to adjacency list. Then it will fill adjacency lists
 * with proper cities (in alphabetical order).
 */

void addEdgesToGraph(Graph_t* graph, ConnectionsList_t connections_list, UniqueCitiesList_t* unique_cities_list)
{
    /* First, add a node to the graph (i.e. add a node to the list that
     * contains heads to adjacency lists). Then, if there is a connection from or to this
     * city that is in the node, add edge to the adjacency list.
     *
     * Note: it will add a node to keep adjacency list in alphabetical order. */

    ConnectionsListNode_t* city;
    UniqueCitiesListNode_t* cityList;
    for (cityList = unique_cities_list->head; cityList != NULL; cityList = cityList->next) {
        addAdjacencyList(graph, cityList->city);
        for (city = connections_list.head; city != NULL; city = city->next) {
            if (strcmp(cityList->city, city->from) == 0) {
                addNodeToAdjacencyList(graph->head, city->to, city->distance);
            }
        }
    }
}

/*
 * FUNCTION NAME: addNodeToAdjacencyList
 *
 * DESCRIPTION:
 * Calls the function that creates node. Then
 * adds a node as a head of the list.
 */

void addNodeToAdjacencyList(AdjacencyList_t* adjacency_list, const char* to, double distance)
{
    AdjacencyListNode_t* node = makeAdjacencyListNode(to, distance);
    AdjacencyListNode_t* temp1;

    /* If adjacency list is empty, then create head.
     * If it is not, then check two cases: if there is one element
     * on the list only or if there are more. */

    if (adjacency_list->head == NULL) { /* Empty adjacency list. */
        adjacency_list->head = node;
    } else {
        if (adjacency_list->head->next == NULL) { /* Adjacency list with only 1 element. */
            if (strcmp(to, adjacency_list->head->to) > 0) { /* Compare, if city that is about to be added should */
                adjacency_list->head->next = node; /* be before or after element that is already on the list. */
            } else if (strcmp(to, adjacency_list->head->to) < 0) {
                node->next = adjacency_list->head;
                adjacency_list->head = node;
            }
        }

        /* If there are more elements on the list, then search
             * where element should be added.
             * If previous element is lesser and next is greater (in alphabetical order)
             * then add a node here. */

        else if (adjacency_list->head->next != NULL) {
            /* If added element will be first on the list. */

            if (strcmp(to, adjacency_list->head->to) < 0) {
                node->next = adjacency_list->head;
                adjacency_list->head = node;
            }

            /* If added element won't be first on the list. */

            else {
                for (temp1 = adjacency_list->head; temp1 != NULL; temp1 = temp1->next) {
                    /* If added element will be in the middle of the list. */

                    if (temp1->next != NULL && strcmp(to, temp1->to) > 0 && strcmp(to, temp1->next->to) < 0) {
                        node->next = temp1->next;
                        temp1->next = node;
                        break;
                    }

                    /* If added element will be at the end of the list. */

                    else if (temp1->next == NULL && strcmp(to, temp1->to) > 0) {
                        temp1->next = node;
                    }
                }
            }
        }
    }
}

/*
 * FUNCTION NAME: makeAdjacencyListNode
 *
 * DESCRIPTION:
 * Function creates a node that is in adjacency list node.
 *
 * RETURNS:
 * node - created node with filled values.
 */

AdjacencyListNode_t* makeAdjacencyListNode(const char* to, double distance)
{
    AdjacencyListNode_t* node;
    node = (AdjacencyListNode_t*)malloc(sizeof(AdjacencyListNode_t));
    checkMemory(node);
    node->to = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->to);
    strcpy(node->to, to);
    node->distance = distance;
    node->next = NULL;
    return node;
}

/*
 * FUNCTION NAME: addAdjacencyList
 *
 * DESCRIPTION:
 * Function adds a node as a head to adjacency list.
 */

void addAdjacencyList(Graph_t* graph, const char* from)
{
    AdjacencyList_t* node = makeAdjacencyList(from);
    if (graph->head != NULL) {
        node->next = graph->head;
    }
    graph->head = node;
}

/*
 * FUNCTION NAME: makeAdjacencyList
 *
 * DESCRIPTION:
 * Function creates a adjacency list node and fills it with
 * proper values.
 *
 * RETURNS:
 * node - created node.
 */

AdjacencyList_t* makeAdjacencyList(const char* from)
{
    AdjacencyList_t* node;
    node = (AdjacencyList_t*)malloc(sizeof(AdjacencyList_t));
    checkMemory(node);
    node->from = (char*)malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->from);
    node->head = NULL;
    node->next = NULL;
    strcpy(node->from, from);
    return node;
}

/*
 * FUNCTION NAME: removeAdjacencyListNodes
 *
 * DESCRIPTION:
 * Function removes every dynamically allocated
 * variable that is in node.
 */

void removeAdjacencyListNodes(AdjacencyListNode_t* head)
{
    AdjacencyListNode_t *current, *previous;
    for (current = head; current != NULL;) {
        previous = current;
        current = current->next;
        free(previous->to);
        free(previous);
    }
}

/*
 * FUNCTION NAME: removeConnectionsList
 *
 * DESCRIPTION:
 * Function frees memory from dynamically allocated char arrays.
 */

void removeConnectionsList(ConnectionsList_t* connections_list)
{
    ConnectionsListNode_t* temp;
    temp = connections_list->head;
    while (temp != NULL) {
        connections_list->head = connections_list->head->next;
        free(temp->from);
        free(temp->to);
        free(temp);
        temp = connections_list->head;
    }
}

/*
 * FUNCTION NAME: removeGraph
 *
 * DESCRIPTION:
 * Function frees every dynamically allocated variable
 * that graph contains.
 */

void removeGraph(Graph_t* graph)
{
    AdjacencyList_t *current, *previous;
    for (current = graph->head; current != NULL;) {
        free(current->from);
        previous = current;
        current = current->next;
        removeAdjacencyListNodes(previous->head);
        free(previous);
    }
    free(graph);
}

/*
 * FUNCTION NAME: removeUniqueCitiesList
 *
 * DESCRIPTION:
 * Function frees memory from dynamically allocated elements.
 */

void removeUniqueCitiesList(UniqueCitiesList_t* unique_cities)
{
    UniqueCitiesListNode_t* temp;
    temp = unique_cities->head;
    while (temp != NULL) {
        unique_cities->head = unique_cities->head->next;
        free(temp->city);
        free(temp);
        temp = unique_cities->head;
    }
}

/*
 * FUNCTION NAME: updateDataBaseFile
 *
 * DESCRIPTION:
 * Function saves connections in alphabetical
 * order in DataBase.txt file.
 */

void updateDataBaseFile(const Graph_t* graph)
{
    FILE* fp;
    if ((fp = fopen("../res/DataBase.txt", "w")) == NULL) {
        printDataBaseError(CANT_UPDATE_FILE);
        return;
    }
    AdjacencyList_t* adjacency_list;
    AdjacencyListNode_t* adjacency_list_node;

    for (adjacency_list = graph->head; adjacency_list != NULL; adjacency_list = adjacency_list->next) {
        for (adjacency_list_node = adjacency_list->head; adjacency_list_node != NULL; adjacency_list_node = adjacency_list_node->next) {
            fprintf(fp, "%s %s %.2lf\n", adjacency_list->from, adjacency_list_node->to, adjacency_list_node->distance);
        }
    }
    fclose(fp);
}

/*
 * FUNCTION NAME: updateOrdinalNumbers
 *
 * DESCRIPTION:
 * Function updates cities' ordinal numbers in the graph.
 */

void updateOrdinalNumbers(Graph_t* graph)
{
    AdjacencyList_t *upper, *compare;
    AdjacencyListNode_t* lower;
    unsigned int ordinal_number = 0;

    /* Firstly, set ordinal numbers in the "upper" list. */

    for (upper = graph->head; upper != NULL; upper = upper->next) {
        upper->ordinal_number = ordinal_number++;
    }

    /* Then, set ordinal numbers in "lower" lists. */

    /* Firstly, take an element from "upper" list. */

    for (upper = graph->head; upper != NULL; upper = upper->next) {
        /* Then take an element from "lower" list. */

        for (lower = upper->head; lower != NULL; lower = lower->next) {
            /* Then search for element in "upper" list that matches an element
             * from "lower" list. */

            for (compare = graph->head; compare != NULL; compare = compare->next) {
                /* If names are identical (elements are matched) then update the
                 * ordinal number in element from "lower" list to the same ordinal number
                 * as in "upper" list. */

                if (strcmp(lower->to, compare->from) == 0) {
                    lower->ordinal_number = compare->ordinal_number;
                    break;
                }
            }
        }
    }
}
