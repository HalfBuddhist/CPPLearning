/**
 * @file lambda_binder.cpp
 * @author your name (you@domain.com)
 * @brief
 * C++11中lambda表达式无法实现移动捕捉变量，但是使用绑定器可以实现类似的功能
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> data{1, 2, 3, 4};
  auto func =
      std::bind([](const vector<int>& data) { cout << data.size() << endl; },
                std::move(data));
  func();                       // 4
  cout << data.size() << endl;  // 0

  return 0;
}