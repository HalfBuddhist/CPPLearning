//
// Created by Qingwei on 2017/5/28.
// 0-1背包问题, backtracking.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class goods {
public:
    int weight; // 重量
    int price;    // 价格
    goods() : weight(0), price(0) { }
};

bool goods_greater(const goods &lhs, const goods &rhs) {
    return (lhs.price / lhs.weight) > (rhs.price / rhs.weight);
}

class knapsack {

private:
    //classic knapsack var
    vector<goods> goods_list;    // 货物信息列表
    int capacity;                // 背包承载量

    //binary tree depth.
    int total_layers;            // 总层数

    //current recorder
    int curr_price;                // 当前价格
    int curr_weight;                 // 当前重量
    vector<int> curr_path;        // 当前路径

    //best recorder.
    int best_price;                // 当前得到的最优价值
    vector<int> best_path;        // 最优价值下的路径


public:
    //constructor
    knapsack(int c, const vector<goods> &gl) : capacity(c), curr_price(0), best_price(0), curr_weight(0) {
        goods_list = gl;
        total_layers = gl.size();
        curr_path.resize(total_layers);
        best_path.resize(total_layers);
    }

    /**
     * backtracking to find the best knapsack solution.
     */
    void backtrack() {
        __backtrack(0);
        cout << "path: ";
        copy(best_path.begin(), best_path.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        cout << "best_price: " << best_price << endl;
    }

private:
    /**
     * 计算上界
     * 如果想要背包问题中的价值最大化, 那么在选择放物品的时候就要兼顾两个方面的内容,
     * 1, 性价比, 即单位重量下我希望价值最大.
     * 2, 空间利用率, 即我希望我的背包尽量少的空间剩余.
     * 理解了这两点后, 下面的上界就容易理解了.
     * O(nlogn)
     */
    int __bound(int layers) {
        int cleft = capacity - curr_weight;
        int result = curr_price;
        // 将layer之后的物品进行按单位价格降序排序
        vector<goods> tmp = goods_list;
        sort(tmp.begin() + layers, tmp.end(), goods_greater);
        // 以物品单位重量价值递减序装入物品
        while (layers < total_layers && tmp[layers].weight <= cleft) {
            cleft -= tmp[layers].weight;
            result += tmp[layers].price;
            ++layers;
        }
        // 装满背包
        if (layers < total_layers) {
            result += (tmp[layers].price / tmp[layers].weight) * cleft;
        }
        return result;
    }

    /**
     * Backtracking from the layers indicated by layers parameters
     *
     * put the current thing into or not into the knapsack and then backtring the others to find the packing solution.
     * when the laysers beyond the tree depth, then we got a feasible scheme, update the best.
     * the bound function takes the best performance-price ratio and the full space use ratio.
     * why boudn the right branch, not the left branch? not reasonalbe, we add it manually.
     *
     * O(n * nlogn * 2^n)
     * 2^n:         the numbers of the leaves of the subset tree, also the possible solutions count.
     * n:           the time complexity of the backtracking operation.
     * nlogn:       the time complexity of the bound function, which happens on every backtracking operation.
     */
    void __backtrack(int layers) {
        // 到达叶子结点，更新最优价值
        if (layers >= total_layers) {
            if (curr_price > best_price || best_price == 0) {
                best_price = curr_price;
                copy(curr_path.begin(), curr_path.end(), best_path.begin());
            }
            return;
        }
        // 左剪枝（能放的下）
        if (curr_weight + goods_list[layers].weight <= capacity) {
            curr_path[layers] = 1;
            curr_weight += goods_list[layers].weight;
            curr_price += goods_list[layers].price;
            // second time left prunning, added by me manually.
            if (best_price == 0 || __bound(layers + 1) > best_price)
                __backtrack(layers + 1);
            curr_weight -= goods_list[layers].weight;
            curr_price -= goods_list[layers].price;
        }
        // 右剪枝
        if (best_price == 0 || __bound(layers + 1) > best_price) {
            curr_path[layers] = 0;
            __backtrack(layers + 1);
        }
    }
};

int main() {
    const int size = 3;
    vector<goods> gl(size);
    gl[0].weight = 10;
    gl[0].price = 1;
    gl[1].weight = 8;
    gl[1].price = 4;
    gl[2].weight = 5;
    gl[2].price = 5;

    knapsack ks(16, gl);
    ks.backtrack();
    return 0;
}
