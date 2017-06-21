//
// Created by Qingwei on 2017/6/2.
//

#include <iostream>

#define _DEBUG

using namespace std;


/**
 * If the first player could win or not.
 * @param m the nubmer of the cards, m>=1
 * @param n the amount of cards to take at most.
 * @return true if the first player could win, false indicate the first player would lose.
 */
bool judge(int m, int n) {
    if (m <= 0 || n <= 0) {
        cout << "No defination under this situation." << endl;
    }
    int predicator = m % (n + 1);
    return predicator != 1;
}


/**
 * 3. 一共有m张牌，两个人轮流拿，每次最少拿1张，最多拿n张，拿到最后一张牌的人算输，假设两个人都足够聪明。
 * 写一段代码，对于输入的任意m和n，判断先拿的人是否能赢。
 */
int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

    bool ans = judge(12, 10);
    if (ans) {
        cout << "The first player could win." << endl;
    } else {
        cout << "The first player could not win." << endl;
    }


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}