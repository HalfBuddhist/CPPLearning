#include <iostream>
#include <math.h>
#include <assert.h>

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

int main() {
#ifdef _DEBUG
    freopen("/Users/Qingwei/Documents/workspace/Clion/in.txt", "r", stdin);
#endif

    int q;
    long a, b, c;
    cin >> q;
    while (q-- > 0) {
        cin >> a >> b >> c;
        long x, y;
        long g = extended_euclid(a, b, x, y);
        assert(a * x + b * y == g);
        double orthogonality_x = (double(a * c)) / (a * a + b * b);
        long alpha = c / g;
        assert(c % g == 0);
        double k = (orthogonality_x - alpha*x) * g / b;
        long up_x = ((long) ceil(k)) * b / g + x * alpha;
        long up_y = (c - a * up_x) / b;
        assert(a * up_x + b * up_y == c);
        long dn_x = ((long) floor(k)) * b / g + x * alpha;
        assert(up_x >= dn_x);
        long dn_y = (c - a * dn_x) / b;
        assert(a * dn_x + b * dn_y == c);

#ifdef _DEBUG
        cerr << "x:" << x << endl
        << "y:" << y << endl
        << "orth x :\t" << orthogonality_x << endl
        << "alpha:\t" << alpha << endl
        << "k:\t" << k << endl
        << "up_x:\t" << up_x << endl
        << "dn_x:\t" << dn_x << endl
        << "**********************" << endl;
#endif

        if (dn_x <= 0) {
            cout << up_x << " " << up_y << endl;
        } else {
            double distance_up = up_x * up_x + up_y * up_y;
            double distance_dn = dn_x * dn_x + dn_y * dn_y;
            if (distance_up < distance_dn) {
                cout << up_x << " " << up_y << endl;
            } else {
                cout << dn_x << " " << dn_y << endl;
            }
        }
    }

    return 0;
}