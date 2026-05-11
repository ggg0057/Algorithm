#include <stdio.h>
#include "AVLTree.h"

void testAVLTree() {
	AVLTree *tree = createAVLTree();
	element_t values[] = {30, 20, 40, 10, 25, 35, 50, 5};

	for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
		insertAVLTree(tree, values[i]);
	}
	// 验证是否是二叉搜索树
	inOrderAVLTree(tree);
	// 验证是否是平衡树
	printf("Tree height: %d\n", heightAVLTree(tree));

	element_t searchTestValues[] = {25, 100};
	for (int i = 0; i < sizeof(searchTestValues) / sizeof(searchTestValues[0]); ++i) {
		AVLNode *result = searchAVLTree(tree, searchTestValues[i]);
		if (result) {
			printf("Found %d in the tree!\n", searchTestValues[i]);
		} else {
			printf("%d not found in the tree!\n", searchTestValues[i]);
		}
	}
	deleteAVLTree(tree, 10);
	printf("Tree height: %d\n", heightAVLTree(tree));
	inOrderAVLTree(tree);
	deleteAVLTree(tree, 30);
	inOrderAVLTree(tree);

	releaseAVLTree(tree);
}

int main() {
	testAVLTree();

	return 0;
}