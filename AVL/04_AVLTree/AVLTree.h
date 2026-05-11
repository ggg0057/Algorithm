#ifndef AVLTREE_H
#define AVLTREE_H
typedef int element_t;
/* 平衡二叉树节点结构 */
typedef struct tree_node {
	element_t data;
	struct tree_node *left;
	struct tree_node *right;
	int height;
} AVLNode;
/* 平衡二叉树头结构 */
typedef struct {
	AVLNode *root;
	int count;
} AVLTree;

AVLTree *createAVLTree();				// 创建空的平衡二叉树
void releaseAVLTree(AVLTree *tree);		// 释放平衡二叉树节点及头节点
void visitAVLNode(const AVLNode *node);	// 访问平衡二叉树节点

void insertAVLTree(AVLTree *tree, element_t value);		// 向平衡二叉树插入节点
AVLNode *searchAVLTree(const AVLTree *tree, element_t value);	// 在平衡二叉树中查找节点
void deleteAVLTree(AVLTree *tree, element_t value);		// 从平衡二叉树删除节点

void inOrderAVLTree(const AVLTree *tree);	// 平衡二叉树中序遍历
int	heightAVLTree(const AVLTree *tree);		// 这棵树的高度
#endif //AVLTREE_H