#include <iostream>
#include <vector>

#define _DEBUG
using namespace std;

/**
 * // O(n) 解决 LCA
 * 如果有树的索引（可用数组实现）,且加上父母指针, 复杂度可降到O(logn)
 *
 */

//二叉树节点
struct Node {
    int key;
    struct Node *left, *right;
};

//公用函数，生成一个节点
Node *newNode(int k) {
    Node *temp = new Node;
    temp->key = k;
    temp->left = temp->right = NULL;
    return temp;
}

//找到从root到 节点值为key的路径,存储在path中。没有的话返回-1
bool findpath(Node *root, vector<int> &path, int key) {
    if (root == NULL) return false;
    path.push_back(root->key);
    if (root->key == key) return true;
    //左子树或右子树 是否找到,找到的话当前节点就在路径中了
    bool find = (findpath(root->left, path, key) || findpath(root->right, path, key));
    if (find) return true;
    //该节点下未找到就弹出
    path.pop_back();
    return false;
}

int findLCA(Node *root, int key1, int key2) {
    vector<int> path1, path2;
    bool find1 = findpath(root, path1, key1);
    bool find2 = findpath(root, path2, key2);
    if (find1 && find2) {
        int ans;
        for (int i = 0; i < path1.size(); i++) {
            if (path1[i] != path2[i]) {
                break;
            } else
                ans = path1[i];
        }
        return ans;
    }
    return -1;
}

// Driver program to test above functions

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/in.txt", "r", stdin);
#endif

    // 按照上面的图来创创建树
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    cout << "LCA(4, 5) = " << findLCA(root, 4, 5);
    cout << "\nLCA(4, 6) = " << findLCA(root, 4, 6);
    cout << "\nLCA(3, 4) = " << findLCA(root, 3, 4);
    cout << "\nLCA(2, 4) = " << findLCA(root, 2, 4);

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}

