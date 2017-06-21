/**
 * GCD.h
 * gcd algorithms, 及乘法模逆元
 * Created on: 2016年6月3日
 * Author: Qingwei
 */

#ifndef GCD_H_
#define GCD_H_

#include <algorithm> // std::swap for c++ before c++11
#include <utility> // std::swap for c++ since c++11

/**
 * 计算x模 m 的逆元 - modular inverse, 以化乘法为除法.
 * 前提x, m互质, 且m为素数
 * 利用费马小定理
 * 复杂度O(log(m))
 */
long modular_inverse_rec(long x, long m);


/**
 * 计算x模 m 的逆元 - modular inverse, 以化乘法为除法.
 * 迭代版
 * 利用费马小定理
 */
long modular_inverse_iter(long x, long m);


/**
 * use euclid algo, could resove the situation where b > a
 * @param numbers to get gcd, require: a>=0, b>=0, a+b>0
 * @return the gcd of (a, b)
 */
unsigned long euclid(unsigned long a, unsigned long b);

/**
 * use stein algo, could resolve the situation where b > a
 * 
 * 欧几里德算法是计算两个数最大公约数的传统算法，无论从理论还是从实际效率上都是很好的。但是却有一个致命的缺陷，
 * 这个缺陷在素数比较小的时候一般是感觉不到的，只有在大素数时才会显现出来。
 * Stein算法由J. Stein 1961年提出，这个方法也是计算两个数的最大公约数。和欧几里德算法算法不同的是，Stein算法只有整数的移位和加减法，这对于程序设计者是一个福音。
 *
 * 考虑欧几里德算法，最恶劣的情况是，每次迭代a=2b-1,这样，迭代后，r=b-1。如果a小于2N，这样大约需要4N次迭代。而考虑Stein算法，每次迭代后，显然A(n+1)B(n+1)≤AnBn/2，
 * 最大迭代次数也不超过4N次。也就是说，迭代次数几乎是相等的。但是，需要注意的是，对于大素数，试商法将使每次迭代都更复杂，因此对于大素数Stein将更有优势。-百度百科
 * 
 * @param numbers to get gcd, require: a>=0, b>=0, a+b>0
 * @return the gcd of (a, b)
 */
unsigned long stein(unsigned long a, unsigned long b);

/**
 * Recursive extended euclid to calc the gcd and linear comibnation whose result is the gcd in a recursive implement，即线性丢番方程的解.
 * (that is the inverse modulo if gcd=1)
 * 
 * @param a, b: numbers to get calculated.
 * require: a>=0, b>=0, a+b>0，could resolve the situation where b > a
 *
 * @return gcd of (a, b), x and y is the linear combi whose result is the gcd (inverse modulo if prime each other)
 */
long extended_euclid_recursive(long a, long b, long &x, long &y);

/**
 * Standard extended euclid to calc the gcd and linear comibnation whose result is the gcd, 即线性丢番方程的解.
 * (that is the inverse modulo if gcd=1)
 *
 * @param a, b: numbers to get calculated.
 * require: a>=0, b>=0, a+b>0，could resolve the situation where b > a
 *
 * @return gcd of (a, b), x and y is the linear combi whose result is the gcd (inverse modulo if prime each other)
 */
long extended_euclid(long a, long b, long &x, long &y);

/**
 * An weired implementation of the extended euclid to calc the gcd and the inverse modulo only if they are prime.
 * A none recursive implementation. Cannot prove it correct, but so far so good.
 *
 * @param numbers to get gcd or the inverse modulo if prime each other
 * require: a>=0, b>=0, a+b>0，could resolve the situation where b > a
 *
 * @return 0 if no prime, and the result is the gcd;
 * 1 if prime, the result is the inverse modulo small to big.
 */
long extended_euclid_weired(long a, long b, long *result);

#endif /* GCD_H_ */
