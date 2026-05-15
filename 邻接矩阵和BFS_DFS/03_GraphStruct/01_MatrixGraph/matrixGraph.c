#include <stdio.h>
#include <string.h>
#include "matrixGraph.h"

static int isEdge(int weight) {
	if (weight > 0 && weight < INF) {
		return 1;
	}
	return 0;
}

void initMGraph(MGraph *graph, char *names[], int num, int directed, int edgeValue) {
	graph->directed = directed;
	graph->edgeNum = 0;
	graph->nodeNum = num;

	for (int i = 0; i < num; ++i) {
		graph->vex[i].no = i;
		graph->vex[i].show = names[i];
		for (int j = 0; j < num; ++j) {
			graph->edges[i][j] = edgeValue;
		}
	}
}

void addMGraphEdge(MGraph *graph, int x, int y, int w) {
	if (x < 0 || x > graph->nodeNum)
		return;
	if (y < 0 || y > graph->nodeNum)
		return;
	if (!isEdge(graph->edges[x][y])) {
		graph->edges[x][y] = w;
		if (graph->directed == 0) {
			graph->edges[y][x] = w;
		}
		graph->edgeNum++;
	}
}
void visitMGraphNode(const MatrixVertex *node) {
	printf("\t%s", node->show);
}
static int MGraphVisited[MaxNodeNum];
void DFSMGraphTravel(const MGraph *graph, int startV) {
	visitMGraphNode(&graph->vex[startV]);
	MGraphVisited[startV] = 1;
	// 从starV开始，找到一个边节点，再通过这个节点找下一个，DFS
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (isEdge(graph->edges[startV][i]) && MGraphVisited[i] == 0) {
			DFSMGraphTravel(graph, i);
		}
	}
}
void initMGraphVisit() {
	memset(MGraphVisited, 0, sizeof(MGraphVisited));
}

void BFSMGraphTravel(const MGraph *graph, int startV) {
	int que[MaxNodeNum];
	int rear = 0, front = 0;

	rear = (rear + 1) % MaxNodeNum;
	que[rear] = startV;
	MGraphVisited[startV] = 1;
	while (front != rear) {
		front = (front + 1) % MaxNodeNum;
		int cur = que[front];

		visitMGraphNode(&graph->vex[cur]);
		for (int i = 0; i < graph->nodeNum; ++i) {
			if (isEdge(graph->edges[cur][i]) && !MGraphVisited[i]) {
				rear = (rear + 1) % MaxNodeNum;
				que[rear] = i;
				MGraphVisited[i] = 1;
			}
		}
	}
}
