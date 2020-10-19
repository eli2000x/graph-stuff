

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	int order;
	int size;
	int *colorPtr;
	int *parentPtr;
	int *discoverPtr;
	int *finishPtr;
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
	G->colorPtr = calloc(n + 1, sizeof(int));
	G->parentPtr = calloc(n + 1, sizeof(int));
	G->discoverPtr = calloc(n + 1, sizeof(int));
	G->finishPtr = calloc(n + 1, sizeof(int));
	G->adjacencyPtr = calloc(n + 1, sizeof(List));
	for (int i = 1; i <= n; i++) {
		*(G->adjacencyPtr + i) = newList();
		*(G->parentPtr + i) = NIL;
		*(G->discoverPtr + i) = UNDEF;
		*(G->finishPtr + i) = UNDEF;
	}
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
		free(G->colorPtr);
		free(G->parentPtr);
		free(G->discoverPtr);
		free(G->finishPtr);
		free(G->adjacencyPtr);
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

// getParent()
// returns the parent of vertex u
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
	return *(G->parentPtr + u);
}

// getDiscover()
// returns the discover time of vertex u
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
	if (u < 1) {
		printf("Graph Error: calling getDist() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling getDist() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return *(G->discoverPtr + u);
}

// getFinish()
// returns the finish time of vertex u
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
	if (u < 1) {
		printf("Graph Error: calling getFinish() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling getFinish() with u > getORder(G)\n");
		exit(EXIT_FAILURE);
	}
	return *(G->finishPtr + u);
}

// Manipulation procedures ----------------------------------------------------

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
		printf("Graph Error: calling addArc() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (u > getOrder(G)) {
		printf("Graph Error: calling addArc() with u > getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1) {
		printf("Graph Error: calling addArc() with u < 1\n");
		exit(EXIT_FAILURE);
	}
	if (v > getOrder(G)) {
		printf("Graph Error: calling addArc() with u > getOrder(G)\n");
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


// DFS()
// perform depth first search algorithm on G
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
	if (length(S) != getOrder(G)) {
		printf("Graph Error: calling DFS() with length(S) != getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= G->order; i++) {
		*(G->colorPtr + i) = 0;
		*(G->parentPtr + i) = NIL;
	}
	int time = 0;
	int* timePtr = &time;
	List L = copyList(S);
	moveFront(L);
	moveFront(S);
	while(length(S) != 0) {
		deleteFront(S);
	}
	while (length(L) != 0) {
		int d = deleteFront(L);
		if (*(G->colorPtr + d) == 0) {
			Visit(G, S, d, timePtr);
		}
		moveNext(L);
	}
	freeList(&L);

}

// Visit()
// private recursive helper function
void Visit(Graph G, List S, int x, int* timePtr) {
	*(timePtr) = *(timePtr) + 1;
	*(G->discoverPtr + x) = *(timePtr);
	*(G->colorPtr + x) = 1;
	if (length(*(G->adjacencyPtr + x)) == 0) {
		*(timePtr) = *(timePtr) + 1;
		*(G->finishPtr + x) = *(timePtr);
		prepend(S, x);
		return;
	}
	moveFront(*(G->adjacencyPtr + x));
	for (int y = get(*(G->adjacencyPtr + x)); index(*(G->adjacencyPtr + x)) >= 0;
			moveNext(*(G->adjacencyPtr + x))) {
		y = get(*(G->adjacencyPtr + x));
		if (*(G->colorPtr + y) == 0) {
			*(G->parentPtr + y) = x;
			Visit(G, S, y, timePtr);
		}
	}
	*(G->colorPtr + x) = 2;
	*(timePtr) = *(timePtr) + 1;
	*(G->finishPtr + x) = *(timePtr);
	prepend(S, x);
}


// Other Functions ------------------------------------------------------------

// transpose()
// returns a reference to a new graph object representing
// the transpose of G
Graph transpose(Graph G) {
	Graph H = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		*(H->colorPtr + i) = *(G->colorPtr + i);
		*(H->discoverPtr + i) = *(G->discoverPtr + i);
		*(H->finishPtr + i) = *(G->finishPtr + i);
		*(H->parentPtr + i) = *(G->parentPtr + i);
		if (length(*(G->adjacencyPtr + i)) == 0) {
			continue;
		}
		moveFront(*(G->adjacencyPtr + i));
		for (int j = get(*(G->adjacencyPtr + i)); index(*(G->adjacencyPtr + i)) >= 0;
				moveNext(*(G->adjacencyPtr + i))) {
			j = get(*(G->adjacencyPtr + i));
			addArc(H, j, i);
		}
	}
	return (H);

}

// copyGraph
// returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G) {
	Graph H = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) {
		*(H->colorPtr + i) = *(G->colorPtr + i);
		*(H->discoverPtr + i) = *(G->discoverPtr + i);
		*(H->finishPtr + i) = *(G->finishPtr + i);
		*(H->parentPtr + i) = *(G->parentPtr + i);
		if (length(*(G->adjacencyPtr + i)) == 0) {
			continue;
		}
 		moveFront(*(G->adjacencyPtr + i));
		for (int j = get(*(G->adjacencyPtr + i)); index(*(G->adjacencyPtr + i)) >= 0;
				moveNext(*(G->adjacencyPtr + i))) {
			j = get(*(G->adjacencyPtr + i));
			addArc(H, i, j);
		}
	}
	return (H);
}


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

