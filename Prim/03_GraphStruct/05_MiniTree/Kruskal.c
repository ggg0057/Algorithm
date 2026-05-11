#include "Kruskal.h"

#include <stdlib.h>
#include <string.h>

int initEdgeSet(const MGraph *graph, EdgeSet *edges) {
	int k = 0;
	for (int i = 0; i < graph->nodeNum; ++i) {			// 遍历每个节点
		for (int j = i + 1; j < graph->nodeNum; ++j) {	// 遍历每个节点的边，从i + 1开始，上三角
			if (graph->edges[i][j] > 0) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = graph->edges[i][j];
				k++;
			}
		}
	}
	return k;
}

void sortEdgeSet(EdgeSet *edges, int num) {
	EdgeSet tmp;
	for (int i = 0; i < num; ++i) {
		for (int j = i + 1; j < num; ++j) {
			if (edges[j].weight < edges[i].weight) {
				memcpy(&tmp, &edges[i], sizeof(EdgeSet));
				memcpy(&edges[i], &edges[j], sizeof(EdgeSet));
				memcpy(&edges[j], &tmp, sizeof(EdgeSet));
			}
		}
	}
}

static int getRoot(const int *uSet, int a) {
	while (a != uSet[a]) {
		a = uSet[a];
	}
	return a;
}

int KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result) {
	int sum = 0;
	// 1.初始化并查集，每一个节点的编号都是自己
	int *uSet = malloc(sizeof(int) * graph->nodeNum);
	for (int i = 0; i < graph->nodeNum; ++i) {
		uSet[i] = i;
	}
	int count = 0;
	// 2.从已经排好序的边集中，找到最小的边，当这个边加入后，不构成闭环，那这条边就是最小生成树的边
	for (int i = 0; i < num; ++i) {
		int a = getRoot(uSet, edges[i].begin);
		int b = getRoot(uSet, edges[i].end);

		if (a != b) {					// 不构成闭环
			uSet[a] = b;				// a的父节点是b
			result[count].begin = edges[i].begin;
			result[count].end = edges[i].end;
			result[count].weight = edges[i].weight;
			sum += edges[i].weight;
			count++;
			if (count == graph->nodeNum - 1) {
				break;
			}
		}
	}
	free(uSet);
	return sum;
}
