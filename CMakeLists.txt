cmake_minimum_required (VERSION 3.6)

project(ShortestPath)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wno-long-long -Wuninitialized -Wconversion -Wstrict-prototypes -Werror -pedantic")

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

add_executable(${PROJECT_NAME} ${sources})

