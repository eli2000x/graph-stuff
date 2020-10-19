
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {

	// check for command line arguments != 3
	if (argc != 3) {
		printf("Command line arguments != 3\n" );
		exit(EXIT_FAILURE);
	}

	// open files
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

	// local variables
	int order = 0;
	int* orderPtr = &order;
	fscanf(in, "%d", orderPtr);
	Graph G = newGraph(order);
	List L = newList();
	int vertex = 0;
	int firstline = 0;
	int vertex1 = 0;
	int edge = 1;
	int end = 0;
	int* vertexptr = &vertex;
	int* vertex1ptr = &vertex1;

	// perform operations on input file
	while (fgets(input, 1000, in) != NULL) {

		sscanf(input, "%d %d", vertexptr, vertex1ptr);
		if (*vertexptr == 0 && *vertex1ptr == 0 && firstline == 1) {
			end++;
		}

		if (*vertexptr == 0 && end == 0 && firstline == 0) {
			firstline = 1;
			continue;
		}

		sscanf(input, "%d %d", vertexptr, vertex1ptr);

		if (*vertexptr == 0 && *vertex1ptr == 0 && edge == 1) {
			printGraph(out, G);
			edge = 0;
			continue;
		}
		if (end == 2) {
			break;
		}
		if (edge == 1) {
			addEdge(G, vertex, vertex1);
		}
		if (edge == 0) {

			BFS(G, *vertexptr);
			if (getParent(G, *vertexptr) == 0) {
				fprintf(out, "\n");
				fprintf(out, "\nThe distance from %d to %d is %s", *vertexptr, *vertex1ptr, "infinity");
				fprintf(out, "\nNo %d-%d path exists", *vertexptr, *vertex1ptr);
				continue;
			}
			getPath(L, G, *vertex1ptr);

			if (front(L) == NIL) {
				fprintf(out, "\n");
				fprintf(out, "\nThe distance from %d to %d is %s", *vertexptr, *vertex1ptr, "infinity");
				fprintf(out, "\nNo %d-%d path exists", *vertexptr, *vertex1ptr);
			} else {
				fprintf(out, "\n");
				fprintf(out, "\nThe distance from %d to %d is %d", *vertexptr, *vertex1ptr, getDist(G, *vertex1ptr));
				fprintf(out, "\nA shortest %d-%d path is: ", *vertexptr, *vertex1ptr);
				printList(out, L);
			}

			clear(L);
		}
	}

	// free and close
	freeList(&L);
	freeGraph(&G);
	fclose(in);
	fclose(out);




}
