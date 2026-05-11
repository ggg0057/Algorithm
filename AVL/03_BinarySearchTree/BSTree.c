#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

#include <time.h>

BSTree* createBSTree() {
	BSTree* tree = malloc(sizeof(BSTree));
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->count = 0;
	return tree;
}

static void freeNode(BSTree *tree, BSNode *node) {
	if (node == NULL) {
		return;
	}
	freeNode(tree, node->left);
	freeNode(tree, node->right);
	free(node);
	tree->count--;
}

void releaseBSTree(BSTree *tree) {
	if (tree) {
		freeNode(tree, tree->root);
		printf("Tree have lost %d node!\n", tree->count);
		free(tree);
	}
}

static BSNode* createBSNode(element_t e) {
	BSNode* node = malloc(sizeof(BSNode));
	if (node == NULL) {
		return NULL;
	}
	node->left = node->right = NULL;
	node->data = e;
	return node;
}

static BSNode* insertBSNode(BSTree *tree, BSNode *node, element_t e) {
	if (node == NULL) {
		tree->count++;
		return createBSNode(e);
	}
	if (e < node->data) {
		node->left = insertBSNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertBSNode(tree, node->right, e);
	}
	return node;
}

void insertBSTreeV1(BSTree *tree, element_t e) {
	if (tree == NULL) {
		return;
	}
	tree->root = insertBSNode(tree, tree->root, e);
}

BSNode* searchBSTree(const BSTree *tree, element_t e) {
	if (tree == NULL) {
		return NULL;
	}
	BSNode *current = tree->root;
	while (current) {
		if (e == current->data) {
			return current;
		}
		if (e < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return NULL;
}

static BSNode* miniValueBSNode(BSNode *node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

static BSNode* deleteBSNode(BSTree *tree, BSNode *node, element_t e) {
	if (node == NULL) {
		return NULL;
	}
	if (e < node->data) {
		node->left = deleteBSNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteBSNode(tree, node->right, e);
	} else {		// 找到e值所在的节点
		BSNode *tmp;
		if (node->left == NULL) {
			tmp = node->right;
			free(node);
			tree->count--;
			return tmp;
		}
		if (node->right == NULL) {
			tmp = node->left;
			free(node);
			tree->count--;
			return tmp;
		}
		// 此时，说明待删除的节点，有左右子树
		tmp = miniValueBSNode(node->right);
		node->data = tmp->data;
		node->right = deleteBSNode(tree, node->right, tmp->data);
	}
	return node;
}

void deleteBSTreeV1(BSTree *tree, element_t e) {
	if (tree == NULL) {
		return;
	}
	tree->root = deleteBSNode(tree, tree->root, e);
}

void insertBSTreeV2(BSTree *tree, element_t e) {
	if (tree == NULL) {
		return;
	}
	BSNode *pre = NULL;
	BSNode *cur = tree->root;
	while (cur) {
		pre = cur;
		if (e < cur->data) {
			cur = cur->left;
		} else if (e > cur->data) {
			cur = cur->right;
		} else {
			return;
		}
	}
	BSNode *newNode = createBSNode(e);
	if (pre == NULL) {
		tree->root = newNode;
	} else if (e < pre->data) {
		pre->left = newNode;
	} else {
		pre->right = newNode;
	}
	tree->count++;
}

void deleteBSTreeV2(BSTree *tree, element_t e) {
	if (tree == NULL) {
		return;
	}
	BSNode *pre = NULL;
	BSNode *cur = tree->root;
	// 1. 找到待删除的节点cur，以及他的父节点pre
	while (cur && cur->data != e) {
		pre = cur;
		if (e < cur->data) {
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}
	if (cur == NULL) {			// 没有找到待删除的节点
		return;
	}
	// 2. 开始删除节点cur
	if (cur->left == NULL || cur->right == NULL) {
		BSNode *newCur;
		if (cur->left) {
			newCur = cur->left;
		} else {
			newCur = cur->right;
		}
		if (pre == NULL) {
			tree->root = newCur;
		} else if (pre->left == cur) {
			pre->left = newCur;
		} else {
			pre->right = newCur;
		}
		free(cur);
		tree->count--;
	} else {
		// 待删除节点有两个子节点
		BSNode *tmpPre = cur;
		BSNode *tmpCur = cur->right;
		// 找后继节点，以及后继节点的父节点
		while (tmpCur->left) {
			tmpPre = tmpCur;
			tmpCur = tmpCur->left;
		}
		cur->data = tmpCur->data;
		if (tmpPre->left == tmpCur) {
			tmpPre->left = tmpCur->right;
		} else {
			tmpPre->right = tmpCur->right;
		}
		free(tmpCur);
		tree->count--;
	}
}

void visitBSNode(const BSNode *node) {
	if (node) {
		printf("%d ", node->data);
	}
}

static int heightBSNode(const BSNode *node) {
	if (node == NULL) {
		return 0;
	}
	int leftHeight = heightBSNode(node->left);
	int rightHeight = heightBSNode(node->right);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int heightBSTree(const BSTree *tree) {
	if (tree == NULL) {
		return 0;
	}
	return heightBSNode(tree->root);
}

static void inOrderBSNode(const BSNode *node) {
	if (node == NULL) {
		return;
	}
	inOrderBSNode(node->left);
	visitBSNode(node);
	inOrderBSNode(node->right);
}

void inOrderBSTree(const BSTree *tree) {
	if (tree == NULL) {
		return;
	}
	inOrderBSNode(tree->root);
	printf("\n");
}


