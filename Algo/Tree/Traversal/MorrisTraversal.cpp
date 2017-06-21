#include<stdio.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

struct node {
    int data;
    struct node *left;
    struct node *right;
};

/**
 * 叶子节点的空指针来记录当前节点的位置，然后一旦遍历到了叶子节点，发现叶子节点的右指针指向的是当前节点，
 * 那么就认为以当前节点的左子树已经遍历完成。Morris 遍历正是利用了线索二叉树 的思想。
 */


/**
 * 以inorder为例，初始化当前节点为root，它的遍历规则如下：
    如果当前节点为空，程序退出。
    如果当前节点非空，
    如果当前节点的左儿子为空，那么输出当前节点，当前节点重置为当前节点的右儿子。
    如果当前节点的左儿子非空，找到当前节点左子树的最右叶子节点
    （此时最右节点的右儿子有两种情况，一种是指向当前节点，一种是为空,你也许感到奇怪，右节点的右儿子怎么可能非空，
    注意，这里的最右叶子节点只带的是原树中的最右叶子节点。），
    若其最右叶子节点为空，令其指向当前节点，将当前节点重置为其左儿子，若其最右节点指向当前节点，输出当前节点，
    将当前节点重置为当前节点的右儿子,并恢复树结构，即将最右节点的右节点再次设置为NULL
 */
void bst_morris_in_order(struct node *root) {
    struct node *current = root, *pre;

    while (current) {
        if (current->left == NULL) {
            printf(" %d ", current->data);
            current = current->right;
        } else {
            /* 找到current的前驱节点 */
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            /* 将current节点作为其前驱节点的右孩子 */
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {/* 恢复树的原有结构，更改right 指针 */
                pre->right = NULL;
                printf(" %d ", current->data);
                current = current->right;
            }
        }
    }
}

void bst_morris_pre_order(struct node *root) {
    struct node *current = root, *pre;

    while (current) {
        if (current->left == NULL) {
            printf("%d ", current->data);
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            if (pre->right == NULL) {
                printf("%d ", current->data);
                pre->right = current;
                current = current->left;
            } else {
                pre->right = NULL;
                current = current->right;
            }
        }
    }
}

/**
 * 翻转父母与右孩子的关系
 */
void reverse_right_parent(struct node *from_parent, struct node *to_right) {
    struct node *down = from_parent->right, *pre = from_parent, *temp;
    for (; ;) {
        if (down == to_right) {
            down->right = pre;
            break;
        }
        temp = down->right;
        down->right = pre;
        pre = down;
        down = temp;
    }
}

/**
 * 逆序输出
 */
void bst_morris_reverse(struct node *node_c_left, struct node *last) {
    struct node *p = node_c_left, *x, *y;
    if (p == last) {
        printf("%d ", last->data);
        return;
    }

    /* change right to parent pointer */
    reverse_right_parent(node_c_left, last);

    /* visit each */
    x = last;
    for (; ;) {
        printf("%d ", x->data);
        if (x == node_c_left)
            break;
        x = x->right;
    }

    /* revert right pointer */
    reverse_right_parent(last, node_c_left);
}


void bst_morris_post_order(struct node *root) {
    struct node dummy;
    struct node *current, *pre;

    //为了解决根结点无法输出的问题, 因为每一个结点的输出都要靠上层结点的与其左子树的最右子结点的连接来实现.
    //这样根结点就有了上层结点, 就可以因输出了.
    dummy.left = root;
    dummy.right = NULL;
    current = &dummy;

    while (current) {
        if (current->left == NULL) {
            current = current->right;
        } else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
            else {
                bst_morris_reverse(current->left, pre);
                pre->right = NULL;
                current = current->right;
            }
        }
    }
}


struct node *newNode(int data) {
    struct node *tNode = (struct node *) malloc(sizeof(struct node));
    tNode->data = data;
    tNode->left = NULL;
    tNode->right = NULL;
    return (tNode);
}

/* 测试*/
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
    bst_morris_post_order(root);
    return 0;
}