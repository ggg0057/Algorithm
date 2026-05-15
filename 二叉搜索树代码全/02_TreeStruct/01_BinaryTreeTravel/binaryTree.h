#ifndef BINARYTREE_H
#define BINARYTREE_H
typedef char element_t;
// 二叉树的节点结构
typedef struct  tree_node {
	element_t data;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;
// 二叉树的树头结构
typedef struct {
	TreeNode *root;
	int count;
} BinaryTree;

BinaryTree *createBinaryTree();
void releaseBinaryTree(BinaryTree *tree);

void initBinaryTree(BinaryTree *tree, TreeNode *root);
TreeNode *createTreeNode(element_t data);
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right);
void visitTreeNode(const TreeNode *node);

// 广度遍历
void levelOrderBTree(const BinaryTree *tree);
// 深度遍历 一直走，直到走不动，返回，处理另外一条路径
void preOrderBTree(const BinaryTree *tree);
void inOrderBTree(const BinaryTree *tree);
void postOrderBTree(const BinaryTree *tree);

#endif //BINARYTREE_H