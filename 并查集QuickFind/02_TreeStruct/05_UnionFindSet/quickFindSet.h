#ifndef QUICK_FIND_SET_H
#define QUICK_FIND_SET_H
typedef int element_t;

typedef struct {
	element_t *data;		// 存放数据的，采用顺序存储，自带了下标索引，作为关系数组里的索引值
	int *groupID;			// groupID[i] 表示第i个元素说归属的集团编号
	int n;					// 集合中元素的个数
	int capacity;			// 集合的容量
} QuickFindSet;

QuickFindSet* createQuickFindSet(int capacity);
void releaseQuickFindSet(QuickFindSet* setQF);
// 初始化并查集，填写元素的值和构建初始化关系
void initQuickFindSet(QuickFindSet* setQF, const element_t *data, int n);
// 查：在并查集中，判断两个元素是不是同一个集团
int isSameQF(const QuickFindSet* setQF, element_t a, element_t b);
// 并：在并查集中，合并两个元素
void unionQF(const QuickFindSet* setQF, element_t a, element_t b);

#endif //QUICK_FIND_SET_H