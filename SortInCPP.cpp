/*
 * SortInCPP.cpp
 *
 *  Created on: 2016年6月8日
 *      Author: Qingwei
 */
#include <iostream>
#include <vector>
//#include <bits/stdc++.h>
using namespace std;

int SortInCPP() {
	int a[] = { 5, 4, 3, 2, 1 };
	vector<int> b(a, a + 5); //initialised b using elements of a.
	sort(a, a + 5);
	sort(b.begin(), b.end());
	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : b) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

