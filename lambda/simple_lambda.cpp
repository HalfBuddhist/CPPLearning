#include <iostream>
#include <memory>

using namespace std;

int main() {
  ////////////////////////////////////////////////////////////////////////
  // 定义简单的 lambda 表达式
  auto basicLambda = [] { cout << "Hello, world!" << endl; };
  basicLambda();  // 输出：Hello, world!

  ////////////////////////////////////////////////////////////////////////
  // 指明返回类型
  auto add = [](int a, int b) -> int { return a + b; };
  // 自动推断返回类型
  auto multiply = [](int a, int b) { return a * b; };

  int sum = add(2, 5);           // 输出：7
  int product = multiply(2, 5);  // 输出：10
  cout << sum << "\n" << product << endl;

  ////////////////////////////////////////////////////////////////////////
  // 闭包捕捉变量
  int x = 10;
  auto add_x = [x](int a) { return a + x; };        // 复制捕捉x
  auto multiply_x = [&x](int a) { return a * x; };  // 引用捕捉x

  cout << add_x(10) << " " << multiply_x(10) << endl;
  x += 10;
  cout << "x:\t" << x << endl;
  cout << add_x(10) << " " << multiply_x(10) << endl;

  ////////////////////////////////////////////////////////////////////////
  // 闭包内修改捕获的变量
  auto add_x_2 = [x](int a) mutable {
    x *= 2;
    return a + x;
  };
  auto multiply_x_2 = [&x](int a) {
    x *= 2;
    return a * x;
  };
  cout << add_x_2(10) << endl;       // 输出 50
  cout << multiply_x_2(10) << endl;  // 400
  cout << "x:\t" << x << endl;       // 40

  ////////////////////////////////////////////////////////////////////////
  // 表达式捕捉
  // 利用表达式捕获，可以更灵活地处理作用域内的变量
  cout << "表达式捕捉：" << endl;
  x = 4;
  auto y = [&r = x, x = x + 1] {
    r += 2;
    return x * x;
  }();
  // 此时 x 更新为6，y 为25
  cout << x << "\t " << y << endl;

  // 直接用字面值初始化变量
  auto z = [str = "string"] { return str; }();
  // 此时z是const char* 类型，存储字符串 string
  cout << z << endl;

  ////////////////////////////////////////////////////////////////////////
  // 表达式捕捉 unique_ptr
  auto myPi = make_unique<double>(3.1415);
  auto circle_area = [pi = move(myPi)](double r) { return *pi * r * r; };
  cout << circle_area(1.0) << endl;  // 3.1415
  cout << myPi.get() << endl;  // 移动后赋值地址为0，反引用会出现 segment fault.

  ////////////////////////////////////////////////////////////////////////
  // 泛型lambda表达式
  cout << "泛型lambda表达式" << endl;
  auto add_3 = [](auto x, auto y) { return x + y; };
  int xx = add_3(2, 3);         // 5
  double yy = add_3(2.5, 3.5);  // 6.0
  cout << xx << endl << yy << endl;

  return 0;
}
