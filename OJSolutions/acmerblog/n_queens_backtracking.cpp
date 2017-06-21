//
// Created by Qingwei on 2017/5/28.
// 主题：n后问题, backtracking classic.
//
#include <iostream>
#include <vector>

using namespace std;

class queen {
    // 皇后在棋盘上的位置
    struct Coordinates {
        int x;
        int y;

        Coordinates() : x(0), y(0) { }
    };

private:
    vector<Coordinates> curr_solution;  // 当前解决方案
    const int q_count;                  // 皇后个数
    int sum_solution;                   // 当前找到的解决方案的个数

public:
    //constructor
    queen(int qc) : q_count(qc), sum_solution(0) {
        curr_solution.resize(q_count);
    }

    /**
     * backtracking to find all the solutions count.
     * n^(n)
     */
    void backtrack() {
        __backtrack(0);
    }

private:
    /**
     * backtracking from the t'th queen.
     *
     * set the current row's queen to the possibel n locations iteratively, and backtracking from the t'th queen.
     * before backtracking, check the legality of the current location.
     * when t = n, then we've got a solution.
     *
     * n^(n), the number of the leaves of the n-branch tree, each node represents a candidates solution without legality check.
     */
    void __backtrack(int t) {
        if (t >= q_count) {  // 找到一个解决方案
            ++sum_solution;
            for (size_t i = 0; i < curr_solution.size(); ++i) {
                cout << "x = " << curr_solution[i].x
                << " y = " << curr_solution[i].y << endl;
            }
            cout << "sum_solution = " << sum_solution << endl;
        } else {
            for (int i = 0; i < q_count; ++i) {
                curr_solution[t].x = i;
                curr_solution[t].y = t;
                if (__place(t)) {
                    __backtrack(t + 1);
                }
            }
        }
    }

    // 判断第k个皇后的位置是否与前面的皇后相冲突
    bool __place(int k) {
        for (int i = 0; i < k; ++i) {
            if ((abs(curr_solution[i].x - curr_solution[k].x) == abs(curr_solution[i].y - curr_solution[k].y))
                || curr_solution[i].x == curr_solution[k].x) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    queen q(5);
    q.backtrack();
    return 0;
}