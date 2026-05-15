#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

BSTree* createBSTree() {
	BSTree* tree = malloc(sizeof(BSree));
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


