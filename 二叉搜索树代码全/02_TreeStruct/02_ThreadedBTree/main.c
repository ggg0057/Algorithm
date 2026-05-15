#include <stdio.h>
#include "threadedBTree.h"

static ThreadedBTree *initTestTree() {
	ThreadedBTree *tree = createThreadedBTree();

	TreeNode *nodeA = createTreeNode('A');
	TreeNode *nodeB = createTreeNode('B');
	TreeNode *nodeC = createTreeNode('C');
	TreeNode *nodeD = createTreeNode('D');
	TreeNode *nodeE = createTreeNode('E');
	TreeNode *nodeF = createTreeNode('F');
	TreeNode *nodeG = createTreeNode('G');
	TreeNode *nodeH = createTreeNode('H');
	TreeNode *nodeK = createTreeNode('K');

	initThreadedBTree(tree, nodeA);
	insertThreadedBTree(tree, nodeA, nodeB, nodeE);
	insertThreadedBTree(tree, nodeB, NULL, nodeC);
	insertThreadedBTree(tree, nodeC, nodeD, NULL);
	insertThreadedBTree(tree, nodeE, NULL, nodeF);
	insertThreadedBTree(tree, nodeF, nodeG, NULL);
	insertThreadedBTree(tree, nodeG, nodeH, nodeK);
	return tree;
}

int main() {
	ThreadedBTree *tree = initTestTree();
	printf("tree node: %d\n", tree->count);
	inOrderThreading(tree);
	inOrderThreadedTree(tree);
	printf("\n");
	releaseThreadedBTree(tree);

	return 0;
}