/**
 * @file stated_function_obj.cpp
 * @author your name (you@domain.com)
 * @brief 有状态的函数对象，可以作到比普通函数更多。
 * 这里我们看一个可以拥有状态的函数对象，其用于生成连续序列：
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
  vector<int> v(10);
  std::generate(v.begin(), v.end(), IntSequence{0});
  /*  lambda实现同样效果
      int init = 0;
      std::generate(v.begin(), v.end(), [&init] { return ++init; });
  */
  std::for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
  //输出：1, 2, 3, 4, 5, 6, 7, 8, 9, 10

  return 0;
}