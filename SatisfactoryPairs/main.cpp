#include <iostream>

#define _DEBUG

using namespace std;

long extended_euclid(long a, long b, long &x, long &y) {
    //check the order
    bool asc_order = true;
    if (a < b) {
        std::swap(a, b);
        asc_order = false;
    }

    long s0 = 1, t0 = 0, s1 = 0, t1 = 1;
    long q, r, gcd = b;
    if (b == 0) {
        gcd = a;
        s1 = 1;
        t1 = 0;
    }
    else {
        while (a % b != 0) {
            q = a / b;
            r = a % b;

            long t = s1;
            s1 = s0 - q * s1;
            s0 = t;
            t = t1;
            t1 = t0 - q * t1;
            t0 = t;

            a = b;
            gcd = b = r;
        }
    }

    //return the linear combo as the asc_order
    if (asc_order) {
        x = s1;
        y = t1;
    } else {
        x = t1;
        y = s1;
    }
    return gcd;
}


/**
 * 枚举a,b 用extended euclid 计算gcd来判断线性丢番图方程的有解性与其通解.
 * O(n^2*log^2n), 应该会超时.
 *
 * some test case:
 * 25 / 65
 * 25361 / 507280
 * 10 / 15
 * 4 / 2
 */
int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/in.txt", "r", stdin);
#endif
    int n;
    cin >> n;
    int cnt = 0;

    //resolve
    for (int b = 1; b < n; b++) {
        for (int a = 1; a < b; a++) {
            //if legal
            long x, y;
            int gcd = (int) extended_euclid(a, b, x, y);
            if (n % gcd == 0) {
                //legal and check the positive
                int bei = n / gcd;
                x *= bei;
                y *= bei;
                if (x > 0 && y > 0) cnt++;
                else if (x <= 0 && y <= 0) continue;
                else if (x <= 0 && y > 0) {
                    int k = (-1 * x * gcd) / b + 1;
                    if (y - k * a / gcd > 0) cnt++;
                    else continue;
                } else if (y <= 0 && x > 0) {
                    int k = (-1 * y * gcd) / a + 1;
                    if (x - k * b / gcd > 0) cnt++;
                    else continue;
                }
            } else {
                continue;
            }
        }
    }

    cout << cnt << endl;

#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}