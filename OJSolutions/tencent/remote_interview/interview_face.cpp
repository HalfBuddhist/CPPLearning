//
// Created by Qingwei on 2017/6/5.
//
#include <iostream>

#define _DEBUG

using namespace std;

/**
 * c语言编码，实现函数long htonl(long a)，也就是将主机序转化为网络序
 * 或者可以用类似于系统内的实现.
 *     ((__uint32_t)((((__uint32_t)(x) & 0xff000000) >> 24) | \
                (((__uint32_t)(x) & 0x00ff0000) >>  8) | \
                (((__uint32_t)(x) & 0x0000ff00) <<  8) | \
                (((__uint32_t)(x) & 0x000000ff) << 24)))
 */
long my_htonl(long a) {
    int times = 4;
    long ans = 0;
    while (times-- > 0) {
        ans <<= 8;
        ans += a & (0x00ff);
        a >>= 8;
    }
    return ans;
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

    cout << sizeof(long) << endl;
    cout << htonl(100) << endl;
    cout << my_htonl(100);


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}