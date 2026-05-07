#include <stdio.h>
#include <stdlib.h>
#include "Prim.h"

/* cost: 图中到各顶点边的权值数组
 * mark: 图中已经激活顶点的状态
 * visit:从哪个顶点访问当前顶点
 * startV: 第一个激活的顶点编号
 */
int PrimMGraph(const MGraph *graph, int startV, EdgeSet *result) {
	int *cost = malloc(sizeof(int) * graph->nodeNum);
	int *mark = malloc(sizeof(int) * graph->nodeNum);
	int *visit = malloc(sizeof(int) * graph->nodeNum);
	if (cost == NULL || mark == NULL || visit == NULL) {
		return 0;
	}
	int sum = 0;
	// 1. 根据传入的startV，激活当前节点，更新相关的辅助空间
	for (int i = 0; i < graph->nodeNum; ++i) {
		cost[i] = graph->edges[startV][i];
		mark[i] = 0;
		if (cost[i] < INF) {
			visit[i] = startV;
		} else {
			visit[i] = -1;
		}
	}
	mark[startV] = 1;

	// 2. 动态激活节点，直到全部激活为止
	for (int i = 0; i < graph->nodeNum - 1; ++i) {		// 查找n-1个最小生成树的边
		// 从权值数组里找到未激活节点里的最小值
		int mini = INF;
		int k = 0;							// 找最小值的辅助空间，当前最小值的顶点编号
		// 2.1 从cost数组内找到未激活节点里的最小值
		for (int j = 0; j < graph->nodeNum; ++j) {		// 从权值数组里找到未激活顶点的最小值
			if (mark[j] == 0 && cost[j] < mini) {
				mini = cost[j];
				k = j;
			}
		}
		mark[k] = 1;						// 激活最小值的点
		result[i].begin = k;
		result[i].end = visit[k];			// 从哪个节点来的
		result[i].weight = mini;
		sum += mini;

		// 3. 每激活一个顶点后，更新cost数组，以k为行下标，或者他到其他节点的权值，更新cost数组
		for (int j = 0; j < graph->nodeNum; ++j) {
			if (graph->edges[k][j] < cost[j]) {
				cost[j] = graph->edges[k][j];
				visit[j] = k;
			}
		}
	}

	free(cost);
	free(mark);
	free(visit);
	return sum;
}
