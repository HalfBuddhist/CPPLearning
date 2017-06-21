//
// Created by Qingwei on 2017/5/28.
// 旅行售货员问题, backtracking and prunning.
// use the template of the permutation tree.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class traveling {

public:
    static const int NOEDGE = -1; // indicate not connected.
private:
    //base varible.
    int node_count;        // 结点个数
    vector<vector<int> > undigraph; // 无向图(采用矩阵存储)

    int curr_cost;        // 当前费用
    vector<int> curr_solution;    // 当前解决方案

    int best_cost;        // 最优值
    vector<int> best_solution;    // 最优解决方案

public:
    //constructor
    traveling(const vector<vector<int> > &ug) : curr_cost(0), best_cost(-1) {
        node_count = ug.size();
        undigraph = ug;
        curr_solution.resize(node_count);
        for (int i = 0; i < node_count; ++i) {
            curr_solution[i] = i; // initial permutation.
        }
        best_solution.resize(node_count);
    }

    /**
     * backtracking to find the best saling route.
     * and print the best route.
     */
    void backtrack() {
        __backtrack(1);
        copy(best_solution.begin(), best_solution.end(), ostream_iterator<int>(cout, "->"));
        cout << endl << best_cost << endl;
    }

private:
    /**
     * Backtracking on the whole permutaions started from the location (layers)
     * to find the best route.
     * when (layers) is larger than n, then we got a new permuation,  that is a solution also.
     *
     * there two key point of the this backtracking algo.
     * 1, the permuations generation algo, this is completed by swap the current ele with the later element  consecutively
     * and merge this locatoin with the whole permuations of the later elemnent. Buth the complexity is also the n*n!.
     * if youd don't remember this youd could also use the other permutations algos depicted in the permuations class of Java.
     * But the prunning process will be not so intuitionistic as this mehtod.
     *
     * 2, the prunning process, prunne the branches in which the current_cost is larager than the best cost we have got.
     * this prunnning is very obvious.
     *
     * O(n! * n * n)
     *
     * the n! is the time complexity of the permutations.
     * the first n is the time complexity of the backtracking operation it self.
     * the second n is the time complexity of the update the best solution.
     *
     * @param i, location start of the whole permutation.
     */
    void __backtrack(int layers) {
        if (layers >= node_count) {//got a scheme.
            if (undigraph[curr_solution[node_count - 1]][curr_solution[0]] == NOEDGE) {
                return;
            }
            //add the last city to the original city's distance.
            int total_cost = curr_cost + undigraph[curr_solution[node_count - 1]][curr_solution[0]];
            if (total_cost < best_cost || best_cost == -1) {
                // 更新最优费用和最优路径
                best_cost = total_cost;
                copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
            }
            return;
        }

        //generate permutatins and prunning.
        for (int i = layers; i < node_count; ++i) {
            // 剪枝
            if (undigraph[curr_solution[layers - 1]][curr_solution[i]] != NOEDGE &&
                (best_cost == -1 ||
                 curr_cost + undigraph[curr_solution[layers - 1]][curr_solution[i]] < best_cost)) {
                // 搜索子树
                swap(curr_solution[layers], curr_solution[i]);
                curr_cost += undigraph[curr_solution[layers - 1]][curr_solution[layers]];
                __backtrack(layers + 1);
                curr_cost -= undigraph[curr_solution[layers - 1]][curr_solution[layers]];
                swap(curr_solution[layers], curr_solution[i]);
            }
        }
    }
};

int main() {
    int size = 4; // city cnt.
    vector<vector<int> > ug(size); // an undirected graph depicted in adjacent matrix.
    for (int i = 0; i < size; ++i) {
        ug[i].resize(size);
    }

    ug[0][0] = -1;
    ug[0][1] = 30;
    ug[0][2] = 6;
    ug[0][3] = 4;

    ug[1][0] = 30;
    ug[1][1] = -1;
    ug[1][2] = 5;
    ug[1][3] = 10;

    ug[2][0] = 6;
    ug[2][1] = 5;
    ug[2][2] = -1;
    ug[2][3] = 20;

    ug[3][0] = 4;
    ug[3][1] = 10;
    ug[3][2] = 20;
    ug[3][3] = -1;

    traveling t(ug);
    t.backtrack();

    return 0;
}
