#ifndef DIJKSTRA_SHORT_PATH_H
#define DIJKSTRA_SHORT_PATH_H
/* Dijkstra算法通过邻接矩阵来进行算法设计 */
#include "../01_MatrixGraph/matrixGraph.h"
/* input: 邻接矩阵、单源点
 * output: 距离数组、路径数组，打印出单源点到指定节点的路径，到其的最短路径值
 */
void DijkstraMGraph(const MGraph *graph, int start, int dist[], int path[]);

/* 从path信息表里打印出到end_point点的路径信息*/
void showShortPath(const int path[], int num, int end_point);
#endif //DIJKSTRA_SHORT_PATH_H