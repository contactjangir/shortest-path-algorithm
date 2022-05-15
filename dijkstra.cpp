/*
* Dijkstra's shortest path algorithm
* for adjacency list representation of graph
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// node in adjacency list
struct adj_list_node
{
  int dest;
  int weight;
  struct adj_list_node *next;
};

// an adjacency list
struct adj_list
{
  struct adj_list_node *head;
};

// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph
{
  int V;
  struct adj_list *array;
};

// a new adjacency list node
struct adj_list_node *
newAdjListNode (int dest, int weight)
{
  struct adj_list_node *newNode =
    (struct adj_list_node *) malloc (sizeof (struct adj_list_node));
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

// function to create a graph of V vertices
struct Graph *
create_graph (int V)
{
  struct Graph *graph = (struct Graph *) malloc (sizeof (struct Graph));
  graph->V = V;

  graph->array = (struct adj_list *) malloc (V * sizeof (struct adj_list));

  for (int i = 0; i < V; ++i)
    graph->array[i].head = NULL;

  return graph;
}

void
add_edge (struct Graph *graph, int src, int dest, int weight)
{
  struct adj_list_node *newNode = newAdjListNode (dest, weight);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  newNode = newAdjListNode (src, weight);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}

struct min_heap_node
{
  int v;
  int dist;
};

struct min_heap
{

  // Number of heap nodes present currently
  int size;

  // Capacity of min heap
  int capacity;

  int *pos;
  struct min_heap_node **array;
};

struct min_heap_node *
allocate_min_heap_node (int v, int dist)
{
  struct min_heap_node *minHeapNode =
    (struct min_heap_node *) malloc (sizeof (struct min_heap_node));
  minHeapNode->v = v;
  minHeapNode->dist = dist;
  return minHeapNode;
}

// function to create a Min Heap
struct min_heap *
create_min_heap (int capacity)
{
  struct min_heap *minHeap =
    (struct min_heap *) malloc (sizeof (struct min_heap));
  minHeap->pos = (int *) malloc (capacity * sizeof (int));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array =
    (struct min_heap_node **)
    malloc (capacity * sizeof (struct min_heap_node *));
  return minHeap;
}

// function to swap two nodes of min heap.
void
swapMinHeapNode (struct min_heap_node **a, struct min_heap_node **b)
{
  struct min_heap_node *t = *a;
  *a = *b;
  *b = t;
}

void
min_heapify (struct min_heap *minHeap, int idx)
{
  int smallest, left, right;
  smallest = idx;
  left = 2 * idx + 1;
  right = 2 * idx + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->dist < minHeap->array[smallest]->dist)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->dist < minHeap->array[smallest]->dist)
    smallest = right;

  if (smallest != idx)
    {
      min_heap_node *smallestNode = minHeap->array[smallest];
      min_heap_node *idxNode = minHeap->array[idx];

      minHeap->pos[smallestNode->v] = idx;
      minHeap->pos[idxNode->v] = smallest;

      swapMinHeapNode (&minHeap->array[smallest], &minHeap->array[idx]);

      min_heapify (minHeap, smallest);
    }
}

int
is_heap_empty (struct min_heap *minHeap)
{
  return minHeap->size == 0;
}

// function to extract minimum node from heap
struct min_heap_node *
extractMin (struct min_heap *minHeap)
{
  if (is_heap_empty (minHeap))
    return NULL;

  // store the root node
  struct min_heap_node *root = minHeap->array[0];

  // replace root node with last node
  struct min_heap_node *lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;

  // update position of last node
  minHeap->pos[root->v] = minHeap->size - 1;
  minHeap->pos[lastNode->v] = 0;

  // reduce heap size and heapify root
  --minHeap->size;
  min_heapify (minHeap, 0);

  return root;
}

// function to decreasy dist value of a given vertex v.
void
decrease_key (struct min_heap *minHeap, int v, int dist)
{
  int i = minHeap->pos[v];

  minHeap->array[i]->dist = dist;

  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
      minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
      minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
      swapMinHeapNode (&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

      i = (i - 1) / 2;
    }
}

bool
is_inside_min_heap (struct min_heap *minHeap, int v)
{
  if (minHeap->pos[v] < minHeap->size)
    return true;
  return false;
}

void
print_dist (int dist[], int n, int src)
{
  printf ("Vertex \t\tDistance from Source\n");
  for (int i = 0; i < n; ++i)
    printf ("%d --->%d \t\t %d\n", src, i, dist[i]);
}

void
dijkstra (struct Graph *graph, int src)
{

  // Get the number of vertices in graph
  int V = graph->V;

  // dist values used to pick
  // minimum weight edge in cut
  int dist[V];

  // minHeap represents set E
  struct min_heap *minHeap = create_min_heap (V);

  printf ("\nSource vertex is : %d\n\n", src);
  // Initialize min heap with all
  // vertices. dist value of all vertices
  for (int v = 0; v < V; ++v)
    {
      dist[v] = INT_MAX;
      minHeap->array[v] = allocate_min_heap_node (v, dist[v]);
      minHeap->pos[v] = v;
    }

  // Make dist value of src vertex
  // as 0 so that it is extracted first
  minHeap->array[src] = allocate_min_heap_node (src, dist[src]);
  minHeap->pos[src] = src;
  dist[src] = 0;
  decrease_key (minHeap, src, dist[src]);

  // Initially size of min heap is equal to V
  minHeap->size = V;

  // In the followin loop,
  // min heap contains all nodes
  // whose shortest distance
  // is not yet finalized.
  while (!is_heap_empty (minHeap))
    {
      // Extract the vertex with
      // minimum distance value
      struct min_heap_node *minHeapNode = extractMin (minHeap);

      // Store the extracted vertex number
      int u = minHeapNode->v;

      // Traverse through all adjacent
      // vertices of u (the extracted
      // vertex) and update
      // their distance values
      struct adj_list_node *pCrawl = graph->array[u].head;
      while (pCrawl != NULL)
	{
	  int v = pCrawl->dest;

	  // If shortest distance to v is
	  // not finalized yet, and distance to v
	  // through u is less than its
	  // previously calculated distance
	  if (is_inside_min_heap (minHeap, v) &&
	      dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
	    {
	      dist[v] = dist[u] + pCrawl->weight;

	      // update distance
	      // value in min heap also
	      decrease_key (minHeap, v, dist[v]);
	    }
	  pCrawl = pCrawl->next;
	}
    }

  // print the calculated shortest distances
  print_dist (dist, V, src);
}


int
main ()
{
  printf
    ("\nUsing Dijkstra's algorithm to find single source shortest paths for the following Graph:\n");
  printf("           7          8  \n");
  printf ("     (1)------>(4)------->(5) \n");
  printf ("    / | \\     / | \\       |  \\  \n");
  printf ("  5/  | 3\\  2/  |  \\      |   \\4 \n");
  printf ("  /  2|   \\ /   |5  \\7    |3   \\ \n");
  printf ("(0)   |   (3)   |    \\    |     (8) \n");
  printf ("   \\  |      \\  |     \\   |  \n");
  printf ("   2\\ |      6\\ |      \\  |  \n");
  printf ("     \\|   9    \\|  2    \\ |  \n");
  printf ("    (2)------->(6)------>(7)       \n");
  // create the graph given in above fugure
  int V = 9;
  struct Graph *graph = create_graph (V);
  add_edge (graph, 0, 1, 5);
  add_edge (graph, 0, 2, 2);
  add_edge (graph, 1, 3, 3);
  add_edge (graph, 1, 4, 7);
  add_edge (graph, 2, 1, 2);
  add_edge (graph, 2, 6, 9);
  add_edge (graph, 3, 4, 2);
  add_edge (graph, 3, 6, 6);
  add_edge (graph, 4, 5, 8);
  add_edge (graph, 4, 6, 5);
  add_edge (graph, 4, 7, 7);
  add_edge (graph, 5, 8, 4);
  add_edge (graph, 6, 7, 2);
  add_edge (graph, 7, 5, 3);

  dijkstra (graph, 0);

  return 0;
}
