#include <stdio.h>
#include <stdlib.h>
#include "threadedBTree.h"

ThreadedBTree *createThreadedBTree() {
	ThreadedBTree *tree = malloc(sizeof(ThreadedBTree));
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;
}

static void freeTreeNode(ThreadedBTree *tree, TreeNode *node) {
	if (node) {
		if (node->l_tag == 0) {
			freeTreeNode(tree, node->left);
		}
		if (node->r_tag == 0) {
			freeTreeNode(tree, node->right);
		}
		free(node);
		tree->count--;
	}
}

void releaseThreadedBTree(ThreadedBTree *tree) {
	if (tree) {
		freeTreeNode(tree, tree->root);
		printf("tree have lost %d node\n", tree->count);
		free(tree);
	}
}

void initThreadedBTree(ThreadedBTree *tree, TreeNode *root) {
	if (tree && tree->root == NULL) {
		tree->root = root;
		tree->count = 1;
	}
}

TreeNode *createTreeNode(element_t data) {
	TreeNode *node = malloc(sizeof(TreeNode));
	if (node) {
		node->data = data;
		node->left = NULL;
		node->l_tag = 0;
		node->right = NULL;
		node->r_tag = 0;
	}
	return node;
}

void visitTreeNode(const TreeNode *node) {
	if (node) {
		printf("\t%c", node->data);
	}
}

void insertThreadedBTree(ThreadedBTree *tree,TreeNode *parent, TreeNode *left, TreeNode *right) {
	if (tree && parent) {
		parent->left = left;
		parent->right = right;
		tree->count += (left ? 1 : 0) + (right ? 1 : 0);
	}
}

static TreeNode *prev = NULL;
static void inThreading(TreeNode *node) {
	if (node == NULL) {
		return;
	}
	// 递归左子树
	inThreading(node->left);
	// 开始处理当前节点
	if (node->left == NULL) {
		node->l_tag = 1;
		node->left = prev;
	}
	if (prev != NULL && prev->right == NULL) {
		prev->r_tag = 1;
		prev->right = node;
	}
	prev = node;
	// 递归右子树
	inThreading(node->right);
}

void inOrderThreading(ThreadedBTree *tree) {
	if (tree && tree->root) {
		prev = NULL;
		inThreading(tree->root);
		if (prev != NULL) {
			prev->right = NULL;
			prev->r_tag = 1;
		}
	}
}

void inOrderThreadedTree(ThreadedBTree *tree) {
	if (tree && tree->root) {
		TreeNode *node = tree->root;
		// 找中序遍历的第一个节点
		while (node->l_tag == 0) {
			node = node->left;
		}
		// 线性遍历方式
		while (node) {
			visitTreeNode(node);
			// 如果右标志为1，说明右指针是后继节点
			if (node->r_tag == 1) {
				node = node->right;
			} else {
				// 不是线索化的节点，找到一个可以作为下一个访问的node节点
				node = node->right;
				while (node && node->l_tag == 0) {
					node = node->left;
				}
			}
		}
	}
}
