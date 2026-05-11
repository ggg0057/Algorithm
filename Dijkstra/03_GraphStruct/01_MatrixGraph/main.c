#include <stdio.h>
#include "matrixGraph.h"

void setupMGraph(MGraph *graph) {
	char *nodeNames[] = {
		"V1", "V2", "V3", "V4",
		"V5", "V6", "V7", "V8"
	};
	initMGraph(graph, nodeNames, 8, 0, 0);
	addMGraphEdge(graph, 0, 1, 1);
	addMGraphEdge(graph, 0, 2, 1);
	addMGraphEdge(graph, 1, 3, 1);
	addMGraphEdge(graph, 1, 4, 1);
	addMGraphEdge(graph, 2, 5, 1);
	addMGraphEdge(graph, 2, 6, 1);
	addMGraphEdge(graph, 3, 7, 1);
	addMGraphEdge(graph, 4, 7, 1);
	addMGraphEdge(graph, 5, 6, 1);
}

int main() {
	MGraph g1;
	setupMGraph(&g1);

	printf("edge num = %d\n", g1.edgeNum);
	printf("DFS: ");
	DFSMGraphTravel(&g1, 0);

	initMGraphVisit();
	printf("\nBFS: ");
	BFSMGraphTravel(&g1, 0);
	return 0;
}