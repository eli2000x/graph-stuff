

#ifndef GRAPH_H_
#define GRAPH_H_
#define INF -1
#define NIL -2
#include "List.h"
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n);

// freeGraph()
// frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------

// getOrder()
// returns the order
int getOrder(Graph G);

// getSize()
// returns the size
int getSize(Graph G);

// getSource()
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G);

// getParent()
// returns the parents of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// appends to the List L where the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// Pre: getSource(G) != NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v
// u is added to the adjacency List of v, and v to the adjacency List of u
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v, v is added to the adjacency List of u
// u is not added to the adjacency List of v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v);

// insert()
// insert value into List in increasing order
void insert(List L, int val);

// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly
void BFS(Graph G, int s);

// Other Functions ------------------------------------------------------------

// printGraph()
// prints the adjacency List representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);


#endif
