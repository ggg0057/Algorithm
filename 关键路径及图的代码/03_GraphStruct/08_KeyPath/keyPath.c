#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyPath.h"

static int topologicalOrder(const AGraph* graph, int *ETV, int *LTV) {
	int *inDegree = malloc(sizeof(int) * graph->nodeNum);		// 入度记录表
	memset(inDegree, 0, sizeof(int) * graph->nodeNum);
	// 1. 初始化图中所有顶点的入度记录表
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (graph->nodes[i].firstEdge) {
			// 该节点有边时，统计边的情况更新入度记录表
			ArcEdge *edge = graph->nodes[i].firstEdge;
			while (edge) {
				++inDegree[edge->no];
				edge = edge->next;
			}
		}
	}
	// 2. 将入度为0的节点入栈，出栈时就可以找到各个顶点的最早发生时间
	int top = -1;
	int *stack = malloc(sizeof(int) * graph->nodeNum);
	int *topOut = malloc(sizeof(int) * graph->nodeNum);

	// 2.1 将初始化的入度表中，入度为0的顶点编号压入栈，此时这个点就是源点
	for (int i = 0; i < graph->nodeNum; ++i) {
		if (inDegree[i] == 0) {
			stack[++top] = i;
			break;				// 默认只有一个源点
		}
	}
	// 2.2 不断弹栈，更新入度记录表
	int tmp = 0;				// 暂存从栈上弹出的顶点编号，通过这个编号的出度情况，计算ETV
	int index = 0;				// 拓扑排序结果的索引
	while (top != -1) {
		tmp = stack[top--];
		topOut[index++] = tmp;c
		ArcEdge *edge = graph->nodes[tmp].firstEdge;
		while (edge) {
			--inDegree[edge->no];
			if (inDegree[edge->no] == 0) {
				stack[++top] = edge->no;
			}
			// 从tmp顶点的最早发生时间加上待删除的边
			if (ETV[tmp] + edge->weight > ETV[edge->no]) {
				ETV[edge->no] = ETV[tmp] + edge->weight;
			}
			edge = edge->next;
		}
	}
	// 拓扑排序结束，入度记录表、栈空间使命结束了
	free(inDegree);
	free(stack);
	if (index < graph->nodeNum) {
		// 有环
		free(topOut);
		return -1;
	}

	tmp = topOut[--index];			// 获取拓扑排序结果的最后一个顶点编号
	// 3. 更新LTV
	for (int i = 0; i < graph->nodeNum; ++i) {
		LTV[i] = ETV[tmp];
	}
	while (index) {
		int getTopNo = topOut[--index];
		ArcEdge *edge = graph->nodes[getTopNo].firstEdge;
		while (edge) {
			// 后一个节点的LTV减去入度边的权值
			if (LTV[edge->no] - edge->weight < LTV[getTopNo]) {
				LTV[getTopNo] = LTV[edge->no] - edge->weight;
			}
			edge = edge->next;
		}
	}
	free(topOut);
	return 0;
}

static void showTable(const int *table, int n, const char *name) {
	printf("%s\n", name);
	for (int i = 0; i < n; ++i) {
		printf("\t%d", table[i]);
	}
	printf("\n");
}

/* 为了求出一个给定的AOE网的关键路径，需要4个统计值：
 * 对于AOE网中的顶点有两个时间
 * ETV：事件最早发生的时间		LTV：事件最晚发生时间
 * 对于边来说有两个时间
 * ETE：活动最早发生的时间		LTE：活动最晚发生时间
 * 对于所有的边来说，它的最早发生时间等于最晚发生时间，这条边就是关键活动，这些关键活动构成的路径称之为关键路径
 */
void keyPath(const AGraph *graph) {
	// 1. 计算顶点的ETV和LTV
	int *ETV = malloc(sizeof(int) * graph->nodeNum);
	int *LTV = malloc(sizeof(int) * graph->nodeNum);
	if (ETV == NULL || LTV == NULL) {
		return;
	}
	memset(ETV, 0, sizeof(int) * graph->nodeNum);
	memset(LTV, 0, sizeof(int) * graph->nodeNum);
	topologicalOrder(graph, ETV, LTV);

	showTable(ETV, graph->nodeNum, "ETV: ");
	showTable(LTV, graph->nodeNum, "LTV: ");
	// 2. 计算边的ETE和LTE，直接计算关键路径
	for (int i = 0; i < graph->nodeNum; ++i) {
		ArcEdge *edge = graph->nodes[i].firstEdge;
		while (edge) {
			// 每个边的最早发生时间就是边的弧尾的ETV
			// 每个边的最晚发生时间就是边的弧头的LTV减去当前边的权重值
			if (ETV[i] == LTV[edge->no] - edge->weight) {
				printf("<%s> ---%d--- <%s>\n",
					graph->nodes[i].show, edge->weight, graph->nodes[edge->no].show);
			}
			edge = edge->next;
		}
	}
	free(ETV);
	free(LTV);
}
