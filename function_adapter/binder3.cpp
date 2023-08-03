/**
 * @file binder3.cpp
 * @author your name (you@domain.com)
 * @brief 注意绑定器默认是以传值方绑定参数，如果需要引用绑定值，
 * 那么要使用std::ref和std::cref函数，分别代表普通引用和const引用绑定参数
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

void f(int& n1, int& n2, const int& n3) {
  cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  ++n1;
  ++n2;
  //   ++n3;  //无法编译
}

int main() {
  int n1 = 1, n2 = 2, n3 = 3;
  auto boundf = std::bind(f, n1, std::ref(n2), std::cref(n3));
  n1 = 10;
  n2 = 11;
  n3 = 12;
  cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  boundf();
  cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  //  Before function : 10 11 12
  //  In function : 1 11 12
  //  After function : 10 12 12

  return 0;
}