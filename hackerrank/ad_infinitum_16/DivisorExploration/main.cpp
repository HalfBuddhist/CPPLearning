#include <iostream>

#define _DEBUG

using namespace std;

long power_mod(long a, long b, long mod) {
    long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long modular_inverse_iter(long x, long m) {
    return power_mod(x, m - 2, m);
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/in.txt", "r", stdin);
    freopen("/Users/Qingwei/Documents/workspace/Clion/out.txt", "w", stdout);
#endif

    //presolve
    long mod = (long) (1e9 + 7);
    long factorial[(int) (2e5 + 5)];
    long factorial_inv[(int) (2e5 + 5)];
    factorial[1] = 1;
    factorial_inv[1] = 1;
    for (int i = 2; i < (int) (2e5 + 5); i++) {
        long temp = (((long) i) * (i + 1) / 2) % mod;
        factorial[i] = (temp * factorial[i - 1]) % mod;
//        factorial[i] = regular_mod(factorial[i], mod);
        factorial_inv[i] = modular_inverse_iter(factorial[i], mod);
//        factorial_inv[i] = regular_mod(factorial_inv[i], mod);
    }

    //input
    int d, m, a;
    cin >> d;
    while (d-- > 0) {
        cin >> m >> a;
        cout << (factorial[a + m + 1] * factorial_inv[a + 1]) % mod << endl;
    }


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}