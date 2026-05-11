#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BSTree.h"

/* https://www.cs.usfca.edu/~galles/visualization/BST.html */
void test01() {
	element_t data[] = {55, 33, 45, 100, 22, 80, 8, 130, 120, 121, 122};
	BSTree *tree = createBSTree();

	for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
		insertBSTreeV1(tree, data[i]);
	}
	inOrderBSTree(tree);
	printf("tree height: %d\n", heightBSTree(tree));

	BSNode *result = searchBSTree(tree, 230);
	if (result) {
		printf("search %d success!\n", result->data);
	} else {
		printf("search failed!\n");
	}
	deleteBSTreeV1(tree, 422);
	inOrderBSTree(tree);

	releaseBSTree(tree);
}

// 线性查找法
void test02() {
	int n = 100000;
	srand(time(NULL) + 1);
	element_t *data = malloc(sizeof(element_t) * n);

	for (int i = 0; i < n; ++i) {
		data[i] = rand() % (n + 1000) + 1;
	}

	int cnt = 5000;
	clock_t start = clock();
	// 做了5000次实验
	for (int i = 0; i < cnt; ++i) {
		// 每次实验都从data里找一个不存在的值
		for (int j = 0; j < n; ++j) {
			if (data[j] == n + 5000) {
				printf("find error!\n");
			}
		}
	}
	clock_t end = clock();
	printf("linear find cost %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("==============================\n");
	BSTree *tree = createBSTree();
	for (int i = 0; i < n; ++i) {
		insertBSTreeV1(tree, data[i]);
	}
	start = clock();
	// 做了5000次实验
	for (int i = 0; i < cnt; ++i) {
		// 每次实验都从二叉搜索树中找一个不存在的值
		BSNode *res = searchBSTree(tree, n + 5000);
		if (res != NULL) {
			printf("BSTree find error!\n");
		}
	}

	end = clock();
	printf("BSTree find cost %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	releaseBSTree(tree);
	free(data);
}

void test03() {
	element_t data[] = {55, 33, 45, 100, 22, 80, 8, 130, 120, 121, 122};
	BSTree *tree = createBSTree();

	for (int i = 0; i < sizeof(data)/sizeof(data[0]); ++i) {
		insertBSTreeV2(tree, data[i]);
	}
	inOrderBSTree(tree);
	printf("tree height: %d\n", heightBSTree(tree));

	BSNode *result = searchBSTree(tree, 100);
	if (result) {
		printf("search %d success!\n", result->data);
	} else {
		printf("search failed!\n");
	}
	deleteBSTreeV2(tree, 80);
	inOrderBSTree(tree);

	releaseBSTree(tree);
}

int main() {
	test03();

	return 0;
}