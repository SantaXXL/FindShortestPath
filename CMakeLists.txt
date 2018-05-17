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

add_executable(Shortest_path ${sources})

