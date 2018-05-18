/*
 * FILE NAME: Menu.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 20.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of showMenu() function.
 * Firstly, this function calls graphCreation() to create a graph.
 * Then it shows program menu and runs option selected by the user.
 * Note: graph stands for a list in which every node contains a head to
 * another list (adjacency list).
 */

#include <stdlib.h>

#include "Constants.h"
#include "ErrorCodes.h"
#include "GraphRepresentation.h"
#include "Menu.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: showMenu
 *
 * DESCRIPTION:
 * This function calls graphCreation() function, that creates graph.
 * Then it shows menu and runs an option selected by the user.
 */

void showMenu(void)
{
    char choice[MAX_INPUT_MAIN_MENU]; /* Gets user's choice; 3 chars: choice, '\n', '\0' */
    unsigned int counter = 0; /* Counts how many times user typed in a wrong choice */
    int number; /* Number == atoi(&choice[0]) */
    programError_t what_error; /* Error handling */

    /* Create and fill graph with proper data. */

    Graph_t* graph = graphCreation();

    /* Firstly, show menu. Then read user's choice.
     * User's choice is wrong if:
     * - he didn't type only 1 sign (choice[1] != '\n');
     * - typed sign is not a number (!isdigit(choice[0]);
     * - typed number is different than available in menu;
     * Every 3 wrong answers, show menu once again. Between
     * showing the entire menu, just print a short message on the screen. */

    while (1) {
        counter = 0;
        do {
            showMenuOptions(counter);
            getUsersChoice(choice);
            what_error = checkUsersChoiceMainMenu(choice, &number);
            ++counter;
        } while (what_error != NO_ERROR);

        switch (number) {
        case FIND_SHORTEST_PATH: {
            findShortestPathMenu(graph);
            break;
        }
        case ADD_CONNECTION: {
            addConnection(graph);
            break;
        }
        case REMOVE_CONNECTION: {
            removeConnectionMenu(graph);
            break;
        }
        case REMOVE_CITY: {
            removeCityMenu(graph);
            break;
        }
        case RENAME_CITY: {
            renameCityMenu(graph);
            break;
        }
        case CHANGE_DISTANCE: {
            changeDistanceMenu(graph);
            break;
        }
        case SHOW_CITIES_LIST: {
            showCityList(graph);
            break;
        }
        case SHOW_CONNECTIONS: {
            showConnections(graph);
            break;
        }
        case SHOW_AUTHOR: {
            showAuthor();
            break;
        }
        case EXIT: {
            updateDataBaseFile(graph);
            removeGraph(graph);
            exit(EXIT_SUCCESS);
        }
        default: {
            break;
        }
        }
    }
}
