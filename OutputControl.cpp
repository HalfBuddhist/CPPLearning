//============================================================================
// Name        : SystaxOfCPP.cpp
// Author      : Qingwei Liu
// Version     :
// Copyright   : All copyleft reserved!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

int OutputControl() {
	//precision
	double f = 3.14159;
	cout << setprecision(5) << f << endl;                //3.1416
	cout << setprecision(9) << f << endl;                 //3.14159

//	cout << setiosflags(ios::fixed) << setprecision(5) << f << endl;   //3.14159
//	cout.setf(ios::fixed); cout << setprecision(5)<<f<<endl; //same func
	cout.setf(ios::fixed, ios::floatfield); cout << setprecision(5)<<f<<endl; //same func
//	cout << fixed << setprecision(5) << f <<endl; //same func

	cout  << setprecision(9) << f << endl; //3.141590000
	cout << f << endl;                                             //3.141590000
	cout << resetiosflags(ios::fixed) << setprecision(5) << f << endl; //3.14159
	cout.precision(6);	//same func as the setprecision,
//	the setprecision function should only be used as a stream manipulator as above.
	cout << f << endl;


	//the field
	std::cout.setf(std::ios::hex, std::ios::basefield); // set hex as the basefield
	std::cout.setf(std::ios::showbase);                  // activate showbase
	std::cout << 100 << '\n';
	std::cout.unsetf(std::ios::showbase);                // deactivate showbase
	std::cout << 100 << '\n';
	return 0;
}
