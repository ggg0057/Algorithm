#include <stdio.h>
#include "binaryTree.h"

static BinaryTree *initTestTree() {
	BinaryTree *tree = createBinaryTree();

	TreeNode *nodeA = createTreeNode('A');
	TreeNode *nodeB = createTreeNode('B');
	TreeNode *nodeC = createTreeNode('C');
	TreeNode *nodeD = createTreeNode('D');
	TreeNode *nodeE = createTreeNode('E');
	TreeNode *nodeF = createTreeNode('F');
	TreeNode *nodeG = createTreeNode('G');
	TreeNode *nodeH = createTreeNode('H');
	TreeNode *nodeK = createTreeNode('K');

	initBinaryTree(tree, nodeA);
	insertBinaryTree(tree, nodeA, nodeB, nodeE);
	insertBinaryTree(tree, nodeB, NULL, nodeC);
	insertBinaryTree(tree, nodeC, nodeD, NULL);
	insertBinaryTree(tree, nodeE, NULL, nodeF);
	insertBinaryTree(tree, nodeF, nodeG, NULL);
	insertBinaryTree(tree, nodeG, nodeH, nodeK);
	return tree;
}

void test01() {
	BinaryTree *tree = initTestTree();
	printf("tree count: %d\n", tree->count);
	printf("    level travel: ");
	levelOrderBTree(tree);
	printf(" preOrder travel: ");
	preOrderBTree(tree);
	printf("  inOrder travel: ");
	inOrderBTree(tree);
	printf("postOrder travel: ");
	postOrderBTree(tree);
	releaseBinaryTree(tree);
}

void test02() {
	BinaryTree *tree = initTestTree();
	printf("tree count: %d\n", tree->count);
	printf(" preOrderV2 travel: ");
	preOrderBTreeV2(tree);
	printf("\n");
	inOrderBTreeV2(tree);
	printf("\n");
	postOrderBTreeV2(tree);
	printf("\n");
	releaseBinaryTree(tree);
}

int main() {
	test02();
	return 0;
}