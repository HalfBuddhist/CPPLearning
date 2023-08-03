/**
 * @file while_between_switch_case.cpp
 * @author your name (you@domain.com)
 * @brief 死循环，循环处理所有的case直到return 或者发生异常。
 * @version 0.1
 * @date 2022-07-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
using namespace std;

int main() {
  int a = 3;
  int cnt = 20;
  switch (a) {
    while (1) {
      case 1:
        if (cnt < 0) {
          return 0;
        }
        cout << "print 1 here." << endl;
        cnt--;
      case 2:
        if (cnt < 0) {
          return 0;
        }
        cout << "print 2 here." << endl;
        cnt--;
      case 3:
        if (cnt < 0) {
          return 0;
        }
        cout << "print 3 here." << endl;
        cnt--;
    }
  }
}
