#include <stdio.h>
#include <stdlib.h>
#include "adjacencyMultiList.h"

AdjacencyMultiList *createMultiList(int n) {
	AdjacencyMultiList *multi_list = malloc(sizeof(AdjacencyMultiList));
	multi_list->nodes = malloc(sizeof(MultiListVertex) * n);
	multi_list->vertexNum = n;
	multi_list->edgeNum = 0;
	return multi_list;
}

void initMultiList(AdjacencyMultiList *graph, char *names[], int n) {
	for (int i = 0; i < n; ++i) {
		graph->nodes[i].no = i;
		graph->nodes[i].show = names[i];
		graph->nodes[i].firstEdge = NULL;
	}
	graph->vertexNum = n;
}

// 插入的是a节点和b节点之间的边
int insertMultiList(AdjacencyMultiList *graph, int a, int b, int w) {
	if (a < 0 || b < 0)
		return -1;
	// 产生这条边
	MultiListEdge *edge = malloc(sizeof(MultiListEdge));
	edge->weight = w;
	// 处理这条边，处理a节点连接关系
	edge->iVex = a;
	edge->iNext = graph->nodes[a].firstEdge;
	graph->nodes[a].firstEdge = edge;
	// 处理这条边，处理b节点连接关系
	edge->jVex = b;
	edge->jNext = graph->nodes[b].firstEdge;
	graph->nodes[b].firstEdge = edge;

	graph->edgeNum++;
	return 0;
}

static void initMark(const AdjacencyMultiList *graph) {
	for (int i = 0; i < graph->vertexNum; ++i) {
		MultiListEdge *edge = graph->nodes[i].firstEdge;
		while (edge) {
			edge->mark = 0;
			if (edge->iVex == i) {
				edge = edge->iNext;
			} else {
				edge = edge->jNext;
			}
		}
	}
}

void showMultiList(const AdjacencyMultiList *graph) {
	initMark(graph);
	for (int i = 0; i < graph->vertexNum; ++i) {
		MultiListEdge *edge = graph->nodes[i].firstEdge;
		while (edge && edge->mark == 0) {
			printf("<%s --- %s>\n", graph->nodes[edge->iVex].show, graph->nodes[edge->jVex].show);
			edge->mark = 1;
			if (edge->iVex == i) {
				edge = edge->iNext;
			} else {
				edge = edge->jNext;
			}
		}
	}
}

void deleteMultiList(AdjacencyMultiList *graph, int a, int b) {
	// 找到a编号的前一个边节点
	MultiListEdge *aPreEdge = NULL;
	MultiListEdge *aCurEdge = graph->nodes[a].firstEdge;
	while (aCurEdge &&
		!((aCurEdge->iVex == a && aCurEdge->jVex == b) || (aCurEdge->jVex == a && aCurEdge->iVex == b))) {
		aPreEdge = aCurEdge;
		if (aCurEdge->iVex == a) {
			aCurEdge = aCurEdge->iNext;
		} else {
			aCurEdge = aCurEdge->jNext;
		}
	}
	if (aCurEdge == NULL) {
		return;
	}
	// 找到b编号的前一个边节点
	MultiListEdge *bPreEdge = NULL;
	MultiListEdge *bCurEdge = graph->nodes[b].firstEdge;
	while (bCurEdge &&
		!((bCurEdge->iVex == a && bCurEdge->jVex == b) || (bCurEdge->iVex == b && bCurEdge->jVex == a))) {
		bPreEdge = bCurEdge;
		if (bCurEdge->iVex == b) {
			bCurEdge = bCurEdge->iNext;
		} else {
			bCurEdge = bCurEdge->jNext;
		}
	}
	if (bCurEdge == NULL) {
		return;
	}

	if (aPreEdge == NULL) {
		if (aCurEdge->iVex == a) {
			graph->nodes[a].firstEdge = aCurEdge->iNext;
		} else {
			graph->nodes[a].firstEdge = aCurEdge->jNext;
		}
	} else {
		if (aPreEdge->iVex == a && aCurEdge->iVex == a) {
			aPreEdge->iNext = aCurEdge->iNext;
		} else if (aPreEdge->iVex == a && aCurEdge->jVex == a) {
			aPreEdge->iNext = aCurEdge->jNext;
		} else if (aPreEdge->jVex == a && aCurEdge->iVex == a) {
			aPreEdge->jNext = aCurEdge->iNext;
		} else {
			aPreEdge->jNext = aCurEdge->jNext;
		}
	}
	if (bPreEdge == NULL) {
		if (bCurEdge->iVex == b) {
			graph->nodes[b].firstEdge = bCurEdge->iNext;
		} else {
			graph->nodes[b].firstEdge = bCurEdge->jNext;
		}
	} else {
		if (bPreEdge->iVex == b && bCurEdge->iVex == b) {
			bPreEdge->iNext = bCurEdge->iNext;
		} else if (bPreEdge->iVex == b && bCurEdge->jVex == b) {
			bPreEdge->iNext = bCurEdge->jNext;
		} else if (bPreEdge->jVex == b && bCurEdge->iVex == b) {
			bPreEdge->jNext = bCurEdge->iNext;
		} else {
			bPreEdge->jNext = bCurEdge->jNext;
		}
	}
	free(aCurEdge);
	graph->edgeNum--;
}
