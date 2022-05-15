# Implement Bellman-Ford and Dijkstra's algorithm for shortest path finding algorithm.  

Name: Ram Chandra Jangir

Roll Number : CS21M517

Registered Mail ID: contactjangir@gmail.com



**How to compile and run the program:**


**Step-1 :**

Clone this project using below command and you will get below list of files.

       git clone https://github.com/contactjangir/shortest-path-algorithm.git

       cd shortest-path-algorithm

       shortest-path-algorithm$ tree
	.
	├── bellman
	├── bellman.cpp
	├── dijkstra
	├── dijkstra.cpp
	├── Makefile
	├── output_bellman.txt
	├── output_dijkstra.txt
	├── README.md
	└── Solution.pdf

0 directories, 9 files



**Step-2 :**

It is already having a precompiled two binaries bellman and dijkstra which can be run directly on Ubuntu system.

OR

**How to compile**

	shortest-path-algorithm$ make
	g++ -std=c++11 -o bellman bellman.cpp
	g++ -std=c++11 -o dijkstra dijkstra.cpp




**Step-3 :**

**How to run this program for Bellman-Ford Algorithm**

	shortest-path-algorithm$ ./bellman

     Using Bellman-Ford algorithm to find single source shortest paths for the following Graph:

          (1)---->(4)
          / |    /  \
         /  |   /    \
        /   |  /      \
     (0)--->(2)        (6)
        \   |          /
         \  |         /
          \ |        /
           (3)------>(5)


     Source Vertex is : 0

     Vertex   Distance from Source
     0 ---> 0                 0
     0 ---> 1                 1
     0 ---> 2                 3
     0 ---> 3                 5
     0 ---> 4                 0
     0 ---> 5                 4
     0 ---> 6                 3




**Step-4 :**

**How to run this program for Dijkstra's Algorithm**

	shortest-path-algorithm$ ./dijkstra

     Using Dijkstra's algorithm to find single source shortest paths for the following Graph:

          (1)------>(4)------->(5)
         / | \     / | \       |  \
        /  |  \   /  |  \      |   \
       /   |   \ /   |   \     |    \
     (0)   |   (3)   |    \    |     (8)
        \  |      \  |     \   |
         \ |       \ |      \  |
          \|        \|       \ |
         (2)------->(6)------>(7)

     Source vertex is : 0

     Vertex          Distance from Source
     0 --->0                  0
     0 --->1                  4
     0 --->2                  2
     0 --->3                  7
     0 --->4                  9
     0 --->5                  16
     0 --->6                  11
     0 --->7                  13
     0 --->8                  20
