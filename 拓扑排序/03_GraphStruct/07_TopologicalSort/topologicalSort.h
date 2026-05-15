#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H
/* 1. 找到图中，入度为0的顶点，把这些顶点放入缓存中（栈、队列）
 * 2. 从缓存区中，取出一个顶点，放入到结果集
 * 3. 这个顶点的事件发生了，顶点的对应出度消失，有其他顶点的入度随之消失。
 * 4. 又会增加新的入度为0的顶点出现，如果出现，放入缓存
 * 5. 重复2-3-4
 * 6. 取出缓存中的所有顶点数量：a1，图中顶点的总个数为a2;
 * a1 == a2   没有环，a1 < a2     有环
 */
#include "../02_AdjacencyList//adjacencyList.h"

int TopologicalSortAGraph(const AGraph *graph);
#endif //TOPOLOGICAL_SORT_H