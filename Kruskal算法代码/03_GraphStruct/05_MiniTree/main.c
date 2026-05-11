#include <stdio.h>
#include <stdlib.h>
#include "Kruskal.h"

void setupMGraph(MGraph *graph, int edgeValue) {
	char *names[] = {
		"A", "B", "C", "D",
		"E", "F", "G",
	};
	initMGraph(graph, names, 7, 0, edgeValue);
	addMGraphEdge(graph, 0, 1, 12);
	addMGraphEdge(graph, 0, 5, 16);
	addMGraphEdge(graph, 0, 6, 14);
	addMGraphEdge(graph, 1, 2, 10);
	addMGraphEdge(graph, 1, 5, 7);
	addMGraphEdge(graph, 2, 3, 3);
	addMGraphEdge(graph, 2, 4, 5);
	addMGraphEdge(graph, 2, 5, 6);
	addMGraphEdge(graph, 3, 4, 4);
	addMGraphEdge(graph, 4, 5, 2);
	addMGraphEdge(graph, 4, 6, 8);
	addMGraphEdge(graph, 5, 6, 9);
}

int test01() {
	MGraph graph;
	EdgeSet *edges;				// 边集数组首地址
	int num;					// 边集数组的个数
	EdgeSet *result;			// 激活边的情况
	int sum;

	setupMGraph(&graph, 0);
	edges = malloc(sizeof(EdgeSet) * graph.edgeNum);
	num = initEdgeSet(&graph, edges);
	printf("edge set num : %d\n", num);
	sortEdgeSet(edges, num);

	result = malloc(sizeof(EdgeSet) * (graph.nodeNum - 1));
	sum = KruskalMGraph(&graph, edges, num, result);
	printf("Kruskal sum of weight: %d\n", sum);
	for (int i = 0; i < graph.nodeNum - 1; ++i) {
		printf("edge %d: [%s] --- <%d> --- [%s]\n", i + 1,
			graph.vex[result[i].begin].show, result[i].weight,graph.vex[result[i].end].show);
	}
	free(edges);
	free(result);
}

int main() {
	test01();

	return 0;
}