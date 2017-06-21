/*
 * GCD.cpp
 *
 *  Created on: 2016年6月3日
 *      Author: Qingwei
 */

#include "GCD.h"

/**
 * 模MOD下, x^y
 */
long bin(long x, long y, long MOD) {
    if (y == 0) {
        return 1;
    }
    long long u = bin(x, y / 2, MOD);
    if (y % 2 == 0) {
        return u * u % MOD;
    }
    else {
        return u * u % MOD * x % MOD;
    }
}

/**
 * 求模mod下, a^b
 */
long power_mod(long a, long b, long mod) {
    long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long modular_inverse_rec(long x, long m) {
    return bin(x, m - 2, m);
}


long modular_inverse_iter(long x, long m) {
    return power_mod(x, m - 2, m);
}


unsigned long euclid(unsigned long a, unsigned long b) {
    if (a < b)
        std::swap(a, b);
    return b == 0 ? a : euclid(b, a % b);
}

unsigned long stein(unsigned long a, unsigned long b) {
    if (a < b) //arrange so that a>b
        std::swap(a, b);
    if (0 == b) //the base case
        return a;

    if (a % 2 == 0 && b % 2 == 0) //a and b are even
        return 2 * stein(a / 2, b / 2);

    if (a % 2 == 0) // only a is even
        return stein(a / 2, b);

    if (b % 2 == 0) // only b is even
        return stein(a, b / 2);

    return stein((a - b) / 2, b); // a and b are odd
}

long extended_euclid_recursive(long a, long b, long &x, long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long gcd = extended_euclid_recursive(b, a % b, x, y);
        long t = x;
        x = y;
        y = t - (a / b) * y;
        return gcd;
    }
}

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

long extended_euclid_weired(long a, long b, long *result) {
    long x1, x2, x3, y1, y2, y3, t1, t2, t3, q;
    x1 = y2 = 1;
    x2 = y1 = 0;
    x3 = (a >= b) ? a : b;
    y3 = (a >= b) ? b : a;

    while (true) {
        if (y3 == 0) {
            *result = x3; /* 两个数不互素则result为两个数的最大公约数，此时返回值为零 */
            return 0;
        }
        if (y3 == 1) {
            *result = y2; /* 两个数互素,则resutl为其乘法逆元，此时返回值为1 */
            return 1;
        }
        q = x3 / y3;
        t1 = x1 - q * y1;
        t2 = x2 - q * y2;
        t3 = x3 - q * y3;
        x1 = y1;
        x2 = y2;
        x3 = y3;
        y1 = t1;
        y2 = t2;
        y3 = t3;
    }
}

