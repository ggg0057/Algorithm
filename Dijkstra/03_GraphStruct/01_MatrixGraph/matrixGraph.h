#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
// 邻接矩阵的顶点结构，每个顶点的结构
typedef struct {
	int no;			// 顶点的编号
	char *show;		// 顶点的显示数据，考试可以不管
} MatrixVertex;
// 邻接矩阵的边结构，每条边的结构，用int空间表示，既可以描述权值，也可以描述布尔值是否有边
typedef int MatrixEdge;

#define MaxNodeNum		20
#define INF				1E4
/* 邻接矩阵的图结构 */
typedef struct {
	MatrixVertex vex[MaxNodeNum];		// 存储顶点的信息，使用一维数组
	int nodeNum;						// 约束实际顶点的个数
	MatrixEdge edges[MaxNodeNum][MaxNodeNum];		// 邻接矩阵定义矩阵空间
	int directed;						// 是否是有向图
	int edgeNum;						// 定义图的边数
} MGraph;

void initMGraph(MGraph *graph, char *names[], int num, int directed, int edgeValue);
// 将x号节点和y号节点添加一条边，权值是w，如果是无向图，自动完成y到x的赋值
void addMGraphEdge(MGraph *graph, int x, int y, int w);
void visitMGraphNode(const MatrixVertex *node);
void initMGraphVisit();

void DFSMGraphTravel(const MGraph *graph, int startV);		// 深度搜索，startV起点
void BFSMGraphTravel(const MGraph *graph, int startV);		// 广度搜索，startV起点

#endif //MATRIX_GRAPH_H