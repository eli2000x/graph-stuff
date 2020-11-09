

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {

	
	int order = 8;
	Graph G = newGraph(order);
	List S = newList();
	for (int i = 1; i <= order; i++) {
		append(S, i);
	}
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 7);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 7, 8);
	addArc(G, 8, 8);
	fprintf("Order is %d\n", getOrder(G));
	fprintf("Size is %d\n", getSize(G));
	printGraph(G);
	printList(S);

	for (int i = 1; i <= order; i++) {
		printf("%d: Parent is %d\n", i, getParent(G, i));
		printf("%d: Discover is %d\n", i, getDiscover(G, i));
		printf("%d: Finish is %d\n", i, getFinish(G, i));
	}

	DFS(G, S);

	printGraph(G);
	printList(S);

	for (int i = 1; i <= order; i++) {
		printf("%d: Parent is %d\n", i, getParent(G, i));
		printf("%d: Discover is %d\n", i, getDiscover(G, i));
		printf("%d: Finish is %d\n", i, getFinish(G, i));
	}

	Graph H = transpose(G);
	fprintf("Order is %d\n", getOrder(G));
	fprintf("Size is %d\n", getSize(G));
	printGraph(G);
	printList(S);

	for (int i = 1; i <= order; i++) {
		printf("%d: Parent is %d\n", i, getParent(G, i));
		printf("%d: Discover is %d\n", i, getDiscover(G, i));
		printf("%d: Finish is %d\n", i, getFinish(G, i));
	}

	DFS(H, S);

	printGraph(G);
	printList(S);

	for (int i = 1; i <= order; i++) {
		printf("%d: Parent is %d\n", i, getParent(G, i));
		printf("%d: Discover is %d\n", i, getDiscover(G, i));
		printf("%d: Finish is %d\n", i, getFinish(G, i));
	}


	freeGraph(&G);
	freeGraph(&H);
	freeGraph(&S);
	

}
