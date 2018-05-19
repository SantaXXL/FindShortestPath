/*
 * FILE NAME: ErrorCodes.h
 *
 * AUTHOR: Dominik Mankowski
 *
 * DATE: 28.04.2016
 *
 * DESCRIPTION:
 *
 * This file contains definition of enums
 * program_error and system_error.
 */

#ifndef SHORTEST_PATH_ERROR_CODES_H
#define SHORTEST_PATH_ERROR_CODES_H

typedef enum programError {
    ALREADY_ON_THE_LIST,
    BAD_FORMAT,
    CANT_OPEN_FILE,
    CANT_UPDATE_FILE,
    CITY_ALREADY_IN_GRAPH,
    CONNECTION_ALREADY_IN_GRAPH,
    DIFFERENT_DISTANCE,
    DIRECTED_CONNECTION,
    EMPTY_GRAPH,
    IDENTICAL_NAMES,
    INCORRECT_DISTANCE,
    INCORRECT_NAME,
    NO_SUCH_CITY,
    NO_SUCH_CONNECTION,
    NO_CONNECTIONS,
    NO_DIGIT,
    NO_ERROR,
    TOO_MANY_SIGNS,
} programError_t;

typedef enum systemError {
    CANT_ALLOCATE_MEMORY,
} systemError_t;

#endif //SHORTEST_PATH_ERRORSCODES_H
