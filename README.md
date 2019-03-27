# **Finding Shortest Path**
##  **1. About**
This program finds and prints the shortest path between a pair of cities, specified by user. The list of connections between all the cities is located in *res/DataBase.txt* file. Various options, like add/remove a connection, add/remove a city and so on are implemented as well.

##  **2. Technical details**
I used pure (i.e. without any external libraries) C language (C99 standard) and checked for any potential memory leaks with Valgrind. The algorithm used to find the shortest path in the graph is Dijkstra's algorithm with minimum binary heap as a priority queue. The graph is implemented as a list of adjacency lists - from a time perspective the adjacency matrix would be a better choice, but this was my first semester of college and I wanted to learn how to use pointers.

Note: one of the underlying assumptions in this project is the undirectionality of the graph, hence, if there is a connection from A to B, then there must be a connection from B to A with the same distance. This can be (fairly) easily changed, since Dijkstra's algorithm works fine for directed graphs.

##  **3. How to run it**
Download the project

`git clone https://github.com/santaxl/ShortestPath.git`

Change directory to `FindShortestPath` folder

`cd FindShortestPath`

Create `build` folder and change directory to it

`mkdir build && cd build`

Run Cmake

`cmake ..`

Run make

`make`

Voilà, everything is ready and you are good to go

`./ShortestPath`

To change connections you can either do it from within the application or just edit *res/DataBase.txt*. 
