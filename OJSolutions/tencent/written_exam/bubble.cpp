//
// Created by Qingwei on 2017/6/2.
//

#include <iostream>
#include <vector>

#define _DEBUG

using namespace std;

/**
 * 用C语言实现一个冒泡排序函数，要求支持泛型。
 */
template<typename T>
void SortPP(vector<T> &list) {
    for (int i = 0; i < list.size(); ++i) {
        for (int j = list.size() - 2; j >= i; j--) {
            if (list[j + 1] < list[j]) {
                int t = list[j + 1];
                list[j + 1] = list[j];
                list[j] = t;
            }
        }
    }
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(2);
    a.push_back(5);
    a.push_back(4);
    SortPP(a);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, ", "));

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}