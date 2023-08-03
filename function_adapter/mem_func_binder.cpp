/**
 * @file mem_func_binder.cpp
 * @author liuqw (liuqingwei@ainnovation.com)
 * @brief 当想调用成员函数时，你还可以使用std::mem_fn函数，
 * 此时你可以省略掉用于调用对象的占位符：
 * 使用std::men_fn不需要绑定参数，可以更方便地调用成员函数。
 * std::mem_fn 还可以调用成员变量
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

class Person {
 public:
  Person(const string& n) : name{n} {}
  void print() const { cout << name << endl; }
  void print2(const string& prefix) { cout << prefix << name << endl; }

 private:
  string name;
};

class Foo {
 public:
  int data = 7;
  void display_greeting() { cout << "Hello, world.\n"; }
  void display_number(int i) { cout << "number: " << i << '\n'; }
};

int main() {
  vector<Person> p{Person{"Tick"}, Person{"Trick"}};
  std::for_each(p.begin(), p.end(), std::mem_fn(&Person::print));
  // 输出: Trick Trick

  Person n{"Bob"};
  std::mem_fn (&Person::print2)(n, "Person: ");
  // 输出：Person: Bob

  Foo f;
  // 调用成员函数
  std::mem_fn (&Foo::display_greeting)(f);    // Hello, world.
  std::mem_fn (&Foo::display_number)(f, 20);  // number: 20
  // 调用数据成员
  cout << std::mem_fn(&Foo::data)(f) << endl;  // 7

  return 0;
}