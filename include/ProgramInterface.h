/*
 * FILE NAME: ProgramInterface.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 27.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains definitions of enum types
 * that are used in showMenu() function.
 */

#ifndef SHORTEST_PATH_MENU_H
#define SHORTEST_PATH_MENU_H

#include "GraphRepresentation.h"

/* Cities amount passed from addConnection function. */

typedef enum amount_of_cities
{
    NO_CITIES,
    ONE_CITY,
    TWO_CITIES,
}amount_of_cities;


/* Manage cities enum. */

typedef enum manage_cities
{
    FIRST_CITY,
    SECOND_CITY,
    REMOVE_CITY,
    RENAME_CITY,
    NEW_CITYS_NAME,
}manage_cities;

typedef struct shortest_path_list
{
    char *citys_name;
    struct shortest_path_list *next;
}shortest_path_list;

typedef struct shortest_path
{
    shortest_path_list *head;
}shortest_path;

/**********************************************************************************************************************/

/* Declarations */

void clearBuffer(void);
void getCitysName(manage_cities, char *);
void getDistanceBetweenCities(double *);
void getUsersChoice(char *);
void showAuthor(void);
void showCityList(const Graph_t *);
void showConnections(const Graph_t *);
void showMenuOptions(unsigned int);
void showThePath(shortest_path path, const char *, const char *, unsigned int, double *);

#endif //SHORTEST_PATH_MENU_H
