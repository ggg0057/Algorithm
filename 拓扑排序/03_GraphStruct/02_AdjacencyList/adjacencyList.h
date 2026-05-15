#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
// 边的结构
typedef struct arcEdge {
	int		no;				// 边空间的索引号，以顶点到no的关系 出度关系
	int		weight;			// 这条边的权值
	struct arcEdge *next;	// 顶点的下一个出度
} ArcEdge;

// 顶点结构
typedef struct {
	int		no;				// 顶点的编号
	char *show;				// 顶点的显示内容
	ArcEdge *firstEdge;		// 指向第一个出度的节点，后续出度由边的next来指定
} ArcNode;

// 邻接表的图结构
typedef struct {
	ArcNode *nodes;			// 图中顶点的集合，邻接 连续空间
	int	nodeNum;			// 图中顶点的个数
	int	directed;			// 是否有向图
	int edgeNum;			// 图中的边数
	int *visited;			// 以访问编号，遍历的辅助数组
} AGraph;

AGraph *createAGraph(int n);			// 产生n个节点的邻接表的图
void releaseAGraph(AGraph *graph);		// 释放图

void initAGraph(AGraph *graph, char *names[], int num, int directed);
void addAGraph(AGraph *graph, int x, int y, int w);

// 深度遍历
void DFSAGraphTravel(const AGraph *graph, int v);
// 广度遍历
void BFSAGraphTravel(const AGraph *graph, int v);

// 重置访问标记
void resetAGraphVisited(AGraph *graph);
void visitAGraphNode(const ArcNode *node);
#endif //ADJACENCY_LIST_H