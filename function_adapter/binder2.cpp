/**
 * @file binder2.cpp
 * @author your name (you@domain.com)
 * @brief 利用不同函数对象组合，函数适配器可以调用全局函数，
 * 下面的例子是不区分大小写来判断一个字符串是否包含一个特定的子串.
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

// 大写转换函数
char myToupper(char c) {
  if (c >= 'a' && c <= 'z') return static_cast<char>(c - 'a' + 'A');
  return c;
}

int main() {
  string s{"Internationalization"};
  string sub{"Nation"};

  auto pos =
      std::search(s.begin(), s.end(), sub.begin(), sub.end(),
                  std::bind(std::equal_to<char>{},
                            std::bind(myToupper, std::placeholders::_1),
                            std::bind(myToupper, std::placeholders::_2)));
  if (pos != s.end()) {
    cout << sub << " is part of " << s << endl;
  }

  // 输出：Nation is part of Internationalization
  return 0;
}