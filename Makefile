
all:
	g++ -std=c++11 -o bellman bellman.cpp
	g++ -std=c++11 -o dijkstra dijkstra.cpp

clean:
	rm -fr bellman dijkstra
