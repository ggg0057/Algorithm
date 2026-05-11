#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

// 在堆上产生了一个的树头空间，返回这个堆空间首地址
BinaryTree* createBinaryTree() {
	BinaryTree* tree = malloc(sizeof(BinaryTree));
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->count = 0;
	return tree;
}

static void destroyTreeNode(BinaryTree *tree, TreeNode *node) {
	if (node) {
		destroyTreeNode(tree, node->left);
		destroyTreeNode(tree, node->right);
		free(node);
		tree->count--;
	}
}

void releaseBinaryTree(BinaryTree *tree) {
	if (tree) {
		destroyTreeNode(tree, tree->root);
		printf("tree lost %d node!\n", tree->count);
		free(tree);
	}


}

// 在空树中初始化根节点
void initBinaryTree(BinaryTree* tree, TreeNode *root) {
	if (tree && tree->root == NULL) {
		tree->root = root;
		tree->count = 1; // 假设初始化时只有根节点
	}
}

TreeNode* createTreeNode(element_t data) {
	TreeNode* node = malloc(sizeof(TreeNode));
	if (node == NULL) {
		return NULL;
	}
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// 将已经存在的离散树节点，建立关系
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
	if (parent == NULL || tree == NULL) {
		return;
	}
	parent->left = left;
	parent->right = right;
	if (left != NULL) {
		tree->count++;
	}
	if (right != NULL) {
		tree->count++;
	}
}

// 用显示树节点里的数据情况，作为处理/访问节点的逻辑
void visitTreeNode(const TreeNode *node) {
	if (node != NULL) {
		printf("\t%c", node->data);
	}
}

/* 由于激活了一个根节点，有左、右两种新任务出现，处理者一次只能处理一个
 * 生产者太快了，消费者太慢了，中间增加一个缓存区（队列）
 * 缓存区 其他接口 是不需要，推荐缓存区放置在栈上（顺序队列）
 */
#define MAX_QUEUE_SIZE	8
void levelOrderBTree(const BinaryTree *tree) {
	TreeNode *queue[MAX_QUEUE_SIZE];
	int front = 0, rear = 0;

	// 1. 任务初始化
	queue[rear] = tree->root;
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	// 2. 循环处理任务，直到任务处理完成（缓存区没有任务了）
	while (rear != front) {
		// 2.1 从缓存区里取出一个任务
		TreeNode *node = queue[front];
		front = (front + 1) % MAX_QUEUE_SIZE;
		// 2.2 访问/处理这个任务
		visitTreeNode(node);
		// 2.3 新的任务送入到缓存区
		if (node->left) {
			queue[rear] = node->left;
			rear = (rear + 1) % MAX_QUEUE_SIZE;
		}
		if (node->right) {
			queue[rear] = node->right;
			rear = (rear + 1) % MAX_QUEUE_SIZE;
		}
	}
	printf("\n");
}

static void preOrderNode(const TreeNode *node) {
	if (node) {
		visitTreeNode(node);
		preOrderNode(node->left);
		preOrderNode(node->right);
	}
}

void preOrderBTree(const BinaryTree *tree) {
	if (tree != NULL) {
		preOrderNode(tree->root);
	}
	printf("\n");
}

static void inOrderNode(const TreeNode *node) {
	if (node) {
		inOrderNode(node->left);
		visitTreeNode(node);
		inOrderNode(node->right);
	}
}

void inOrderBTree(const BinaryTree *tree) {
	if (tree != NULL) {
		inOrderNode(tree->root);
	}
	printf("\n");
}

static void postOrderNode(const TreeNode *node) {
	if (node) {
		postOrderNode(node->left);
		postOrderNode(node->right);
		visitTreeNode(node);
	}
}

void postOrderBTree(const BinaryTree *tree) {
	if (tree != NULL) {
		postOrderNode(tree->root);
	}
	printf("\n");
}

/* 非递归的先序遍历，基本思想：
 * 引入一个栈做任务结构，一旦处理一个任务时候，先把他右任务压入栈，然后再压入左任务
 * 弹栈弹出的就是新的任务，每一个新任务，都重复上面的步骤
 */
#define MAX_STACK_SIZE	8
void preOrderBTreeV2(const BinaryTree *tree) {
	TreeNode *stack[MAX_STACK_SIZE];
	int top = -1;		// 空递增栈

	// 1. 初始化
	stack[++top] = tree->root;
	// 2. 循环处理，直到任务没有
	while (top != -1) {
		TreeNode *node = stack[top--];
		visitTreeNode(node);
		if (node->right) {			// 有右先压右
			stack[++top] = node->right;
		}
		if (node->left) {			// 有左后压左
			stack[++top] = node->left;
		}
	}
}

/* 非递归的中序遍历，以根节点开始，整条左边进栈
 * 从栈中弹出节点，开始访问，然后以这个节点的右孩子为新节点
 * 再次按照整条左边进栈，再弹栈
 */
void inOrderBTreeV2(const BinaryTree *tree) {
	TreeNode *stack[MAX_STACK_SIZE];
	int top = -1;		// 空递增栈

	TreeNode *current = tree->root;		// 新节点
	while (current != NULL || top != -1) {
		while (current != NULL) {	// 新节点的整条左边入栈，新节点先入栈，才能处理新节点
			stack[++top] = current;
			current = current->left;
		}
		current = stack[top--];		// 弹栈
		visitTreeNode(current);		// 没有左边，最后入栈的任务，就是中序的结果
		current = current->right;	// 以右孩子为新节点
	}
}

/* 非递归的后序遍历，需要两个栈，第一个栈辅助栈，第二个栈最后输出的结果
 * 1. 第一个阶段：
 * 1.1 第一个栈初始化头节点后，弹出放入第二个栈，这样根节点就最后出了
 * 1.2 后序遍历的倒数第二个应该是头结点的右孩子，所以辅助栈<先左后右>压入
 * 1.3 处理从第一个栈里出来的元素时，先压入第二个栈，根据这个任务，先左后右压入第一个栈
 * 1.4 直到第一个栈里没有任务，说明树的节点都处理完成
 * 2. 第二个阶段：
 * 2.1 按照第二个栈，出栈
 */
void postOrderBTreeV2(const BinaryTree *tree) {
	TreeNode *stack1[MAX_STACK_SIZE + 10];
	TreeNode *stack2[MAX_STACK_SIZE + 10];
	int top1 = -1;
	int top2 = -1;

	stack1[++top1] = tree->root;
	while (top1 != -1) {
		TreeNode *node = stack1[top1--];		// 栈1弹栈
		stack2[++top2] = node;					// 压入栈2
		if (node->left) {						// 先左后右压入栈1
			stack1[++top1] = node->left;
		}
		if (node->right) {
			stack1[++top1] = node->right;
		}
	}
	while (top2 != -1) {
		TreeNode *node = stack2[top2--];
		visitTreeNode(node);
	}
}
