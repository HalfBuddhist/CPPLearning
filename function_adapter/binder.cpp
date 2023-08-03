#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

int main() {
  // 得到一个减去固定树的函数对象：
  auto minus10 = std::bind(std::minus<int>{}, std::placeholders::_1, 10);
  cout << minus10(100, 10) << endl;  // 输出10

  // 逆转参数顺序
  auto vminus = std::bind(std::minus<int>{}, std::placeholders::_2,
                          std::placeholders::_1);
  cout << vminus(20, 10) << endl;  // 输出-10

  // 绑定器还可以互相嵌套，从而实现函数对象的组合：
  // 定义一个接收一个参数，然后将参数加10再乘以2的函数对象
  auto plus10times2 =
      std::bind(std::multiplies<int>{},
                std::bind(std::plus<int>{}, std::placeholders::_1, 10), 2);
  cout << plus10times2(4) << endl;  // 输出： 28

  // 定义3次方函数对象
  auto pow3 = std::bind(std::multiplies<int>{},
                        std::bind(std::multiplies<int>{}, std::placeholders::_1,
                                  std::placeholders::_1),
                        std::placeholders::_1);
  cout << pow3(3) << endl;  // 输出：27

  return 0;
}
