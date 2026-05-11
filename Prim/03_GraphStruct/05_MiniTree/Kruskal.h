#ifndef KRUSKAL_H
#define KRUSKAL_H
/* Kruskal算法：
 *	m条边，n个顶点，m条边中找n-1条边，n-1条边之和是最小的，且是生成树
 *	约束，必须保证这条边加入后，不会产生环
 * 如何判断一条边加入后，无向图是否含有环，引入并查集
 * 算法思路：
 *	1. 构建一个边集数组，进行升序排列，从小到大一一获取，满足条件：
 *	2. 加入的这条边是否会形成环路，形成这条边放弃，找下一条边
 */
// 使用邻接矩阵来表示无向图
#include "../01_MatrixGraph/matrixGraph.h"
#include "common.h"

// 从邻接矩阵中初始化边集数组
int initEdgeSet(const MGraph *graph, EdgeSet *edges);
// 排序边集数组
void sortEdgeSet(EdgeSet *edges, int num);
// Kruskal生成最小生成树
int KruskalMGraph(const MGraph *graph, const EdgeSet *edges, int num, EdgeSet *result);
#endif //KRUSKAL_H