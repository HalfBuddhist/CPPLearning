/*
 * SquareRoot.h
 * Methods to calculate the square root manually.
 * Both iterative method in essence.
 *  Created on: 2016-06-06
 *      Author: Qingwei
 */

#ifndef SQUAREROOT_H_
#define SQUAREROOT_H_

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * calulate the square root use binary search method.
 *
 * @param n - number to get the square root;
 * n >= 0
 * threshold - the precision level
 * (be careful about the double precision 16, that is 16 effective numbers totally
 * including the integer part and the decimals. So be carefull to set the threshold,
 * not smaller than 16 - integer part).
 *
 * @return the square root of n in precision level of threshold.
 */
double sqrt_binary_search(double n, const double threshold = 0.00001);

/**
 * calulate the square root use Newton Raphson method. This method is based on the fact that
 * b >= (a+b)/2 >= sqrt(ab) >= a  under: a>b>0, a b more closer, the (a+b)/2 more close to sqrt(ab),
 * and replace a,b with (a+b)/2 x/((a+b)/2) iteratively, which is more close to each other, until the
 * threshold is reached.
 *
 * @param n - number to get the square root;
 * n >= 0
 * threshold - the precision level
 * (be careful about the double precision 16, that is 16 effective numbers totally
 * including the integer part and the decimals. So be carefull to set the threshold,
 * not smaller than 16 - integer part).
 *
 * @return the square root of n in precision level of threshold.
 */
double sqrt_Newton_Raphson(double n, const double threshold = 0.00001);

#endif /* SQUAREROOT_H_ */
