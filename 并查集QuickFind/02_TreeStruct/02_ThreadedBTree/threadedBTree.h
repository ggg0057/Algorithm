#ifndef THREADED_BTREE_H
#define THREADED_BTREE_H
typedef char element_t;
// 线索二叉树的节点结构
typedef struct  tree_node {
	element_t data;
	struct tree_node* left;
	struct tree_node* right;
	int l_tag;		// 左标志，0表示指向左子树，1表示的指向前驱节点
	int r_tag;		// 右标志，0表示指向右子树，1表示的指向后继节点
} TreeNode;

typedef struct {
	TreeNode *root;
	int count;
} ThreadedBTree;

ThreadedBTree *createThreadedBTree();
void releaseThreadedBTree(ThreadedBTree *tree);
void initThreadedBTree(ThreadedBTree *tree, TreeNode *root);
TreeNode *createTreeNode(element_t data);
void visitTreeNode(const TreeNode *node);
void insertThreadedBTree(ThreadedBTree *tree,TreeNode *parent, TreeNode *left, TreeNode *right);

// 在原始树中构建线索
void inOrderThreading(ThreadedBTree *tree);
// 在已经线索化好的二叉树中，进行中序遍历（不是递归方式）
void inOrderThreadedTree(ThreadedBTree *tree);

#endif //THREADED_BTREE_H