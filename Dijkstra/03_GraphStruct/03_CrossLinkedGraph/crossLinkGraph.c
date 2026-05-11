#include <stdio.h>
#include <stdlib.h>
#include "crossLinkGraph.h"

CrossGraph *createCrossGraph(int n) {
	CrossGraph *graph = malloc(sizeof(CrossGraph));
	graph->nodes = malloc(sizeof(CrossVertex) * n);
	graph->numEdge = 0;
	graph->numVertex = n;
	return graph;
}

void releaseCrossGraph(CrossGraph *graph) {
	if (graph) {
		if (graph->nodes) {
			int num = 0;
			for (int i = 0; i < graph->numVertex; ++i) {
				ArcBox *box = graph->nodes[i].firstOut;
				while (box) {
					ArcBox *tmp = box;
					box = box->tailNext;
					free(tmp);
					num++;
				}
			}
			printf("released %d edges!\n", num);
			free(graph->nodes);
		}
		free(graph);
	}
}

void initCrossGraph(CrossGraph *graph, char *names[], int num) {
	for (int i = 0; i < num; ++i) {
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstIn = graph->nodes[i].firstOut = NULL;
	}
	graph->numVertex = num;
}

/* 出度关系	tail tailNext
 * 入度关系	head headNext
 */
void addCrossArc(CrossGraph *graph, int tail, int head, int w) {
	ArcBox *box = malloc(sizeof(ArcBox));
	box->weight = w;
	// 使用头插法，出度
	box->tailVertex = tail;
	box->tailNext = graph->nodes[tail].firstOut;
	graph->nodes[tail].firstOut = box;
	// 使用头插法，入度
	box->headVertex = head;
	box->headNext = graph->nodes[head].firstIn;
	graph->nodes[head].firstIn = box;
}

int inDegreeCrossGraph(const CrossGraph *graph, int no) {
	int count = 0;
	ArcBox *box = graph->nodes[no].firstIn;
	while (box) {
		count++;
		box = box->headNext;
	}
	return count;
}

int outDegreeCrossGraph(const CrossGraph *graph, int no) {
	int count = 0;
	ArcBox *box = graph->nodes[no].firstOut;
	while (box) {
		count++;
		box = box->tailNext;
	}
	return count;
}
