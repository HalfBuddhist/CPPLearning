//
// Created by Qingwei on 2017/3/13.
//
#include <iostream>
#include <cstdio>

#define _DEBUG

using namespace std;

int arr[100005];
int s_idx, e_idx;

//2 pointers, o(n),
int maxSum2Pointers(const int *arr, int n) {
    int start = 0, end = 0;
    int max_sum = 1 << 31;
    int t_sum = 0;
    while (start < n && end < n) {
        t_sum += arr[end];
        //store info for the max subarray
        if (t_sum > max_sum) {
            s_idx = start;
            e_idx = end;
        }
        max_sum = max(max_sum, t_sum);
        if (t_sum < 0) {
            t_sum = 0;
            start = end + 1;
        }
        end++;
    }
    return max_sum;
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif
    int n = 0;
    while (1) {
        scanf("%d", &n);
        if (n) {
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            int res = maxSum2Pointers(arr, n);
            printf("%d %d %d\n", res, s_idx, e_idx);
        } else
            break;
    }


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}