#include <iostream>
#include <complex>
#include <assert.h>

#define _DEBUG

using namespace std;

long regular_modular(long var, long mod) {
    assert(mod > 0);
    while (var >= mod) {
        var -= mod;
    }
    while (var < 0) {
        var += mod;
    }
    return var;
}

int main() {
#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/in.txt", "r", stdin);
#endif
    int q;
    cin >> q;
    while (q-- > 0) {
        long a, b, m, k;
        cin >> a >> b >> k >> m;

        if (k == 0) {
            cout << 1 << " " << 0 << endl;
            continue;
        }

        complex<long> p, t;
        complex<long> x(a, b);
        while ((k & 1) == 0l) { //when k == 0????
            t = x * x;
            x.real(t.real() % m);
            x.imag(t.imag() % m);
            k >>= 1;
        }
        p = x;
        k >>= 1;
        while (k > 0) {
            t = x * x;
            x.real(t.real() % m);
            x.imag(t.imag() % m);
            if ((k & 1) != 0) {
                t = p * x;
                p.real(t.real() % m);
                p.imag(t.imag() % m);
            }
            k >>= 1;
        }

        //get final p
        cout << regular_modular(p.real() % m, m) << " " << regular_modular(p.imag() % m, m) << endl;
    }

#ifdef _DEBUG
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}