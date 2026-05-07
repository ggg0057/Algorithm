#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

static int maxNum(int a,  int b) {
	return a > b ? a : b;
}

static int h(const AVLNode* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

static int getBalance(const AVLNode* node) {
	if (node == NULL) {
		return 0;
	}
	return h(node->left) - h(node->right);
}

/* 左旋操作
 *     px
 *     |
 *     x
 *   /  \
 * lx    y
 *      / \
 *     ly ry
 * */
static AVLNode* leftRotate(AVLNode *x) {
	// 调整节点的关系
	AVLNode* y = x->right;
	x->right = y->left;
	y->left = x;
	// 更新x和y的高度，先更新x节点的高度再更新y节点的高度
	x->height = maxNum(h(x->left), h(x->right)) + 1;
	y->height = maxNum(h(y->left), h(y->right)) + 1;
	return y;
}

/* 右旋操作
 *       py
 *       |
 *       y
 *     /  \
 *    x   ry
 *   / \
 * lx  rx
 * */
static AVLNode* rightRotate(AVLNode* y) {
	AVLNode* x = y->left;
	y->left = x->right;
	x->right = y;
	// 更新x和y的高度，先更新y节点的高度再更新x节点的高度
	y->height = maxNum(h(y->left), h(y->right)) + 1;
	x->height = maxNum(h(x->left), h(x->right)) + 1;
	return x;
}

AVLTree *createAVLTree() {
	AVLTree *tree = malloc(sizeof(AVLTree));
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->count = 0;
	return tree;
}

static void freeAVLNode(AVLTree *tree, AVLNode *node) {
	if (node == NULL) {
		return;
	}
	freeAVLNode(tree, node->left);
	freeAVLNode(tree, node->right);
	free(node);
	tree->count--;
}

void releaseAVLTree(AVLTree *tree) {
	freeAVLNode(tree, tree->root);
	printf("released have %d tree_node!\n", tree->count);
	free(tree);
}

void visitAVLNode(const AVLNode *node) {
	if (node != NULL) {
		printf("\t<%d: %d>", node->data, node->height);
	}
}

static AVLNode* createAVLNode(element_t e) {
	AVLNode* node = malloc(sizeof(AVLNode));
	if (node == NULL) {
		return NULL;
	}
	node->left = node->right = NULL;
	node->data = e;
	node->height = 1;
	return node;
}

/* 递归从node节点开始插入元素e */
static AVLNode* insertAVLNode(AVLTree *tree, AVLNode* node, element_t e) {
	// 1. 递归找到插入的位置
	if (node == NULL) {
		// 递归到空位置处了，带着新节点原路返回，更新节点的高度，判断平衡因子
		AVLNode* newNode = createAVLNode(e);
		if (newNode == NULL) {
			return NULL;
		}
		tree->count++;
		return newNode;
	}
	// 1.1 递的过程
	if (e < node->data) {
		node->left = insertAVLNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertAVLNode(tree, node->right, e);
	} else {
		return node;
	}
	// 2. 平衡化的操作，在归的过程中
	// 2.1 更新归中的每个节点的高度
	node->height = 1 + maxNum(h(node->left), h(node->right));
	// 2.2 计算当前节点的平衡因子
	int balance = getBalance(node);
	if (balance > 1) {			// 失衡点 左边的高度高了，L
		// 失衡节点的左边节点 L 还是 R 出现新节点
		if (e > node->left->data) {
			// LR
			node->left = leftRotate(node->left);
		}
		// LL
		return rightRotate(node);
	}
	if (balance < -1) {			// 失衡点 右边的高度高了，R
		// 失衡节点的右边节点 R 还是 L 出现新节点
		if (e < node->right->data) {
			// RL
			node->right = rightRotate(node->right);
		}
		// RR
		return leftRotate(node);
	}
	return node;
}

/* 二叉平衡树插入元素e：
 * 1. 按二叉搜索树的规则，递归找到插入的位置
 * 2. 归的流程，更新原路径上节点的高度，同时计算平衡因子
 * 3. 如果发现条件满足，进行干预
 */
void insertAVLTree(AVLTree *tree, element_t value) {
	if (tree) {
		tree->root = insertAVLNode(tree, tree->root, value);
	}
}

AVLNode* searchAVLTree(const AVLTree *tree, element_t value) {
	AVLNode *current = tree->root;
	while (current != NULL) {
		if (value == current->data) {
			return current;
		}
		if (value < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return NULL;
}

static AVLNode* deleteAVLNode(AVLTree *tree, AVLNode *node, element_t e) {
	// 1. 找到要删除的节点
	if (node == NULL) {
		return NULL;
	}
	if (e < node->data) {
		node->left = deleteAVLNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteAVLNode(tree, node->right, e);
	} else {
		// 找到e的节点，判断该节点的度情况
		AVLNode *tmp;
		if (node->left == NULL || node->right == NULL) {
			tmp = node->left ? node->left : node->right;
			if (tmp == NULL) {
				// 度为0，直接删除node，返回NULL进行归
				tree->count--;
				free(node);
				return NULL;
			}
			// 度为1，
			node->data = tmp->data;
			node->left = tmp->left;
			node->right = tmp->right;
			tree->count--;
			free(tmp);
		}
		else {
			// 度为2，找前驱节点，更新当前度为2的点值，删除这个前驱节点
			tmp = node->left;
			while (tmp->right) {
				tmp = tmp->right;
			}
			node->data = tmp->data;
			node->left = deleteAVLNode(tree, node->left, tmp->data);
		}
	}
	// 2. 更新平衡因子，LL LR状态，由于是删除行为，不能判断当前节点和 值进行比较，只能用平衡因子的正负号来决定
	node->height = maxNum(h(node->left), h(node->right)) + 1;
	int balance = getBalance(node);
	if (balance > 1) {		// 左多 L
		if (getBalance(node->left) < 0) {
			// LR
			node->left = leftRotate(node->left);
		}
		// LL
		return rightRotate(node);
	}
	if (balance < -1) {		// 右多
		if (getBalance(node->right) > 0) {
			// RL
			node->right = rightRotate(node->right);
		}
		// RR
		return leftRotate(node);
	}
	return node;
}

/* 1. 按照二叉搜索树规则，递归找到元素value的节点
 * 2. 根据度，进行删除，度为2要找前驱或后继节点
 * 3. 原路返回，归的过程中，计算高度，根据平衡因子来调整
 */
void deleteAVLTree(AVLTree *tree, element_t value) {
	if (tree) {
		tree->root = deleteAVLNode(tree, tree->root, value);
	}
}

static void inOrderAVLNode(const AVLNode *node) {
	if (node == NULL) {
		return;
	}
	inOrderAVLNode(node->left);
	visitAVLNode(node);
	inOrderAVLNode(node->right);
}

void inOrderAVLTree(const AVLTree *tree) {
	inOrderAVLNode(tree->root);
	printf("\n");
}

int heightAVLTree(const AVLTree *tree) {
	return h(tree->root);
}

