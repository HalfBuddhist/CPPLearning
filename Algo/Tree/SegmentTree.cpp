/*---------------------------------------------
*   日期：2015-02-25
*   作者：SJF0115
*   题目: 23.线段树
*   来源：算法系列
-----------------------------------------------*/
#include <iostream>

using namespace std;

#define MAX 10

// 线段树节点
struct IntervalTreeNode {
    int left, right, mid;
    // 表示是否被覆盖
    bool cover;
};

// 由线段树的性质可知，建树所需要的空间大概是所需处理
// 最长线段长度的2倍多，所以需要开3倍大小的数组
IntervalTreeNode intervalTree[3 * MAX];

// 创建线段树
// left,right分别为当前节点的左右端点，num为节点在数组中的编号
void Create(int left, int right, int num) {
    intervalTree[num].left = left;
    intervalTree[num].right = right;
    intervalTree[num].mid = (left + right) / 2;
    intervalTree[num].cover = false;
    // 若不为叶子节点，则递归的建立左右子树
    if (left + 1 != right) {
        Create(left, intervalTree[num].mid, 2 * num);
        Create(intervalTree[num].mid, right, 2 * num + 1);
    }//if
}

// 插入
void Insert(int left, int right, int num) {
    // 若插入的线段完全覆盖当前节点所表示的线段
    if (intervalTree[num].left == left && intervalTree[num].right == right) {
        intervalTree[num].cover = 1;
        return;
    }//if
    // 当前节点的左子节点所代表的线段包含插入的线段
    if (right <= intervalTree[num].mid) {
        Insert(left, right, 2 * num);
    }//if
        // 当前节点的右子节点所代表的线段包含插入的线段
    else if (left >= intervalTree[num].mid) {
        Insert(left, right, 2 * num + 1);
    }//if
        // 插入的线段跨越了当前节点所代表线段的中点
    else {
        Insert(left, intervalTree[num].mid, 2 * num);
        Insert(intervalTree[num].mid, right, 2 * num + 1);
    }//else
}

// 删除
bool Delete(int left, int right, int num) {
    // 删除到叶节点的情况
    if (intervalTree[num].left + 1 == intervalTree[num].right) {
        int cover = intervalTree[num].cover;
        intervalTree[num].cover = 0;
        return cover;
    }//if
    // 当前节点不为叶节点且被覆盖
    if (intervalTree[num].cover == 1) {
        intervalTree[num].cover = 0;
        intervalTree[2 * num].cover = 1;
        intervalTree[2 * num + 1].cover = 1;
    }//if
    // 左子节点
    if (right <= intervalTree[num].mid) {
        return Delete(left, right, 2 * num);
    }//if
        // 右子节点
    else if (left >= intervalTree[num].mid) {
        return Delete(left, right, 2 * num + 1);
    }//else
        // 跨越左右子节点
    else {
        return Delete(left, intervalTree[num].mid, 2 * num) &&
               Delete(intervalTree[num].mid, right, 2 * num + 1);
    }//else
}

// 覆盖长度
int CoverLen(int num) {
    IntervalTreeNode node = intervalTree[num];
    // 如果当前节点所代表的线段已被覆盖，
    // 则将统计长度加上当前线段长度。
    if (node.cover) {
        return node.right - node.left;
    }//if
    // 当遍历到叶节点时返回
    if (node.left + 1 == node.right) {
        return 0;
    }//if
    // 递归进入当前节点的左右子节点进行计算
    return CoverLen(2 * num) + CoverLen(2 * num + 1);
}

int main() {
    int x[] = {1, 2, 5};
    int y[] = {3, 4, 6};

    // 创建[1,10]区间的线段树
    Create(1, 10, 1);

    // 插入
    for (int i = 0; i < 3; ++i) {
        Insert(x[i], y[i], 1);
    }//for

    // 删除
    Delete(2, 3, 1);

    /*for(int i = 1;i < 3*MAX;++i){
        cout<<"["<<intervalTree[i].left<<","<<intervalTree[i].right<<"]"<<"->"<<intervalTree[i].cover<<endl;
    }//for*/

    // 覆盖长度
    int len = CoverLen(1);
    cout << len << endl;
    return 0;
}
