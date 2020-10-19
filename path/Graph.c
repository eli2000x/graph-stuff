

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

// FILE* for printGraph
// EXTRA LIST PRECONDITION

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	int order;
	int size;
	int label;
	int *colorPtr;
	int *distancePtr;
	int *parentPtr;
	List *adjacencyPtr;
} GraphObj;

typedef struct GraphObj* Graph;


// private Graph type

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n) {
	Graph G = calloc(1, sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->label = NIL;
	G->adjacencyPtr = calloc(n + 1, sizeof(List));

	for (int i = 1; i <= n; i++) {
		*(G->adjacencyPtr + i) = newList();
	}
	G->colorPtr = calloc(n + 1, sizeof(int));
	G->distancePtr = calloc(n + 1, sizeof(int));
	G->parentPtr = calloc(n + 1, sizeof(int));
	return (G);
}

// freeGraph()
// frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
	Graph G = *pG;
	if (pG != NULL && *pG != NULL) {
		for (int i = 1; i <= getOrder(G); i++) {
			freeList(G->adjacencyPtr + i);
		}
		free(G->adjacencyPtr);
		free(G->colorPtr);
		free(G->distancePtr);
		free(G->parentPtr);
	}
		free(*pG);
		*pG = NULL;

}

// Access functions -----------------------------------------------------------

// getOrder()
// returns the order
int getOrder(Graph G) {
	return G->order;
}

// getSize()
// returns the size
int getSize(Graph G) {
	return G->size;
}

// getSource()
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G) {
	return G->label;
}

// getParent()
// returns the parents of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
	if (u < 1) {
		printf("Graph Error: calling getParent() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling getParent() with u > getOrder\n");
		exit(EXIT_FAILURE);
	}
	if (G->label < 0) {
		return NIL;
	}
	return *(G->parentPtr + u);
}

// getDist()
// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
	if (u < 1) {
		printf("Graph Error: calling getDist() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling getDist() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (G->label < 0) {
		return INF;
	}
	if (G->label == u) {
		return 0;
	}
	return *(G->distancePtr + u);
}

// getPath()
// appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists
// Pre: getSource(G) != NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
	if (L == NULL) {
		printf("Graph Error: calling getPath() with null List reference\n");
		exit(EXIT_FAILURE);
	}
	int v = u;
	if (getSource(G) == NIL) {
		printf("Graph Error: calling getPath() with getSource() == NIL\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1) {
		printf("Graph Error: calling getPath() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling getPath() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (G->label == u) {
		append(L, u);
		return;
	}
	if (*(G->distancePtr + v) == INF) {
		append(L, NIL);

		return;
	}
	int w = u;
	prepend(L, w);
	while(G->label != w) {
		prepend(L, *(G->parentPtr + w));
		w = *(G->parentPtr + w);
	}


}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
	for (int i = 1; i <= G->order; i++) {
		clear(*(G->adjacencyPtr + i));
	}
	G->size = 0;
}

// addEdge()
// inserts a new edge joining u to v
// u is added to the adjacency List of v, and v to the adjacency List of u
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
	if (u < 1) {
		printf("Graph Error: calling addEdge() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling addEdge() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1) {
		printf("Graph Error: calling addEdge() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (v > getOrder(G)) {
		printf("Graph Error: calling addEdge() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	insert(*(G->adjacencyPtr + u), v);
	insert(*(G->adjacencyPtr + v), u);

	G->size += 1;

}

// addArc()
// inserts a new directed edge from u to v, v is added to the adjacency List of u
// u is not added to the adjacency List of v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
	if (u < 1) {
		printf("Graph Error: calling addEdge() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling addEdge() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1) {
		printf("Graph Error: calling addEdge() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (v > getOrder(G)) {
		printf("Graph Error: calling addEdge() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	insert(*(G->adjacencyPtr + u), v);
	G->size += 1;
}

// insert()
// insert value into List in increasing order
void insert(List L, int val) {
	if (length(L) == 0) {
		append(L, val);
		return;
	}
	moveFront(L);
	while (index(L) >= 0) {
		if (val <= get(L)) {
			insertBefore(L, val);
			return;
		} else {
			if (get(L) == back(L)) {
				append(L, val);
				return;
			}
			moveNext(L);
		}
	}

}

// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly
void BFS(Graph G, int s) {
	for (int i = 1; i <= G->order; i++) {
		if (i == s) {
			*(G->colorPtr + i) = 1;
			*(G->distancePtr + i) = 0;
			*(G->parentPtr + i) = NIL;
		} else {
			*(G->colorPtr + i) = 0;
			*(G->distancePtr + i) = INF;
			*(G->parentPtr + i) = NIL;
		}
	}
	if (length(*(G->adjacencyPtr + s)) == 0) {
		*(G->parentPtr + s) = 0;
		G->label = s;
		return;
	}
	List L = newList();
	append(L, s);
	while (length(L) != 0) {
		int u = deleteFront(L);
		moveFront(*(G->adjacencyPtr + u));
		printf("%d\n", s);
		for (int v = get(*(G->adjacencyPtr + u)); index(*(G->adjacencyPtr + u)) >= 0;
				moveNext(*(G->adjacencyPtr + u))) {
				v = get(*(G->adjacencyPtr + u));
				if (*(G->colorPtr + v) == 0) {
					*(G->colorPtr + v) = 1;
					*(G->distancePtr + v) = *(G->distancePtr + u) + 1;
					*(G->parentPtr + v) = u;
					append(L, v);
				}

		}
		*(G->colorPtr + u) = 2;
	}
	freeList(&L);

	G->label = s;
}

// Other Functions ------------------------------------------------------------

// printGraph()
// prints the adjacency List representation of G to the file pointed to by out

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->order; i++) {
		moveFront(*(G->adjacencyPtr + i));
		if (i == 1) {
			fprintf(out, "%d: ", i);
		} else {
			fprintf(out, "\n%d: ", i);
		}
		while(index(*(G->adjacencyPtr + i)) >= 0) {
			fprintf(out, "%d ", get(*(G->adjacencyPtr + i)));
			moveNext(*(G->adjacencyPtr + i));
		}
	}
}

