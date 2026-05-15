#ifndef ADJACENCY_MULTI_LIST_H
#define ADJACENCY_MULTI_LIST_H
// 邻接多重表的边结构
typedef struct amlEdge {
	int iVex;						// 边的顶点i的编号
	struct amlEdge *iNext;			// 顶点i编号的下一条边
	int jVex;						// 边的顶点j的编号
	struct amlEdge *jNext;			// 顶点j编号的下一条边
	int weight;
	int mark;						// 是否已经显示图的这条边
} MultiListEdge;
// 邻接多重表的顶点结构
typedef struct {
	int no;
	char *show;
	MultiListEdge *firstEdge;		// 该顶点的边节点（这个边还有一个顶点会指向）
} MultiListVertex;
// 邻接多重表
typedef struct {
	MultiListVertex *nodes;
	int vertexNum;
	int edgeNum;
} AdjacencyMultiList;

AdjacencyMultiList *createMultiList(int n);
void releaseMultiList(AdjacencyMultiList *graph);
void initMultiList(AdjacencyMultiList *graph, char *names[], int n);

int insertMultiList(AdjacencyMultiList *graph, int a, int b, int w);
void showMultiList(const AdjacencyMultiList *graph);
void deleteMultiList(AdjacencyMultiList *graph, int a, int b);
#endif //ADJACENCY_MULTI_LIST_H