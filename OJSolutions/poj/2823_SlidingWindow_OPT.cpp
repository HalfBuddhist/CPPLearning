#include <iostream>
#include <queue>
#include <stdio.h>

#define _DEBUG

using namespace std;

int nums[1000005];
int ans_min[1000005];
int ans_max[1000005];
int min_queue[1000005];
int max_queue[1000005];


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
    int max_f = 0, max_e = 0, min_f = 0, min_e = 0;
    int idx_min = 0, idx_max = 0;

    for (int i = 0; i < n; i++) {
        //min queue
        if (min_f < min_e && (i - min_queue[min_f]) >= k)
            min_f++;
        while (min_f < min_e && nums[min_queue[min_e - 1]] >= nums[i])
            min_e--;
        min_queue[min_e++] = i;

        //max queue
        if (max_f < max_e && (i - max_queue[max_f]) >= k)
            max_f++;
        while (max_f < max_e && nums[max_queue[max_e - 1]] <= nums[i])
            max_e--;
        max_queue[max_e++] = i;

        if (i >= k - 1) {
            ans_max[idx_max++] = nums[max_queue[max_f]];
            ans_min[idx_min++] = nums[min_queue[min_f]];
        }
    }

    //out
    for (int i = 0; i < idx_min; i++) {
        printf("%d ", ans_min[i]);
    }
    printf("\n");
    for (int i = 0; i < idx_max; i++) {
        printf("%d ", ans_max[i]);
    }
    printf("\n");

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}