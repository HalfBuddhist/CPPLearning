//
// Created by Qingwei on 2017/5/26.
// 主题：装载问题
// 子集树的解法: 回溯用递归实现.
//
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

/**
 * 装载问题子函数
 * layers: 搜索到第layers层结点
 * layers_size: layers_size总层数
 * current_w: 当前承载量
 * best_w: 最优载重量
 * flag_x: 选取方案
 * best_x: 最佳选取方案
 * remainder_w:剩余重量
 * container_w:每个集装箱的重量
 * total_w: 总承载量
 */
void __backtrack(int layers, const int layers_size, int current_w, int &best_w, vector<int> &flag_x,
                 vector<int> &best_x, int remainder_w, const vector<int> &container_w, int total_w) {
    //exit condition
    if (layers > layers_size - 1) {
        // 到达叶子结点，更新最优载重量
        if (current_w < best_w || best_w == -1) {
            copy(flag_x.begin(), flag_x.end(), best_x.begin());
            // copy(best_x.begin(),best_x.end(), flag_x.begin());
            best_w = current_w;
        }
        return;
    }

    if (current_w + container_w[layers] <= total_w) {
        // 搜索左子树, including the container.
        flag_x[layers] = 1;
        __backtrack(layers + 1, layers_size, current_w + container_w[layers], best_w, flag_x, best_x,
                    remainder_w - container_w[layers], container_w, total_w);
    }


    if (current_w + remainder_w > best_w || best_w == -1) {
        // search the right branch of the current node.
        flag_x[layers] = 0;
        __backtrack(layers + 1, layers_size, current_w, best_w, flag_x, best_x, remainder_w, container_w, total_w);
    }

}

/**
 * 装载问题
 * container_w: 各个集装箱重量
 * total_w: 总承载量
 */
void loading_backtrack(int total_w, vector<int> &container_w) {
    int layers_size = container_w.size();   // 层数
    int current_w = 0;          // 当前装载重量
    int remainder_w = total_w;  // 剩余重量
    int best_w = -1;             // 最优载重量
    vector<int> flag_x(layers_size);    // 是否被选取标志
    vector<int> best_x(layers_size);    // 最佳选取方案

    //resolve
    __backtrack(0, layers_size, current_w, best_w, flag_x, best_x, remainder_w, container_w, total_w);

    // output
    cout << "path : ";
    copy(best_x.begin(), best_x.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "best_w = " << best_w << "( ";
    // 将结果输出
    for (size_t i = 0; i < best_x.size(); ++i) {
        if (best_x[i] == 1) {
            cout << container_w[i] << " ";
        }
    }
    cout << ")" << endl;
}

int main() {
    const int total_w = 30;
    vector<int> container_w; //containers.
    container_w.push_back(40);
    container_w.push_back(1);
    container_w.push_back(40);
    container_w.push_back(9);
    container_w.push_back(1);
    container_w.push_back(8);
    container_w.push_back(5);
    container_w.push_back(50);
    container_w.push_back(6);

    loading_backtrack(total_w, container_w);
    return 0;
}
