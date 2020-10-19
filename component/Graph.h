

#ifndef GRAPH_H_
#define GRAPH_H_
#define NIL -2
#define UNDEF -1
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

// getParent()
// returns the parent of vertex u
// parent of a vertex can be NIL
// Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// returns discover time of vertex u
// UNDEF if DFS() has not been called
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// returns finish time of vertex u
// UNDEF if DFS() has not been called
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------

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

// DFS()
// perform depth first search algorithm on G
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);

// Visit()
// private recursive helper function
void Visit(Graph G, List S, int x, int* time);

// Other Functions ------------------------------------------------------------

// transpose()
// returns a reference to a new graph object representing
// the transpose of G
Graph transpose(Graph G);

// copyGraph()
// returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// prints the adjacency List representation of G to the file pointed to by out

void printGraph(FILE* out, Graph G);


#endif
