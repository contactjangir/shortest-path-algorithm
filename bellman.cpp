// Implement Bellman-Ford's single source shortest path algorithm.

#include <bits/stdc++.h>

// a weighted edge in graph
struct edge
{
  int src, dest, weight;
};

struct Graph
{
  int V, E;
  struct edge *edge;
};

struct Graph *
create_graph (int V, int E)
{
  struct Graph *graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new edge[E];
  return graph;
}

void
print_dist (int dist[], int n, int src)
{
  printf ("Vertex\t Distance from Source\n");
  for (int i = 0; i < n; ++i)
    printf ("%d ---> %d \t\t %d\n", src, i, dist[i]);
}

void
bellman_ford (struct Graph *graph, int src)
{
  int V = graph->V;
  int E = graph->E;
  int dist[V];

  printf ("\n\nSource Vertex is : %d\n\n", src);
  // Step 1: Initialize distances from src to all other vertices
  // as INFINITE
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX;
  dist[src] = 0;

  // Step 2: Relax all edges |V| - 1 times. A simple shortest
  // path from src to any other vertex can have at-most |V| - 1
  // edges
  for (int i = 1; i <= V - 1; i++)
    {
      for (int j = 0; j < E; j++)
	{
	  int u = graph->edge[j].src;
	  int v = graph->edge[j].dest;
	  int weight = graph->edge[j].weight;
	  if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
	    dist[v] = dist[u] + weight;
	}
    }

  // Step 3: check for negative-weight cycles. The above step
  // guarantees shortest distances if graph doesn't contain
  // negative weight cycle. If we get a shorter path, then there
  // is a cycle.
  for (int i = 0; i < E; i++)
    {
      int u = graph->edge[i].src;
      int v = graph->edge[i].dest;
      int weight = graph->edge[i].weight;
      if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
	{
	  printf ("Graph contains negative weight cycle");
	  return;		// If negative cycle is detected, simply return
	}
    }

  print_dist (dist, V, src);

  return;
}

int
main ()
{

  printf
    ("\nUsing Bellman-Ford algorithm to find single source shortest paths for the following Graph:\n");

  printf ("         -1    \n");
  printf ("     (1)---->(4)\n");
  printf ("     / |    /  \\\n");
  printf ("   6/  |-2 /1  3\\\n");
  printf ("   / 5 |  /      \\\n");
  printf ("(0)--->(2)        (6)\n");
  printf ("   \\   |          /\n");
  printf ("   5\\  |-2      3/\n");
  printf ("     \\ |   -1   / \n");
  printf ("      (3)------>(5)\n");

  /* Let us create the graph given in above example */
  /* Number of vertices in graph */
  int V = 7;
  /* Number of edges in graph */
  int E = 10;

  struct Graph *graph = create_graph (V, E);

  // add edge 0-1
  graph->edge[0].src = 0;
  graph->edge[0].dest = 1;
  graph->edge[0].weight = 6;

  // add edge 0-2
  graph->edge[1].src = 0;
  graph->edge[1].dest = 2;
  graph->edge[1].weight = 5;

  // add edge 0-3
  graph->edge[2].src = 0;
  graph->edge[2].dest = 3;
  graph->edge[2].weight = 5;

  // add edge 1-4
  graph->edge[3].src = 1;
  graph->edge[3].dest = 4;
  graph->edge[3].weight = -1;

  // add edge 2-1
  graph->edge[4].src = 2;
  graph->edge[4].dest = 1;
  graph->edge[4].weight = -2;

  // add edge 2-4
  graph->edge[5].src = 2;
  graph->edge[5].dest = 4;
  graph->edge[5].weight = 1;

  // add edge 3-2
  graph->edge[6].src = 3;
  graph->edge[6].dest = 2;
  graph->edge[6].weight = -2;

  // add edge 3-5
  graph->edge[7].src = 3;
  graph->edge[7].dest = 5;
  graph->edge[7].weight = -1;

  // add edge 4-6
  graph->edge[8].src = 4;
  graph->edge[8].dest = 6;
  graph->edge[8].weight = 3;

  // add edge 5-6
  graph->edge[9].src = 5;
  graph->edge[9].dest = 6;
  graph->edge[9].weight = 3;

  bellman_ford (graph, 0);

  return 0;
}
