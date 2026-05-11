#ifndef PRIM_H
#define PRIM_H
#include "../01_MatrixGraph/matrixGraph.h"
#include "common.h"

/* Prim算法：
 * 动态维护一个待激活顶点的边权值的数组，某个顶点到当前节点的哪条边的权值信息
 * 以访问节点的visit数组，到某个顶点的另外一个顶点坐标，构成了边
 */
int PrimMGraph(const MGraph *graph, int startV, EdgeSet *result);
#endif //PRIM_H