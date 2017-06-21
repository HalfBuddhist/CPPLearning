/**
 * 主题：批处理作业调度算法
 */
#include <iostream>
#include <vector>

using namespace std;

class flowshop {

public:

    /**
     * initialize the class with a task-cost 2-dimensional table.
     */
    flowshop(vector<vector<int> > &rhs) {
        task_count = rhs.size();
        each_t = rhs;
        best_t.resize(task_count);
        machine2_t.resize(task_count, 0);
        machine1_t = 0;
        cur_total_t = 0;
        best_total_t = 0;

        current_t.resize(task_count, 0);
        for (int i = 0; i < task_count; ++i) {
            current_t[i] = i; // 为了实现全排列
        }
    }


    /**
     * find the best solution use backtracking, and print the best solution out.
     */
    void backtrack() {
        __backtrack(0);
        // 显示最佳调度方案和最优完成时间和
        cout << "the best flowshop scheme is : ";
        copy(best_t.begin(), best_t.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        cout << "the best total time is : " << best_total_t << endl;
    }


private:
    /**
     * Backtracking on the whole permutaions started from the location i
     * to find the best solution.
     * when i is larger than n, then we got a new permuation,  that is a solution also.
     *
     * there two key point of the this backtracking algo.
     * 1, the permuations generation algo, this is completed by swap the current ele with the later element  consecutively
     * and merge this locatoin with the whole permuations of the later elemnent. Buth the complexity is also the n*n!.
     * if youd don't remember this youd could also use the other permutations algos depicted in the permuations class of Java.
     * But the prunning process will be not so intuitionistic as this mehtod.
     *
     * 2, the prunning process, prunne the branches in which the current_cost is larager than the best cost have got.
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
    void __backtrack(int i) {
        if (i >= task_count) { // has get an candidate solution.
            if (cur_total_t < best_total_t || best_total_t == 0) {
                // 存储当前最优调度方式
                copy(current_t.begin(), current_t.end(), best_t.begin());
                best_total_t = cur_total_t;
            }
            return;
        }

        for (int j = i; j < task_count; ++j) {
            // 机器1上结束的时间
            machine1_t += each_t[current_t[j]][0];
            // 机器2上结束的时间
            if (i == 0) {
                machine2_t[i] = machine1_t + each_t[current_t[j]][1];
            } else {
                machine2_t[i] = ((machine2_t[i - 1] > machine1_t) ? machine2_t[i - 1] : machine1_t)
                                + each_t[current_t[j]][1];
            }

            cur_total_t += machine2_t[i];
            // 剪枝
            if (cur_total_t < best_total_t || best_total_t == 0) {
                // 全排列
                swap(current_t[i], current_t[j]);
                __backtrack(i + 1);
                swap(current_t[i], current_t[j]);
            }

            machine1_t -= each_t[current_t[j]][0];
            cur_total_t -= machine2_t[i];
        }
    }


public :
    int task_count;        // 作业数
    vector<vector<int> > each_t;    // 各作业所需的处理时间

    vector<int> machine2_t;    // 机器2完成处理的时间
    int machine1_t;        // 机器1完成处理的时间

    vector<int> current_t;    // 当前作业调度
    vector<int> best_t;        // 当前最优时间调度

    int cur_total_t;            // 当前完成时间和
    int best_total_t;        // 最优完成时间和
};

int main() {
    const int task_count = 3;//4
    vector<vector<int>> each_t(task_count);
    for (int i = 0; i < task_count; ++i) {
        each_t[i].resize(2);
    }
    each_t[0][0] = 2;
    each_t[0][1] = 1;
    each_t[1][0] = 3;
    each_t[1][1] = 1;
    each_t[2][0] = 2;
    each_t[2][1] = 3;
    // each_t[3][0] = 1 ;
    // each_t[3][1] = 1 ;

    flowshop fs(each_t);
    fs.backtrack();
}