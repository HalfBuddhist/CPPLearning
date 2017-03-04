#include <iostream>
#include <assert.h>

using namespace std;

/**
 * 分治法新的理解,原来不仅可以将原来的数据规模分治成logn次-即递归分治, 还可以只分一次的-一次分治.
 *
 * 这样对于原来的规模可以减半, 我们这里考虑一次分治前后的复杂度,
 * 如果原来的复杂度为n, 则前后的复杂度则为 n/2 + n/2 = n, 并没有提升.
 * 如果为logn, 则之后的复杂度为logn/2 + logn/2 = 2logn -4 则反而复杂了.
 * 如果为n2, 后复杂度为n2/2, 还是提升了效率的,但提升并不显著.
 * 如果为2^n, 后复杂度为2^(n/2) * 2, 因为是指数式增长,所以还是极大的提高了效率的.
 * 如果为n!, 后复杂度为(n/2)!*2, 则同样是极大的提高了效率.
 *
 * 但要注意在分治后的merge过程通常不是常数时间内可以完成的, 所以实际上的复杂度为要比上面的所述的要复杂一些,如下面的dp的形成
 * 则需要3^(n/2)的复杂度. 但只要控制复杂度不超过现有规模就可以了.
 *
 * 一般情况下, 只有在指数与阶乘复杂度的情况下利用一次分治才会带来效率的大幅提升,
 * 且通常一次分治算法不需要两个半区单独的进行同样的过程;
 * 下半区的处理可能需要利用上半区的计算结果, 通常情况下有必要对上半区的计算结果进行加工处理得到一种下半区可以利用的中间结果.
 * 由上可知上下半区的处理并不对称, 所以无法进行递归分治.
 *
 * 使用一次分治的原因在于使用递归分治的策略时merge有难度, 或者虽可行,但无法减少本来复杂度的情况.
 */


int a[55][55], c[55];
int n, m;
int N;

int val[(1 << 17)]; //the cost in the first half
int dp[(1 << 17)];  //the max for the mask
int hm[(1 << 17)];  //cout for the max

/**
 * calc the max for the mask and cnt.
 */
void rec(const int t, const int N, const int msk, const int cur) {
    if (t == N) {
        if (dp[msk] < val[cur]) {
            dp[msk] = val[cur];
            hm[msk] = 0;
        }
        if (dp[msk] == val[cur]) {
            hm[msk]++;
        }
        return;
    }
    rec(t + 1, N, msk, cur);
    if ((1 << t) & msk) {
        rec(t + 1, N, msk, cur + (1 << t));
    }
}

int best = 0;
long long ways = 0;

/**
 * cal the second half.
 * k, n, 0, 0
 */
void go(const int t, const int finish, const int cur, const int cost) {
    if (t == finish) {
        //seconf half is legal?
        bool ok = true;
        for (int i = N; i < finish; i++) {
            for (int j = N; j < finish; j++) {
                if (((1 << i) & cur) && ((1 << j) & cur) && a[i][j] == true) {
                    ok = false;
                }
            }
        }
        if (ok == false) {
            return;
        }

        //remove the vertex from the first half.
        int allow = 0;
        for (int i = 0; i < N; i++) {
            bool ok = true;
            for (int j = N; j < finish; j++) {
                if (((1 << j) & cur) && a[i][j] == true) {
                    ok = false;
                }
            }
            if (ok == true) {
                allow += (1 << i);
            }
        }
        int tot_cost = cost + dp[allow];
        if (best < tot_cost) {
            best = tot_cost;
            ways = 0;
        }
        if (best == tot_cost) {
            ways += hm[allow];
        }

        return;
    }
    go(t + 1, finish, cur, cost);
    go(t + 1, finish, cur + (1 << t), cost + c[t]);
}


/**
 * brute force O(2^n)
 */
void brute() {
    int brans = 0;
    int brways = 0;
    for (int msk = 0; msk < (1 << n); msk++) {
        bool ok = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (((1 << i) & msk) && ((1 << j) & msk) && a[i][j] == true) {
                    ok = false;
                }
            }
        }
        if (ok == false) {
            continue;
        }
        int cost = 0;
        for (int i = 0; i < n; i++) {
            if ((1 << i) & msk) {
                cost += c[i];
            }
        }
        if (brans < cost) {
            brans = cost;
            brways = 0;
        }
        if (brans == cost) {
            brways++;
        }
    }
    cerr << brans << " " << brways << endl;
    assert(brans == best && brways == ways);

}

int main() {
    freopen("/Users/Qingwei/Documents/workspace/Clion/hackerrank/week_code_21/DemandingMoney/input.txt", "r", stdin);
    time_t start_t = clock();

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < m; i++) {
        int aa, bb;
        cin >> aa >> bb;
        aa--;
        bb--;
        a[aa][bb] = a[bb][aa] = true;
    }

    //resolve the first half
    N = n / 2;
    for (int i = 0; i < (1 << N); i++) { //枚举每个方案, i则形成掩码.
        bool ok = true;
        int cost = 0;
        for (int j = 0; j < N; j++) {
            if ((1 << j) & i) {//相当于只取了前面的N位做掩码, 最低位并没有用
                cost += c[j];
            }
            for (int k = 0; k < N; k++) {
                if (((1 << j) & i) && ((1 << k) & i) && a[j][k] == true) {
                    ok = false;
                }
            }
        }
        if (ok == false) {
            cost = -1; //not feasible
        }
        val[i] = cost;
    }

    //calc the max value for under the spec mask and cnt.
    for (int i = 0; i < (1 << N); i++) {
        rec(0, N, i, 0);
    }

    //the second half
    go(N, n, 0, 0);

    cout << best << " " << ways << endl;
//    cerr << best << " " << ways << endl;
    //brute();

    time_t end_t = clock();
    cout << float(end_t - start_t) / CLOCKS_PER_SEC;
    return 0;
}