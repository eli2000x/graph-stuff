
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {

	// check for command line arguments != 3
	if (argc != 3) {
		printf("Command line arguments != 3\n");
		exit(EXIT_FAILURE);
	}

	// variables for in/out file
	char input[1000];
	FILE* in;
	FILE* out;

	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	out = fopen(argv[2], "w");
	if (out == NULL) {
		printf("Unable to write to the file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	// get order and create graph and list
	int order;
	int* orderPtr = &order;
	fscanf(in, "%d", orderPtr);
	Graph G = newGraph(order);
	List S = newList();

	// variables for getting vertices
	int vertex = 0;
	int vertex1 = 1;
	int* vertexptr = &vertex;
	int* vertexptr1 = &vertex1;

	// prepend vertices to list
	for (int i = order; i > 0; i--) {
		prepend(S, i);
	}

	// addArcs
	while(fgets(input, 1000, in) != NULL) {
		sscanf(input, "%d %d", vertexptr, vertexptr1);
		if (*vertexptr == 0) {
			continue;
		}
		if (*vertexptr == 0 && *vertexptr1 == 0) {
			break;
		}
		addArc(G, *vertexptr, *vertexptr1);
	}

	// print adjacency list representation
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n\n");

	// call DFS() on G and GT
	DFS(G, S);
	Graph H = transpose(G);
	DFS(H, S);

	// count and print number of connected components
	int numCC = 0;
	moveFront(S);
	while(index(S) >= 0) {
		int n = get(S);
		if (getParent(H, n) == NIL) {
			numCC++;
		}
		moveNext(S);
	}
	fprintf(out, "G contains %d strongly connected components:", numCC);

	// add connected components to stack to print in order
	List P = newList();
	moveFront(S);
	moveFront(P);
	while(index(S) >= 0) {
		int x = get(S);
		if (getParent(H, x) == NIL) {
			prepend(P, x);
			moveFront(P);
		}
		int y;
		if (get(S) == back(S)) {
			break;
		} else {
			moveNext(S);
			y = get(S);
			movePrev(S);
		}
		if (getParent(H, y) == NIL) {
			prepend(P, 0);
			moveNext(S);
				continue;
		}
		insertAfter(P, y);
		moveNext(P);
		moveNext(S);
	}
	prepend(P, 0);

	moveFront(P);
	int comp = 1;
	while (index(P) >= 0) {
		int x = get(P);
		if (x == 0) {
			fprintf(out, "\nComponent %d: ", comp);
			comp++;
		} else {
			fprintf(out, "%d ", x);
		}
			moveNext(P);
	}
	fprintf(out, "\n");

	// free Graphs and List
	freeGraph(&G);
	freeGraph(&H);
	freeList(&S);
	freeList(&P);

	// close files
	fclose(in);
	fclose(out);


}
