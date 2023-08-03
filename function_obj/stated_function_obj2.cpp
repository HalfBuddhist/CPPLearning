/**
 * @file stated_function_obj2.cpp
 * @author your name (you@domain.com)
 * @brief 可以计算均值的函数对象
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

class MeanValue {
 public:
  MeanValue() : num{0}, sum{0} {}

  void operator()(int e) {
    ++num;
    sum += e;
  }

  double value() { return static_cast<double>(sum) / static_cast<double>(num); }

 private:
  int num;
  int sum;
};

int main() {
  vector<int> v{1, 3, 5, 7};
  MeanValue mv = std::for_each(v.begin(), v.end(), MeanValue{});
  cout << mv.value() << endl;  // output: 4

  return 0;
}