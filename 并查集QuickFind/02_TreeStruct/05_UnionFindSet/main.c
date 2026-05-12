#include <stdio.h>
#include "quickFindSet.h"

void test01() {
	int n = 9;
	QuickFindSet *QFSet = createQuickFindSet(n);
	element_t data[9];
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		data[i] = i;
	}
	initQuickFindSet(QFSet, data, n);

	unionQF(QFSet, 3, 4);
	unionQF(QFSet, 8, 0);
	unionQF(QFSet, 2, 3);
	unionQF(QFSet, 5, 6);
	isSameQF(QFSet, 0, 2) ? printf("Yes\n") : printf("No\n");
	isSameQF(QFSet, 2, 4) ? printf("Yes\n") : printf("No\n");
	unionQF(QFSet, 5, 1);
	unionQF(QFSet, 7, 3);
	unionQF(QFSet, 1, 6);
	unionQF(QFSet, 4, 8);
	isSameQF(QFSet, 0, 2) ? printf("Yes\n") : printf("No\n");
	isSameQF(QFSet, 2, 4) ? printf("Yes\n") : printf("No\n");

	releaseQuickFindSet(QFSet);
}

int main() {
	test01();

	return 0;
}