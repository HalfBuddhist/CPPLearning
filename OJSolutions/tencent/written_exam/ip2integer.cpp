//
// Created by Qingwei on 2017/6/2.
//

#include <iostream>

#define _DEBUG

using namespace std;

/**
 * 1. 用C语言写一段代码，不使用现成的库函数，将一个点分十进制形式的IPv4地址
 * （例如：127.0.0.1）转换为一个32位的主机序（注意是主机序）整数。
 * inet_addr 的实现版本.
 */
unsigned int getip(char *address[]) {
    unsigned int ans = 0;
    int cnt = 4;
    while (cnt-- > 0) {
        ans <<= 8;
        unsigned int seg = (unsigned int) atoi(address[3 - cnt]); // host byte order
//        int seg = atoi(address[cnt]);     //network byte order
        ans += (0x00FF & seg);
    }
    return ans;
}


int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

    char *address[] = {"127", "0", "0", "1"};
    unsigned int ans = getip(address);
    cout << ans << endl;

//    int ttt = inet_addr("127.0.0.1");
//    cout << ttt << endl;

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}