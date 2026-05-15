#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topologicalSort.h"

int TopologicalSortAGraph(const AGraph *graph) {
	// 1. 将有向图的所有节点的入度进行统计
	// 1.1 申请入度统计表
	int *inDegree = malloc(sizeof(int) * graph->nodeNum);
	if (inDegree == NULL) {
		return -1;
	}
	memset(inDegree, 0, sizeof(int) * graph->nodeNum);

	// 1.2 遍历邻接表，更新入度统计表
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (graph->nodes[i].firstEdge) {
			ArcEdge *edge = graph->nodes[i].firstEdge;
			while (edge) {
				++inDegree[edge->no];
				edge = edge->next;
			}
		}
	}

	// 2. 从记录表中，查找度为0的点，入栈（入队）。
	// 一旦入栈或入队，这个顶点的出度消失，更新记录表，发现出现了0，自动入缓存
	int *stack = malloc(sizeof(int) * graph->nodeNum);
	if (stack == NULL) {
		free(inDegree);
		return -1;
	}
	int top = -1;
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (inDegree[i] == 0) {
			stack[++top] = i;
		}
	}

	// 3. 从缓存区中取出一个任务，处理这个节点（打印），这个节点的出度对应的入度节点同时减减操作
	int count = 0;
	while (top != -1) {
		int index = stack[top--];
		++count;
		visitAGraphNode(&graph->nodes[index]);
		// 在index索引节点的出度节点，更新记录表
		ArcEdge *edge = graph->nodes[index].firstEdge;
		while (edge) {
			--inDegree[edge->no];
			if (inDegree[edge->no] == 0) {
				stack[++top] = edge->no;
			}
			edge = edge->next;
		}
	}
	free(inDegree);
	free(stack);
	if (count == graph->nodeNum) {
		return 0;
	} else {
		return -3;
	}
}
