#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// T需要支持输出流运算符
template <typename T>
class Print {
 public:
  void operator()(T elem) const { std::cout << elem << ' '; }
};

int main() {
  vector<int> v(10);
  int init = 0;
  generate(v.begin(), v.end(), [&init] { return init++; });

  // 使用for_each输出各个元素（送入一个Print实例）
  for_each(v.begin(), v.end(), Print<int>{});
  // 利用lambda表达式：std::for_each(v.begin(), v.end(), [](int x){ cout << x <<
  // ' ';}); 输出：0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  return 0;
}