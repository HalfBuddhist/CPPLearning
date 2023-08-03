/**
 * @file binder4.cpp
 * @author your name (you@domain.com)
 * @brief  绑定器可以用于调用类中的成员函数：
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

int main() {
  vector<Person> p{Person{"Tick"}, Person{"Trick"}};
  // 调用成员函数print
  std::for_each(p.begin(), p.end(),
                std::bind(&Person::print, std::placeholders::_1));
  // 此处的std::placeholders::_1表示要调用的Person对象，所以相当于调用arg1.print()
  // 输出：Tick   Trick

  std::for_each(p.begin(), p.end(),
                std::bind(&Person::print2, std::placeholders::_1, "Person: "));
  // 此处的std::placeholders::_1表示要调用的Person对象，
  // 所以相当于调用arg1.print2("Person: ")
  // 输出：Person: Tick   Person: Trick

  return 0;
}