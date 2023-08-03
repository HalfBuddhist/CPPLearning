/**
 * @file internal_function_obj.cpp
 * @author your name (you@domain.com)
 * @brief <functional> 中定义了一些系统内置的函数对象，如std::greater, std::less
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class IntSequence {
 public:
  IntSequence(int initVal) : value{initVal} {}
  int operator()() { return ++value; }

 private:
  int value;
};

int main() {
  vector<int> v{3, 4, 2, 9, 5};
  // 升序排序
  std::sort(v.begin(), v.end());  // output: 2, 3, 4, 5, 9
  for_each(v.begin(), v.end(), [](int e) { cout << e << " "; });
  cout << endl;
  // 降序排列
  std::sort(v.begin(), v.end(), std::greater<int>{});  // output: 9, 5, 4, 3, 2
  for_each(v.begin(), v.end(), [](int e) { cout << e << " "; });

  return 0;
}