cmake_minimum_required (VERSION 3.6)

project(ShortestPath)

set(CMAKE_C_FLAGS "-std=c99")

include_directories(include)

set(sources
	"src/ConstantStrings.c"
	"src/ErrorsHandling.c"
	"src/ErrorsMessages.c"
	"src/FindShortestPath.c"
	"src/GraphCreation.c"
	"src/ListCreation.c"
	"src/Main.c"
	"src/ManageCities.c"
	"src/ManageConnections.c"
	"src/Menu.c"
	"src/ProgramInterface.c"
)

add_executable(ShortestPath ${sources})

