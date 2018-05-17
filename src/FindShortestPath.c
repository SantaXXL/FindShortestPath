/*
 * FILE NAME: FindShortestPath.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 03.05.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of functions, that
 * are used to find a shortest path between two cities.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "Constants.h"
#include "ErrorCodes.h"
#include "FindShortestPath.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: findShortestPathMenu
 *
 * DESCRIPTION:
 * This function gets cities names from user
 * and then calls findShortestPath() function to find
 * a shortest path between them.
 */

void findShortestPathMenu(Graph_t *graph)
{
    if(graph->head == NULL)
    {
        printErrorUsersActions(EMPTY_GRAPH);
        return;
    }

    char city1[G_CITYS_NAME_LENGTH];
    char city2[G_CITYS_NAME_LENGTH];
    programError_t what_error = NO_ERROR;

    do          /* Get the name of city1. */
    {
        printErrorUsersActions(what_error);
        getCitysName(FIRST_CITY, city1);
        what_error = checkIfNameIsCorrect(city1);
        if(what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city1);
    }
    while(what_error != NO_ERROR);

    do          /* Get the name of city2. */
    {
        printErrorUsersActions(what_error);
        getCitysName(SECOND_CITY, city2);
        what_error = checkIfNameIsCorrect(city2);
        if(what_error == NO_ERROR)
            what_error = checkIfNamesAreTheSame(city1, city2);
        if(what_error == NO_ERROR)
            what_error = checkIfIsInGraph(graph, city2);
    }
    while(what_error != NO_ERROR);

    /* Update ordinal numbers in the graph. */

    updateOrdinalNumbers(graph);

    findShortestPath(graph, city1, city2);
}


/*
 * FUNCTION NAME: findShortestPath
 *
 * DESCRIPTION:
 * Function searches for shortest path between city1 and city2.
 * Dijkstra's algorithm is used.
 */

void findShortestPath(const Graph_t *graph, const char *source, const char *destination)
{
    unsigned int i;
    shortest_path path;     /* Contains names of cities that create shortest path. */
    path.head = NULL;
    size_t number_of_vertices = 0;
    unsigned int source_number = 0;
    unsigned int destination_number = 0;
    AdjacencyList_t *upper;

    /* Firstly, find the number of vertices (cities) in the graph.
     * Also, find which node in graph is a source and which one is a
     * destination. */

    for(upper = graph->head; upper != NULL; upper = upper->next)
    {
        ++number_of_vertices;
        if(strcmp(upper->from, source) == 0)
            source_number = upper->ordinal_number;
        if(strcmp(upper->from, destination) == 0)
            destination_number = upper->ordinal_number;
    }

    /* Remember a name of every city in the array - will be easier
     * to show a shortest path, (there will be no need to search whole graph
     * just to find the name of i-th city). */

    char **cities_names = malloc(number_of_vertices * sizeof(char *));
    checkMemory(cities_names);
    for(i = 0; i < number_of_vertices; ++i)
    {
        cities_names[i] = malloc(G_CITYS_NAME_LENGTH * sizeof(char));
        checkMemory(cities_names[i]);
    }
    i = 0;
    for(upper = graph->head; upper != NULL; upper = upper->next)
        strcpy(cities_names[i++], upper->from);

    /* distance_array, i.e. cost of a path from source to i-th vertex. */

    double distance_array[number_of_vertices];
    for(i = 0; i < number_of_vertices; ++i)
        distance_array[i] = LLONG_MAX;
    distance_array[source_number] = 0;

    /* previous_vertex_array - this array remembers every previous vertex
     * before entering a next one (which ends shortest path from source to this vertex),
     * e.g. if shortest path will be 0->3->4, thus
     * pva[0] = -1, pva[3] = 0, pva[4] = 3. */

    int previous_vertex_array[number_of_vertices];
    for(i = 0; i < number_of_vertices; ++i)
        previous_vertex_array[i] = -1;

    /* Now initialize priority queue - min. binary heap.
     * Note: The lesser key is, the higher priority it has. */

    PQNode_t ** priority_queue;
    priority_queue = (PQNode_t **)malloc(number_of_vertices * sizeof(PQNode_t *));
    checkMemory(priority_queue);
    for(i = 0; i < number_of_vertices; ++i)
    {
        priority_queue[i] = (PQNode_t *)malloc(sizeof(PQNode_t));
        checkMemory(priority_queue[i]);
        priority_queue[i]->city_number = i;
        priority_queue[i]->key = LLONG_MAX;
    }

    /* Now set minimal key to source and rebuild the heap. */

    priority_queue[0]->key = 0;
    priority_queue[0]->city_number = source_number;
    priority_queue[source_number]->city_number = 0;

    /* Everything is ready, run the algorithm. */

    DijkstrasAlgorithm(priority_queue, number_of_vertices, destination_number, graph, distance_array, previous_vertex_array);

    /* Distance array is filled, previous_vertex_array is filled, so show the path. */

    setPath(&path, destination_number, previous_vertex_array, cities_names);
    showThePath(path, destination, source, destination_number, distance_array);

    /* Free memory. */

    shortest_path_list *temp, *previous;
    for(temp = path.head; temp != NULL;)
    {
        previous = temp;
        free(temp->citys_name);
        temp = temp->next;
        free(previous);
    }
    for(i = 0; i < number_of_vertices; ++i)
        free(cities_names[i]);
    free(cities_names);
}


/*
 * FUNCTION NAME: DijkstrasAlgorithm
 *
 * DESCRIPTION:
 * This function runs Dijkstra's algorithm.
 * Stops when priority queue is empty or shortest path to destination had been found.
 */

void DijkstrasAlgorithm(PQNode_t **priority_queue, size_t number_of_vertices, unsigned int destination_number,
                        const Graph_t *graph, double *distance_array, int *previous_vertex_array)
{
    while(priority_queue[0] != NULL)
    {
        /* Find neighbours and update distance_array. */

        updateDistanceArray(priority_queue[0]->city_number, distance_array, graph, previous_vertex_array);

        /* If the path to destination is found, stop the algorithm. */

        if(priority_queue[0]->city_number == destination_number)
            break;

        /* Now extract minimal element from the tree (i.e. remove root).
         * Then replace it with last element of the tree and decrease number
         * of vertices and rebuild the heap. */

        extractMin(priority_queue, &number_of_vertices);

        /* Decrease the keys in priority queue after updating a distance array. */

        decreaseKeys(distance_array, priority_queue, &number_of_vertices);

    }
    /* Remove priority queue from the memory. */

    while(priority_queue[0] != NULL)
        removeLastPQ(priority_queue, &number_of_vertices);
    free(priority_queue);
}


/*
 * FUNCTION NAME: heapifyRoot
 *
 * DESCRIPTION:
 * After removing root in function extractMin, the heap is breached.
 * So rebuild it.
 *
 * COPYRIGHTS:
 * This 'algorithm' is created by Jerzy Wałaszek.
 * Step 8: http://eduinf.waw.pl/inf/alg/001_search/0138.php
 */

void heapifyRoot(PQNode_t **priority_queue, size_t number_of_vertices, unsigned int parent)
{
    unsigned int left, right, pmin;
    double dmin;
    left = parent * 2 + 1;
    right = left + 1;

    if(left >= number_of_vertices)
        return;
    dmin = priority_queue[left]->key;
    pmin = left;

    if(right < number_of_vertices)
    {
        if(dmin > priority_queue[right]->key)
        {
            dmin = priority_queue[right]->key;
            pmin = right;
        }
    }

    if(priority_queue[parent]->key <= dmin)
        return;
    swapPQNodes(priority_queue, parent, pmin);
    parent = pmin;
    heapifyRoot(priority_queue, number_of_vertices, parent);
}


/*
 * FUNCTION NAME: heapify
 *
 * DESCRIPTION:
 * Function rebuilds the heap after one of it nodes had been
 * changed.
 *
 * COPYRIGHTS:
 * This 'algorithm' is created by Jerzy Wałaszek.
 * Step 10: http://eduinf.waw.pl/inf/alg/001_search/0138.php
 */

void heapify(PQNode_t **priority_queue, size_t number_of_vertices, unsigned int child)
{
    unsigned int parent;
    if(child == 0)
        return;

    parent = (unsigned int)floor((child - 1) / 2);
    if(priority_queue[parent]->key <= priority_queue[child]->key)
        return;
    swapPQNodes(priority_queue, parent, child);
    child = parent;
    heapify(priority_queue, number_of_vertices, child);
}


/*
 * FUNCTION NAME: swapPQNodes
 *
 * DESCRIPTION:
 * Function swaps 2 nodes in the tree.
 */

void swapPQNodes(PQNode_t **priority_queue, unsigned int minimal, unsigned int current)
{
    double temp_priority;
    unsigned int temp_city_number;
    temp_city_number = priority_queue[minimal]->city_number;
    temp_priority = priority_queue[minimal]->key;
    priority_queue[minimal]->city_number = priority_queue[current]->city_number;
    priority_queue[minimal]->key = priority_queue[current]->key;
    priority_queue[current]->key = temp_priority;
    priority_queue[current]->city_number = temp_city_number;
}


/*
 * FUNCTION NAME: DecreaseKeys
 *
 * DESCRIPTION:
 * Function updates keys in priority queue and then rebuilds the heap.
 */

void decreaseKeys(double *distance_array, PQNode_t **priority_queue, size_t *number_of_vertices)
{
    for(size_t i = 0; i < *number_of_vertices; ++i)
    {
        priority_queue[i]->key = distance_array[priority_queue[i]->city_number];
        heapify(priority_queue, *number_of_vertices, (unsigned int)i);
    }
}


/*
 * FUNCTION NAME: extractMin
 *
 * DESCRIPTION:
 * Function removes visited vertex (which is root in priority queue)
 * and replaces it with last element of the tree. It also decreases number of
 * vertices. Then, rebuild the heap.
 */

void extractMin(PQNode_t **priority_queue, size_t *number_of_vertices)
{
    /* Swap data from root and last element of PQ. */

    priority_queue[0]->city_number = priority_queue[*number_of_vertices - 1]->city_number;
    priority_queue[0]->key = priority_queue[*number_of_vertices - 1]->key;

    /* Remove last element of PQ from the memory. */

    removeLastPQ(priority_queue, number_of_vertices);

    /* Rebuild the heap. */

    if(*number_of_vertices != 0)
        heapifyRoot(priority_queue, *number_of_vertices, 0);
}


/*
 * FUNCTION NAME: removeLastPQ
 *
 * DESCRIPTION:
 * Function removes last element of priority queue from an array.
 */

void removeLastPQ(PQNode_t **priority_queue, size_t *number_of_vertices)
{
    free(priority_queue[*number_of_vertices - 1]);
    priority_queue[*number_of_vertices - 1] = NULL;
    --(*number_of_vertices);
}

/*
 * FUNCTION NAME: updateDistanceArray
 *
 * DESCRIPTION:
 * Function updates distance array (i.e. cost from source to 
 * other cities)
 */

void updateDistanceArray(unsigned int citys_number, double *distance_array, const Graph_t *graph, int *previous_vertex_array)
{
    AdjacencyList_t *upper;
    AdjacencyListNode_t *lower;

    for(upper = graph->head; ; upper = upper->next)
    {
        if(upper->ordinal_number == citys_number)
        {
            for(lower = upper->head; lower != NULL; lower = lower->next)
            {
                /* If cost of going to city1 from source (current cost is in distance_array)
                 * is bigger than going from source to current city to city1, then change a cost and
                 * update previous_vertex_array. */

                if(distance_array[citys_number] + lower->distance < distance_array[lower->ordinal_number])
                {
                    distance_array[lower->ordinal_number] = distance_array[citys_number] + lower->distance;
                    previous_vertex_array[lower->ordinal_number] = (int)citys_number;
                }
            }
            break;
        }
    }
}


/*
 * FUNCTION NAME: setThePath
 *
 * DESCRIPTION:
 * Function adds a city from previous_vertex_array to the head of a list.
 * If we would replace addCity function in setPath with printf, the
 * path would be shown backwards (i.e. instead of 0->1->2, it would be 2->1->0).
 * So we need to create a list and keep adding nodes with cities names to the head.
 */

void setPath(shortest_path *path, unsigned int destination_number, const int *previous_vertex_array, char **cities_names)
{
    int i = (int)destination_number;
    while(i != -1)
    {
        addCity(path, cities_names[i]);
        i = previous_vertex_array[i];
    }
}


/* FUNCTION NAME: addCity
 *
 * DESCRIPTION:
 * Function adds a node to the list that contain a city's name that is
 * in the shortest path between source and destination.
 */

void addCity(shortest_path *path, char *citys_name)
{
    shortest_path_list *node = malloc(sizeof(shortest_path_list));
    checkMemory(node);
    node->citys_name = malloc(G_CITYS_NAME_LENGTH * sizeof(char));
    checkMemory(node->citys_name);
    node->next = NULL;
    strcpy(node->citys_name, citys_name);

    if(path->head == NULL)
        path->head = node;
    else
    {
        node->next = path->head;
        path->head = node;
    }
}
