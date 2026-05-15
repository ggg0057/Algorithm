#include <stdio.h>
#include <stdlib.h>
#include "DijkstraShortPath.h"

void DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]) {
	int *mark = malloc(sizeof(int) * graph->nodeNum);
	// 1. 激活了start后，距离dist更新，path中start编号设置为-1，作为路径打印的结束标志
	for (int i = 0; i < graph->nodeNum; ++i) {
		dist[i] = graph->edges[start][i];
		mark[i] = 0;
		if (dist[i] < INF) {
			path[i] = start;
		} else {
			path[i] = -1;
		}
	}
	mark[start] = 1;
	path[start] = -1;
	dist[start] = 0;

	// 2. 找未访问节点中的最小值
	for (int i = 0; i < graph->nodeNum - 1; ++i) {	// 只需要再查找n-1次，确定剩余n-1个节点的最短路径信息
		// 2.1 在未激活的节点中，找到一个源点到其路径的最小值
		int tmpIndex = 0;
		int mini = INF;
		for (int j = 0; j < graph->nodeNum; ++j) {
			if (mark[j] == 0 && dist[j] < mini) {
				mini = dist[j];
				tmpIndex = j;
			}
		}
		mark[tmpIndex] = 1;
		// 2.2 以刚刚激活的节点出发，更新到dist数组里，单源点到其他店
		for (int j = 0; j < graph->nodeNum; ++j) {
			if (mark[j] == 0 && dist[tmpIndex] + graph->edges[tmpIndex][j] < dist[j]) {
				dist[j] = dist[tmpIndex] + graph->edges[tmpIndex][j];
				path[j] = tmpIndex;
			}
		}
	}
	free(mark);
}

// 定义一个满递增栈
void showShortPath(const int path[], int num, int end_point) {
	int *stack = malloc(sizeof(int) * num);
	int top = -1;
	// 1. 将上一个状态压入栈
	while (path[end_point] != -1) {
		stack[++top] = end_point;
		end_point = path[end_point];
	}
	stack[++top] = end_point;
	// 2. 弹栈打印
	while (top != -1) {
		printf("\t%d", stack[top--]);
	}
	printf("\n");
	free(stack);
}
