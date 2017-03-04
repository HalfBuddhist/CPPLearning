#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <set>
#include <map>
#include <bitset>
#include <iomanip>


/**
 * 本题目是一个典型的动态规划的问题.
 * 但由于要求的值很大, 虽然可以用动态表来解决表长度限制的问题. 但是时间上也会超时.
 *
 * 唯一的解法就是如果我们算出了前面的一些项(即f, F函数的值)后, 而后面的项可以用常数时间内或者有限复杂度的时间内算出就可以了.
 * 我们自然想到了插值算法, 而最常见的就是多项式插值(最主要是lagrange 插值与newton 插值), 如果要插值作到0误差,
 * 则要目标真实函数也是一个多项式(同次)函数.
 *
 * 而F函数的变化与其自变量的变化并不能构成多项式的变化,是低于多项式的变化速度的.
 * 可发现F(rem+i*W) form a polynomial of i of the degree N, 另外我们需要一个前n项的合来求得最后答案, 避免L-R差很大时的循环.
 * 而rem-fixed前n项的合是N-1次多项式, 而前面的N-1次项, 可以由动态填表来完成.
 * 枚举每一个rem, 并相加可得到前n项和.
 *
 * 而在求插值时遇到的除法运算, 考虑至最后的结果是模一个大质数, 我们可以用乘法逆元来解决.
 *
 */
#define X first
#define Y second
#define mp make_pair
#define pb push_back

typedef long long ll;

using namespace std;

const int MAXN = 11;
const int MOD = 1E9 + 7;
const int L = 1400100;
//const long long L = 1E17+5;

inline int mod(const long long x) {
    if (x >= 0) {
        return x % MOD;
    }
    return MOD + x % MOD;
}



//inv[i][j] = bin(mod(i - j), MOD - 2);
/**
 * 计算x模 y+2 的逆元, 化乘法为除法.
 * 前提x y+2互质
 * 费马小定理
 */
long long bin(long long x, long long y) {
    if (y == 0) {
        return 1;
    }
    long long u = bin(x, y / 2);
    if (y % 2 == 0) {
        return u * u % MOD;
    }
    else {
        return u * u % MOD * x % MOD;
    }
}

long long inv[15][15];

/**
 * lagrange 插值
 */
long long calc(const vector<long long> &x, const vector<long long> &y, int n, long long X) {
    long long res = 0;
    for (int i = 0; i < n; i++) {
        long long cur = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            long long num = mod(X - x[j]);
            //long long denum = bin( mod(x[i] - x[j]), MOD - 2 );
            long long denum = inv[i][j];
            cur = cur * num % MOD * denum % MOD;
        }
        res += cur * y[i];
        res %= MOD;
    }
    return res;
}

int n; //how many weights.
int a[MAXN]; //store the weights.
int f[L][MAXN]; //dp form to fill L in the maxn first type of weights.


/**
 * 形成n+1个插值点
 */
long long kill(int rem, long long wh, int w) {
    //cerr << rem << endl;
    vector<long long> x, y;
    int s = 0;
    for (int i = 0; i <= n; i++) {
        x.push_back(i);
    }
    for (int i = 0; i <= n; i++) {
        s += f[w * i + rem][n - 1];
        if (s >= MOD) {
            s -= MOD;
        }
        y.push_back(s);
        //cerr << i << " " << s << endl;
    }
    //cerr << " : " << wh << " " << calc(x, y, n, wh) << endl;
    return calc(x, y, n + 1, wh);
}


/**
 * 计算 calc F(0) + F(1) + ... + F(X) = ans(X)
 */
int fun(long long X) {
    //calc the 分母, 化乘法为除法.
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            inv[i][j] = bin(mod(i - j), MOD - 2);
        }
    }
    int w = 1; //W
    for (int i = 0; i < n; i++) {
        w *= a[i];
    }
    int res = 0;
    for (int rem = 0; rem < w; rem++) {
        //why iterate through all the remainders.
        //because the res bellow only include the rem as the X%W, not the others.
        if (rem > X) {
            continue;
        }
        long long wh = X / w - 1 + (X % w >= rem); //i, i+1, kill 先对他们进行了--
        res += kill(rem, wh, w); //得到插值后的值.
        if (res >= MOD) {
            res -= MOD;
        }
    }
    return res;
}

int brute(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        res += f[i][n - 1];
        if (res >= MOD) {
            res -= MOD;
        }
    }
    return res;
}

const int MAXW = 100000; //maxium of weight.

int main() {
    cout << 7 / (-4) << endl << 7 % (-4) << endl;
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/CountingWays/in.txt", "r", stdin);
    //input
    cin >> n;
    assert(1 <= n && n <= 10);
    long long ww = 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ww *= a[i];
        assert(a[i] > 0 && a[i] <= MAXW);
    }
    assert(ww <= MAXW);
    cerr << ww << " " << n << endl;
    long long l, r;
    cin >> l >> r;
    assert(r < 1E18);

    //initialize
    for (int j = 0; j < n; j++) { //initialize the dp table.
        f[0][j] = 1;
    }
    for (int i = 1; i < L; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) {
                f[i][j] = f[i][j - 1];
            }
            if (i >= a[j]) {
                f[i][j] += f[i - a[j]][j];
                if (f[i][j] >= MOD) {
                    f[i][j] -= MOD;
                }
            }
        }
    }

    int stupid;
    if (r <= 100000) {
        stupid = brute(l, r);
        cerr << stupid << endl;
    }
    int ans = mod(fun(r) - fun(l - 1));
    cout << ans << endl;
    if (r <= 100000) {
        assert(ans == stupid);
    }

    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}