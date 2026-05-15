#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacencyList.h"

AGraph *createAGraph(int n) {
	AGraph *graph = malloc(sizeof(AGraph));
	if (graph == NULL) {
		return NULL;
	}
	graph->edgeNum = 0;
	graph->nodeNum = n;
	graph->nodes = malloc(sizeof(ArcNode) * n);
	graph->visited = malloc(sizeof(int) * n);
	// 初始化刚刚申请的空间
	memset(graph->nodes, 0, sizeof(ArcNode) * n);
	memset(graph->visited, 0, sizeof(int) * n);
	return graph;
}

void releaseAGraph(AGraph *graph) {
	int count = 0;
	ArcEdge *tmp;
	if (graph) {
		for (int i = 0; i < graph->nodeNum; ++i) {
			ArcEdge *edge = graph->nodes[i].firstEdge;
			while (edge) {
				tmp = edge;
				edge = edge->next;
				free(tmp);
				count++;
			}
		}
		printf("release %d edges!\n", count);
		free(graph->nodes);
		free(graph->visited);
		free(graph);
	}
}

void initAGraph(AGraph *graph, char *names[], int num, int directed) {
	graph->directed = directed;
	for (int i = 0; i < num; ++i) {
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstEdge = NULL;
	}
}

static ArcEdge *createArcEdge(int v, int w) {
	ArcEdge *edge = malloc(sizeof(ArcEdge));
	if (edge == NULL) {
		return NULL;
	}
	edge->no = v;
	edge->weight = w;
	edge->next = NULL;
	return edge;
}

void addAGraph(AGraph *graph, int x, int y, int w) {
	if (x < 0 || x >= graph->nodeNum || y < 0 || y >= graph->nodeNum) {
		return;
	}
	if (x == y) {
		return;
	}
	// 链表添加，头插法
	ArcEdge *edge = createArcEdge(y, w);
	edge->next = graph->nodes[x].firstEdge;
	graph->nodes[x].firstEdge = edge;
	graph->edgeNum++;
	if (graph->directed == 0) {		// 无向图
		edge = createArcEdge(x, w);
		edge->next = graph->nodes[y].firstEdge;
		graph->nodes[y].firstEdge = edge;
		graph->edgeNum++;
	}
}

void DFSAGraphTravel(const AGraph *graph, int v) {
	graph->visited[v] = 1;
	visitAGraphNode(&graph->nodes[v]);
	ArcEdge *p = graph->nodes[v].firstEdge;
	while (p) {
		if (graph->visited[p->no] == 0) {
			DFSAGraphTravel(graph, p->no);
		}
		p = p->next;
	}
}

void BFSAGraphTravel(const AGraph *graph, int v) {
	int *que = malloc(sizeof(int) * graph->nodeNum);
	int front = 0, rear = 0;

	rear = (rear + 1) % graph->nodeNum;
	que[rear] = v;							// 将第一个元素编号加入队列
	graph->visited[v] = 1;

	while (front != rear) {
		front = (front + 1) % graph->nodeNum;
		int cur = que[front];
		visitAGraphNode(&graph->nodes[cur]);

		ArcEdge *p = graph->nodes[cur].firstEdge;
		while (p) {
			if (graph->visited[p->no] == 0) {
				rear = (rear + 1) % graph->nodeNum;
				que[rear] = p->no;
				graph->visited[p->no] = 1;
			}
			p = p->next;
		}
	}
	free(que);
}

void resetAGraphVisited(AGraph *graph) {
	memset(graph->visited, 0, sizeof(int) * graph->nodeNum);
}

void visitAGraphNode(const ArcNode *node) {
	printf("\t%s", node->show);
}
