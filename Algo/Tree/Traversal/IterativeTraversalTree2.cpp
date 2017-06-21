#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

/* 二叉树节点 */
struct node;
typedef struct node TNode;
struct node {
    int data;
    TNode *left;
    TNode *right;
    int flag;
};

//constructors
TNode *newNode(int data) {
    TNode *node = new TNode;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->flag = 0;
    return node;
}

void Visit(TNode *node) {
    cout << node->data << endl;
}


/**
 * 非递归的方式后序遍历二叉树
 */
// 后序遍历伪代码：非递归版本，用栈实现, 其中flag表示回溯的次数, 当回溯两次时访问,一次从左子树,一次从右子树,
void iterativePostorder(TNode *root) {
    stack<TNode *> s;
    while (root != NULL || !s.empty()) {
        if (root != NULL) {
            s.push(root);
            root = root->left;
        } else {
            TNode *p = s.top(); //should visit right
            p->flag++;
            if (2 == p->flag) {//backtrack from the right
                Visit(p);
                s.pop();
            } else {
                root = p->right;
            }
        }
    }
}

//测试
int main() {
    /*  创建以下的树
            10
          /   \
        8      2
      /  \    /
    3     5  1
  */
    TNode *root = newNode(10);
    root->left = newNode(8);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(5);
    root->right->left = newNode(1);
    iterativePostorder(root);
    return 0;
}