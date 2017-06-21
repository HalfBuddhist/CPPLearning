//============================================================================
// Name        : SquareRoot.cpp
// Author      : LQW
// Version     :
// Copyright   : All copyleft reserved!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include "SquareRoot.h"
using namespace std;

int main() {
	//test the sqrt_binary_search
	cout << setprecision(10) << sqrt_binary_search(101, 0.0000001) << endl;
	//test the newton method
	cout << sqrt_Newton_Raphson(101, 0.0000001) << setprecision(6)<<endl
			<< sqrt_Newton_Raphson(101, 0.0000001) << endl;
	return 0;
}
