cmake_minimum_required (VERSION 3.6)

project(Shortest_path)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(include)

set(sources
	"src/ConstantStrings.c"
	"src/ErrorsHandling.c"
	"src/ErrorsMessages.c"
	"src/FindShortestPath.c"
	"src/GraphCreation.c"
	"src/ListCreation.c"
	"src/main.c"
	"src/ManageCities.c"
	"src/ManageConnections.c"
	"src/Menu.c"
	"src/ProgramInterface.c"
)

set(headers
	"include/Constants.h"
	"include/ErrorCodes.h"
	"include/ErrorsHandling.h"
	"include/ErrorsMessages.h"
	"include/FindShortestPath.h"
	"include/GraphCreation.h"
	"include/GraphRepresentation.h"
	"include/ListCreation.h"
	"include/ListRepresentation.h"
	"include/ManageCities.h"
	"include/ManageConnections.h"
	"include/Menu.h"
	"include/ProgramInterface.h"
)

add_executable(Shortest_path ${sources} ${headers})

