#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

/* 二叉树节点 */
struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *newNode(int data) {
    struct node *node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

/**
 * 非递归的方式先序遍历二叉树
 * 先访问跟节点，然后访问左节点，再访问右节点。如果不用递归，那该怎么做呢？
 * 仔细看一下递归程序，就会发现，其实每次都是走树的左分支(left)，直到左子树为空，
 * 然后开始从递归的最深处返回，然后开始恢复递归现场，访问右子树。
 * 其实过程很简单：一直往左走 root->left->left->left…->null，由于是先序遍历，因此一遇到节点，便需要立即访问；
 * 由于一直走到最左边后，需要逐步返回到父节点访问右节点，因此必须有一个措施能够对节点序列回溯。
 * 有两个办法：
 * 1.用栈记忆：在访问途中将依次遇到的节点保存下来。由于节点出现次序与恢复次序是反序的，因此是一个先进后出结构，需要用栈。
 * 2.节点增加指向父节点的指针：通过指向父节点的指针来回溯
 */

/**
 * 方法一，直接用栈模拟递归。次将节点压入栈，然后弹出，压右子树，再压入左子树，在遍历过程中，
 * 遍历序列的右节点依次被存入栈，左节点逐次被访问。同一时刻，栈中元素为m-1个右节点和1个最左节点，最高为h。
 * 所以空间也为O(h)；
 * 每个节点同样被压栈一次，弹栈一次，访问一次，时间复杂度O(n)
 */
void iterativePreorder(node *root) {
    if (root == NULL)
        return;

    // 根节点入栈
    stack<node *> nodeStack;
    nodeStack.push(root);

    while (nodeStack.empty() == false) {
        // 访问根节点
        struct node *node = nodeStack.top();
        printf("%d ", node->data);
        nodeStack.pop();

        // 不为空的话则入栈
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
}


/**
 * 方法二
 * 同样是使用栈，每次都将遇到的节点压入栈，当左子树遍历完毕后才从栈中弹出最后一个访问的节点，
 * 访问其右子树。在同一层中，不可能同时有两个节点压入栈，因此栈的大小空间为O(h)，h为二叉树高度。
 * 时间方面，每个节点都被压入栈一次，弹出栈一次，访问一次，复杂度为O(n)
 *
 * 不使用栈的方法（未代码实现）, 使用指向父亲的指针
 * 一直访问左子树,形成一个循环, 为空; 利用父亲的指针回溯访问右子树; 右子树访问利用父亲指针回溯到第一个是左子树的祖先处,
 * 并访问其兄弟结点（即父亲的右子树）.
 */
void iterativePreorder2(node *root) {
    stack<node *> s;
    while ((root != NULL) || !s.empty()) {
        if (root != NULL) {
            printf("%d ", root->data);
            s.push(root);       // 先序就体现在这里了，先访问，再入栈
            root = root->left;  // 依次访问左子树
        } else {
            root = s.top();     // 回溯至父亲节点. 此时根节点和左子树都已访问过
            s.pop();
            root = root->right;
        }
    }
}


/**
 * 非递归的方式中序遍历二叉树
 */
/**
 * 根据前面的先序遍历，可以类似的构造出中序遍历的两种方式。
 * 仔细想一下，只有第二种方法 iterativePreorder2 改过来时最方便的。
 * 需要的改动仅仅调换一下节点访问的次序，先序是先访问，再入栈；而中序则是先入栈，弹栈后再访问。伪代码如下。
 * 时间复杂度与空间复杂度同先序一致。
 */
void iterativeInorder(node *root) {
    stack<node *> s;
    while (root != NULL || !s.empty()) {
        if (root != NULL) {
            s.push(root);
            root = root->left;
        } else {
            root = s.top();
            s.pop();
            cout << root->data << endl;
            root = root->right;
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
    struct node *root = newNode(10);
    root->left = newNode(8);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(5);
    root->right->left = newNode(1);
    iterativePreorder(root);
    return 0;
}