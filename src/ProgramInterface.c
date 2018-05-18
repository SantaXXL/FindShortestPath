/*
 * FILE NAME: ProgramInterface.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 26.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of functions, that
 * create menu interface.
 */

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "GraphRepresentation.h"
#include "ProgramInterface.h"

/**********************************************************************************************************************/

/* Global variables */

/* Sets value of global constants which are declared in Constants.h */

const unsigned short int G_CITYS_NAME_LENGTH = 30;
const unsigned short int MAX_INPUT_MAIN_MENU = 3; /* MAX_INPUT_MAIN_MENU = 3, 'user's choice', '\n', '\0' */

/* Following strings are defined in ConstantStrings.c file */

extern const char MENU[];
extern const char AUTHOR[];

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: getCitysName
 *
 * DESCRIPTION:
 * Function gets a name of the city and
 * calls a function that clears an input buffer.
 */

void getCitysName(manage_cities option, char* citys_name)
{
    if (option == FIRST_CITY) {
        printf("Type in first city: ");
    } else if (option == SECOND_CITY) {
        printf("Type in second city: ");
    } else if (option == REMOVE_CITY) {
        printf("What city do you want to remove: ");
    } else if (option == RENAME_CITY) {
        printf("What city do you want to rename: ");
    } else if (option == NEW_CITYS_NAME) {
        printf("Type in new city's name: ");
    }
    fgets(citys_name, G_CITYS_NAME_LENGTH, stdin);

    /* Because fgets is retarded and doesn't skip newline character,
     * remove it manually. */

    if (citys_name[strlen(citys_name) - 1] == '\n') {
        citys_name[strlen(citys_name) - 1] = '\0';
    }
}

/*
 * FUNCTION NAME: getDistanceBetweenCities
 *
 * DESCRIPTION:
 * Function gets a distance between two cities.
 */

void getDistanceBetweenCities(double* distance)
{
    printf("What's the distance between those cities [km]: ");
    while (scanf("%lf", distance) != 1) {
        clearBuffer();
        fputs("\nType in a number!\n\n", stderr);
        printf("What's the distance between those cities [km]: ");
    }
}

/*
 * FUNCTION NAME: getUsersChoice
 *
 * DESCRIPTION:
 * Function gets first 3 signs typed in by user.
 */

void getUsersChoice(char* choice)
{
    fgets(choice, MAX_INPUT_MAIN_MENU, stdin);
}

/*
 * FUNCTION NAME: showCityList
 *
 * DESCRIPTION:
 * Function prints on the screen every city that is on the all_cities
 * list.
 */

void showCityList(const Graph_t* graph)
{
    int counter = 0;
    if (graph->head == NULL) {
        puts("\nThere are no cities in the database!");
        return;
    } else {
        AdjacencyList_t* temp;
        puts("\nCities in the database:\n");
        for (temp = graph->head; temp; temp = temp->next) {
            puts(temp->from);
            ++counter;
        }
        printf("------------------------------------------\n");
        printf("Totally:                         %d cities\n", counter);
    }
}

/*
 * FUNCTION NAME: showConnections
 *
 * DESCRIPTION:
 * Function shows every connection between two cities that
 * exists in the graph.
 */

void showConnections(const Graph_t* graph)
{
    AdjacencyList_t* upper;
    AdjacencyListNode_t* lower;
    if (graph->head == NULL) {
        puts("\nThere are no cities in the database!");
        return;
    }
    int counter = 0;
    printf("\nConnections in the database:\n\n");
    for (upper = graph->head; upper != NULL; upper = upper->next) {
        printf("%s: ", upper->from);
        for (lower = upper->head; lower != NULL; lower = lower->next) {
            printf("%s ", lower->to);
            ++counter;
        }
        printf("\n");
    }
    printf("------------------------------------------\n");
    printf("Totally:                    %d connections\n", counter / 2);
}

/*
 * FUNCTION NAME: showMenuOptions
 *
 * DESCRIPTION:
 * This function prints menu on the screen.
 * If user typed in a wrong choice, it prints
 * a short message to type in the correct choice.
 * Every 3 wrong choices, it prints whole menu.
 */

void showMenuOptions(unsigned int counter)
{
    if ((counter % 3) == 0) {
        printf("\n%s", MENU);
    } else {
        printf("Type in the correct choice: ");
    }
}

/*
 * FUNCTION NAME: showAuthor
 *
 * DESCRIPTION:
 * Function prints author info on the screen.
 */

void showAuthor(void)
{
    puts(AUTHOR);
}

/*
 * FUNCTION NAME: showThePath
 *
 * DESCRIPTION:
 * Shows the shortest path in the graph from
 * destination to source.
 */

void showThePath(shortest_path path, const char* destination, const char* source, unsigned int destination_number, double* distance_array)
{
    /* If there is no path between source and destination. */

    if (distance_array[destination_number] == LLONG_MAX) {
        printf("\nCities %s and %s are not connected!\n\n", source, destination);
        printf("Press enter to continue...");
        if (getchar() != '\n') {
            clearBuffer();
        }
        return;
    }

    /* If there is a path between source and destination. */

    shortest_path_list* temp;
    printf("\nThe shortest path from %s to %s is:\n\n", source, destination);
    for (temp = path.head; temp != NULL; temp = temp->next) {
        if (temp->next != NULL) {
            printf("%s -> ", temp->citys_name);
        } else {
            printf("%s", temp->citys_name);
        }
    }
    printf("\n\nDistance from %s to %s: %.2lfkm.\n\n", source, destination, distance_array[destination_number]);
    printf("Press enter to continue...");
    if (getchar() != '\n') {
        clearBuffer();
    }
}
