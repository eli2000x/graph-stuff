

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
	/*
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	printf("Order of graph: %d\n", getOrder(G));
	printf("Size of graph: %d\n", getSize(G));
	printf("Source vertex: %d\n", getSource(G));
	printGraph(G);

	BFS(G, 1);
	printf("Source vertex: %d\n", getSource(G));
	for (int i = 1; i <= 6; i++) {
		printf("Distance from %d to %d is %d\n", 1, i, getDist(G, i));
	}
	for (int i = 1; i <= 6; i++) {
		printf("Parent of %d is %d\n", i, getParent(G, i));
	}

	List L = newList();
	for (int i = 1; i <= 6; i++) {
		getPath(L, G, i);
		printf("Length of list is: %d\n", length(L));
	}

	freeList(&L);
	*/

	int order = 12;
	int source = 1;
	Graph G = newGraph(order);
	addEdge(G, 1, 2);
	addEdge(G, 2, 1);
	addEdge(G, 2, 3);
	addEdge(G, 2, 8);
	addEdge(G, 3, 2);
	addEdge(G, 3, 4);
	addEdge(G, 3, 8);
	addEdge(G, 4, 3);
	addEdge(G, 4, 8);
	addEdge(G, 4, 9);
	addEdge(G, 4, 12);
	addEdge(G, 5, 6);
	addEdge(G, 6, 5);
	addEdge(G, 6, 7);
	addEdge(G, 6, 10);
	addEdge(G, 6, 11);
	addEdge(G, 7, 6);
	addEdge(G, 7, 11);
	addEdge(G, 8, 2);
	addEdge(G, 8, 3);
	addEdge(G, 8, 4);
	addEdge(G, 8, 12);
	addEdge(G, 9, 4);
	addEdge(G, 10, 6);
	addEdge(G, 11, 6);
	addEdge(G, 11, 7);
	addEdge(G, 12, 4);
	addEdge(G, 12, 8);
	printGraph(G);
	printf("\n");
	BFS(G, source);
	for (int i = 1; i <= order; i++) {
		printf("Distance from %d to %d is %d\n", source, i, getDist(G, i));
	}
	for (int i = 1; i <= order; i++) {
		printf("Parent of %d is %d\n", i, getParent(G, i));
	}


}
