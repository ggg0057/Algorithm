#include <stdio.h>
#include <stdlib.h>
#include "quickFindSet.h"

QuickFindSet* createQuickFindSet(int capacity) {
	QuickFindSet* setQF = malloc(sizeof(QuickFindSet));
	if (setQF == NULL) {
		return NULL;
	}
	setQF->data = malloc(sizeof(element_t) * capacity);
	setQF->groupID = malloc(sizeof(int) * capacity);
	setQF->capacity = capacity;
	setQF->n = 0;
	return setQF;
}

void releaseQuickFindSet(QuickFindSet *setQF) {
	if (setQF) {
		free(setQF->data);
		free(setQF->groupID);
		setQF->capacity = 0;
		setQF->n = 0;
		free(setQF);
	}
}

void initQuickFindSet(QuickFindSet *setQF, const element_t *data, int n) {
	if (n > setQF->capacity) {
		n = setQF->capacity;
	}
	for (int i = 0; i < n; ++i) {
		setQF->data[i] = data[i];
		setQF->groupID[i] = i;			// 每个元素初始化时各自是一个集团
	}
	setQF->n = n;
}

static int findIndex(const QuickFindSet* setQF, element_t e) {
	for (int i = 0; i < setQF->n; ++i) {
		if (setQF->data[i] == e) {
			return i;
		}
	}
	return -1;
}

int isSameQF(const QuickFindSet *setQF, element_t a, element_t b) {
	int indexA = -1, indexB = -1;
	indexA = findIndex(setQF, a);
	indexB = findIndex(setQF, b);
	if (indexA == -1 || indexB == -1) {
		return 0;
	}
	return setQF->groupID[indexA] == setQF->groupID[indexB];
}

void unionQF(const QuickFindSet *setQF, element_t a, element_t b) {
	int indexA = -1, indexB = -1;
	indexA = findIndex(setQF, a);
	indexB = findIndex(setQF, b);
	if (indexA == -1 || indexB == -1) {
		return ;
	}
	int groupA = setQF->groupID[indexA];
	int groupB = setQF->groupID[indexB];
	if (groupA == groupB) {
		return;
	}
	// 将groupB的所有成员改为groupA
	for (int i = 0; i < setQF->n; ++i) {
		if (setQF->groupID[i] == groupB) {
			setQF->groupID[i] = groupA;
		}
	}
}
