/*
 * FILE NAME: ErrorsMessages.c
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 28.04.2016
 *
 * DESCRIPTION:
 *
 * Here are the definitions of functions
 * that print message based upon the error code.
 */

#include <stdio.h>

#include "ErrorCodes.h"
#include "ErrorsMessages.h"

/**********************************************************************************************************************/

/* Definitions */

/*
 * FUNCTION NAME: printDataBaseError
 *
 * DESCRIPTION:
 * Function prints an error message that depends upon a
 * value of error_code.
 */

void printDataBaseError(programError_t error_code)
{
    if (error_code == ALREADY_ON_THE_LIST) {
        fputs("DataBase.txt is incorrect!\n"
              "There is at least more than one connection for a pair of the same cities.\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == BAD_FORMAT) {
        fputs("DataBase.txt is incorrect!\n"
              "DataBase.txt must be filled with such format of data:\n"
              "\"City1 City2 Distance\"\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == CANT_OPEN_FILE) {
        fputs("Can't open DataBase.txt file!\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == CANT_UPDATE_FILE) {
        fputs("Couldn't update DataBase.txt file!\n", stderr);
    } else if (error_code == DIFFERENT_DISTANCE) {
        fputs("DataBase.txt is incorrect!\n"
              "Distance in connection from city1 to city2 is "
              "different than distance from city2 to city1!\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == INCORRECT_DISTANCE) {
        fputs("DataBase.txt is incorrect!\n"
              "There is a non-positive distance between two cities.\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == INCORRECT_NAME) {
        fputs("DataBase.txt is incorrect!\n"
              "City's name can only contain basic ISO Latin characters.\n"
              "Add connections manually...",
            stderr);
    } else if (error_code == NO_CONNECTIONS) {
        fputs("DataBase.txt is incorrect!\n"
              "There are no connections in this file!\n"
              "Add them manually...",
            stderr);
    } else if (error_code == IDENTICAL_NAMES) {
        fputs("DataBase.txt is incorrect!\n"
              "There is a connection between cities with same names.\n"
              "Add connections manually...",
            stderr);
    }
}

/*
 *  FUNCTION NAME: printErrorUsersActions
 *
 *  DESCRIPTION:
 *  Function prints a proper message that depends
 *  upon the value of error_number.
 */

void printErrorUsersActions(programError_t error_code)
{
    if (error_code == CONNECTION_ALREADY_IN_GRAPH) {
        fputs("\nConnection is already in the graph!\n\n", stderr);
        return;
    } else if (error_code == CITY_ALREADY_IN_GRAPH) {
        fputs("\nThis city is already in the graph!\n\n", stderr);
    } else if (error_code == EMPTY_GRAPH) {
        fputs("\nGraph is empty! Add some connections first...\n\n", stderr);
    } else if (error_code == INCORRECT_DISTANCE) {
        fputs("\nIncorrect distance!\n\n", stderr);
        return;
    } else if (error_code == INCORRECT_NAME) {
        fputs("\nCity's name can only contain the ISO basic "
              "Latin alphabet signs!\n\n",
            stderr);
        return;
    } else if (error_code == NO_SUCH_CITY) {
        fputs("\nError! There is no such city in the graph!\n\n", stderr);
    } else if (error_code == NO_SUCH_CONNECTION) {
        fputs("\nThere is no such connection in the graph!\n\n", stderr);
    } else if (error_code == NO_DIGIT) {
        fputs("\nYou have to type in a digit!\n\n", stderr);
        return;
    } else if (error_code == NO_ERROR)
        return;
    else if (error_code == IDENTICAL_NAMES) {
        fputs("\nNames can't be identical!\n\n", stderr);
        return;
    } else if (error_code == TOO_MANY_SIGNS) {
        fputs("\nYou can only type in 1 sign!\n\n", stderr);
        return;
    }
}

/*
 * FUNCTION NAME: printSystemError
 *
 * DESCRIPTION:
 * Function prints an error, if something failed on a
 * system level (e.g. can't allocate a memory).
 */

void printSystemError(systemError_t error_code)
{
    if (error_code == CANT_ALLOCATE_MEMORY) {
        perror("\nError! Can't allocate memory!\n"
               "Closing program now...");
    }
}
