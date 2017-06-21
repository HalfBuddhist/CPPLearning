/*
 * SquareRoot.cpp
 *
 *  Created on: 2016年6月6日
 *      Author: Qingwei
 */

#include "SquareRoot.h"

double sqrt_binary_search(double n, const double threshold) {
	double low = 0.0;
	double high = n + 1;
	while ((high - low) > threshold) {
		double mid = (low + high) / 2;
		if (mid * mid < n) {
			low = mid;
		} else if (mid * mid > n) {
			high = mid;
		} else {
			return mid;
		}
	}
	return low;
}

// Function to calculate square root of the number using Newton-Raphson method
double sqrt_Newton_Raphson(double n, const double threshold) {
	double guess = 1.0;
	while (fabs(guess * guess - n) >= threshold) {
		guess = (n / guess + guess) / 2.0;
	}
	return guess;
}
