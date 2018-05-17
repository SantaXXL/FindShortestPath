/*
 * FILE NAME: Menu.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 20.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains enum definition -
 * main menu options and declarations.
 */

#ifndef SHORTEST_PATH_MENU_H
#define SHORTEST_PATH_MENU_H

/* Declarations */

void addConnection(Graph_t *);
void changeDistanceMenu(Graph_t *);
programError_t checkUsersChoiceMainMenu(const char *, int *);
void findShortestPathMenu(Graph_t *);
void getUsersChoice(char *);
Graph_t *graphCreation(void);
void removeCityMenu(Graph_t *);
void removeConnectionMenu(Graph_t *);
void removeGraph(Graph_t *);
void renameCityMenu(Graph_t *);
void showAuthor(void);
void showConnections(const Graph_t *);
void showCityList(const Graph_t *);
void showMenu(void);
void showMenuOptions(unsigned int);
void updateDataBaseFile(const Graph_t *);

/**********************************************************************************************************************/

/* Menu options */

typedef enum menu_choice
{
    EXIT,
    FIND_SHORTEST_PATH,
    ADD_CONNECTION,
    REMOVE_CONNECTION,
    REMOVE_CITY,
    RENAME_CITY,
    CHANGE_DISTANCE,
    SHOW_CITIES_LIST,
    SHOW_CONNECTIONS,
    SHOW_AUTHOR,
}menu_choice;

#endif //SHORTEST_PATH_MENU_H
