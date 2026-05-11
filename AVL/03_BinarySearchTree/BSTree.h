#ifndef BS_TREE_H
#define BS_TREE_H
typedef int element_t;
typedef struct bsNode {
	element_t data;
	struct bsNode *left;
	struct bsNode *right;
} BSNode;

typedef struct {
	BSNode *root;
	int count;
} BSTree;

BSTree* createBSTree();
void releaseBSTree(BSTree* tree);

// 按照二叉搜索树的规则插入数据（递归方式）
void insertBSTreeV1(BSTree* tree, element_t e);
// 查找二叉搜索树里值为e的节点
BSNode* searchBSTree(const BSTree* tree, element_t e);
// 按照二叉搜索树的规则删除数据（递归方式）
void deleteBSTreeV1(BSTree* tree, element_t e);

// 按照二叉搜索树的规则插入数据（非递归方式）
void insertBSTreeV2(BSTree* tree, element_t e);
// 按照二叉搜索树的规则删除数据（非递归方式）
void deleteBSTreeV2(BSTree* tree, element_t e);

void visitBSNode(const BSNode* node);
int heightBSTree(const BSTree* tree);
void inOrderBSTree(const BSTree* tree);

#endif //BS_TREE_H