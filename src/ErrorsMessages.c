/*
 * FILE NAME: ErrorsMessages.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 28.04.2016
 *
 * DESCRIPTION:
 *
 * Here is the definition of function
 * that prints message based on error code.
 */

#include <stdio.h>

#include "ErrorCodes.h"
#include "ErrorsMessages.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: printErrorDataBase
 *
 * DESCRIPTION:
 * Function prints an error message that depends on a
 * value of error_code.
 */

void printErrorDataBase(programError_t error_code)
{
    if(error_code == ALREADY_ON_THE_LIST)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "There is at least more than one connection for a pair of the same cities.\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == BAD_FORMAT)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "DataBase.txt must be filled with this format of data:\n"
                      "\"City1 City2 Distance\"\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == CANT_OPEN_FILE)
    {
        fputs("Can't open DataBase.txt file!\n"
                "Add connections manually...", stderr);
    }
    else if(error_code == CANT_UPDATE_FILE){
        fputs("Couldn't update DataBase.txt file!\n", stderr);
    }
    else if(error_code == DIFFERENT_DISTANCE)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "Distance in connection from city1 to city2 is "
                      "different than distance from city2 to city1!\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == DIRECTED_CONNECTION)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "In this program only undirected connections are allowed!\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == INCORRECT_DISTANCE)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "There is a non-positive distance between two cities.\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == INCORRECT_NAME)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "City's name can only contain basic ISO Latin characters.\n"
                      "Add connections manually...", stderr);
    }
    else if(error_code == NO_CONNECTIONS)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "There are no connections in this file!\n"
                      "Add them manually...", stderr);
    }
    else if(error_code == SAME_NAME)
    {
        fputs("DataBase.txt is wrongly filled!\n"
                      "There is a connection between cities with same name.\n"
                      "Add connections manually...", stderr);
    }
}

/*
 *  FUNCTION NAME: printErrorUsersActions
 *
 *  DESCRIPTION:
 *  Function prints a proper message that depends
 *  on the value of error_number.
 */

void printErrorUsersActions(programError_t error_code)
{
    if(error_code == CONNECTION_ALREADY_IN_GRAPH)
    {
        fputs("\nConnection is already in the graph!\n\n", stderr);
        return;
    }
    else if(error_code == CITY_ALREADY_IN_GRAPH)
    {
        fputs("\nThis city is already in the graph!\n\n", stderr);
    }
    else if(error_code == EMPTY_GRAPH)
    {
        fputs("\nGraph is empty! Add some connections first...\n\n", stderr);
    }
    else if(error_code == INCORRECT_DISTANCE)
    {
        fputs("\nIncorrect distance!\n\n", stderr);
        return;
    }
    else if(error_code == INCORRECT_NAME)
    {
        fputs("\nCity's name can only contain the ISO basic "
                      "Latin alphabet signs!\n\n", stderr);
        return;
    }
    else if(error_code == NO_SUCH_CITY)
    {
        fputs("\nError! There is no such city in the graph!\n\n", stderr);
    }
    else if(error_code == NO_SUCH_CONNECTION)
    {
        fputs("\nThere is no such connection in the graph!\n\n", stderr);
    }
    else if(error_code == NO_DIGIT)
    {
        fputs("\nYou have to type in a digit!\n\n", stderr);
        return;
    }
    else if(error_code == NO_ERROR)
        return;
    else if(error_code == SAME_NAME)
    {
        fputs("\nNames can't be the same!\n\n", stderr);
        return;
    }
    else if(error_code == TOO_MANY_SIGNS)
    {
        fputs("\nYou can only type in 1 sign!\n\n", stderr);
        return;
    }
}


/*
 * FUNCTION NAME: printErrorSystem
 *
 * DESCRIPTION:
 * Function prints an error, if something failed on a
 * system level (e.g. can't allocate a memory).
 */

void printErrorSystem(systemError_t error_code)
{
    if(error_code == CANT_ALLOCATE_MEMORY)
    {
        perror("\nError! Can't allocate a memory!\n"
                       "Closing program now...");
    }
}
