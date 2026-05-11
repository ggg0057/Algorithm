#ifndef CROSS_LINK_GRAPH_H
#define CROSS_LINK_GRAPH_H
/* 十字链表 */
// 弧的结构
typedef struct arcBox {
	int tailVertex;					// 弧尾编号
	struct arcBox *tailNext;		// 下一个弧尾，出度
	int headVertex;					// 弧头编号
	struct arcBox *headNext;		// 下一个弧头，入度
	int weight;						// 弧的权值
} ArcBox;
// 顶点的结构
typedef struct {
	int no;
	const char *show;
	ArcBox *firstIn;				// 该节点的入度
	ArcBox *firstOut;				// 该节点的出度
} CrossVertex;

// 十字链表表示的图头
typedef struct {
	CrossVertex *nodes;
	int numVertex;
	int numEdge;
} CrossGraph;

CrossGraph *createCrossGraph(int n);
void releaseCrossGraph(CrossGraph * graph);
// 初始化图，设置节点信息
void initCrossGraph(CrossGraph *graph, char *names[], int num);
// 添加边，tail->head
void addCrossArc(CrossGraph *graph, int tail, int head, int w);
// 计算no编号的入度
int inDegreeCrossGraph(const CrossGraph *graph, int no);
// 计算no编号的出度
int outDegreeCrossGraph(const CrossGraph *graph, int no);
#endif //CROSS_LINK_GRAPH_H