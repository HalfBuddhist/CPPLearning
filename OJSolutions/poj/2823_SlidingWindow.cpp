#include <iostream>
#include <queue>
#include <stdio.h>

#define _DEBUG

using namespace std;

int nums[1000005];


/**
 * c++标准可以提交,而G++则不可
 * 怀疑是因为G++的强大功能而引起的
 */
int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    //resovle
    vector<int> ans_min;
    vector<int> ans_max;

    deque<int> min_queue;
    deque<int> max_quque;

    for (int i = 0; i < n; i++) {
        // min queue
        if (!min_queue.empty() && (i - min_queue.front()) >= k)
            min_queue.pop_front();
        while (!min_queue.empty() && nums[min_queue.back()] >= nums[i])
            min_queue.pop_back();
        min_queue.push_back(i);

        //max queue
        if (!max_quque.empty() && (i - max_quque.front()) >= k)
            max_quque.pop_front();
        while (!max_quque.empty() && nums[max_quque.back()] <= nums[i])
            max_quque.pop_back();

        max_quque.push_back(i);

        if (i >= k - 1) {
            ans_max.push_back(nums[max_quque.front()]);
            ans_min.push_back(nums[min_queue.front()]);
        }
    }

    //output
    for (int i = 0; i < ans_min.size() - 1; i++) {
        printf("%d ", ans_min[i]);
    }
    if (ans_min.size() >= 1) printf("%d\n", ans_min[ans_min.size() - 1]);
    for (int i = 0; i < ans_max.size() - 1; i++) {
        printf("%d ", ans_max[i]);
    }
    if (ans_max.size() >= 1) printf("%d\n", ans_max[ans_max.size() - 1]);

#ifdef _DEBUG
//    cerr << "**********************" << endl;
//    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}