#include <cstring>
#include <iostream>

#define SIZE 1000001
using namespace std;

/**
 * 介于0到1000000之间的n个整数，请对他们进行排序，要求时间复杂度为O(n)，写c代码实现
 * brute force, defination.
 * 使用数组进行散列，注意重复元素即可。
 * O(n)
 * AC
 */
void rangeSort(int *array, int len) {
    int data[SIZE];
    int i = 0;
    int j = 0;

    memset(data, -1, SIZE * sizeof(int));

    for (i = 0; i < len; ++i) {
        data[array[i]]++;
    }

    i = 0;
    for (j = 0; j < SIZE;) {
        if (data[j] != -1) {
            array[i++] = j;
            data[j]--;
        } else {
            j++;
        }
    }
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

    int a[] = {2, 3, 2, 4, 0, 1, 0};
    rangeSort(a, 7);
    for (int i = 0; i < 7; i++) {
        cout << a[i] << endl;
    }

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}