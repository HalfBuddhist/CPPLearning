#include <stdlib.h>

#include <iostream>
#include <memory>

struct Foo {
  Foo() { std::cout << "Foo::Foo\n"; }
  ~Foo() { std::cout << "Foo::~Foo\n"; }
  void bar() { std::cout << "Foo::bar\n"; }
};

void f(const Foo&) { std::cout << "f(const Foo&)\n"; }

struct D {
  void operator()(Foo* foo) {
    std::cout << "D operator()" << std::endl;
    delete foo;
  }
};

void TestAutoDestroy() {
  // 1. 普通的 new 对象.
  std::cout << "TestDestroy...................." << std::endl;
  { std::unique_ptr<Foo> p1(new Foo); }
  // 2. 普通的 new[] 对象.
  { std::unique_ptr<Foo[]> p2(new Foo[4]); }
  // 3. 自定义的 deleter.
  { std::unique_ptr<Foo, D> p3(new Foo); }
}

void TestOwner() {
  std::cout << "TestOwner...................." << std::endl;
  // 1. new object.
  std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
  if (p1) p1->bar();
  {
    std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
    f(*p2);
    if (p1 == nullptr) std::cout << "p1 is null. \n";

    p1 = std::move(p2);  // ownership returns to p1
    p2->bar();  // nullptr can could also call non-virtual member method,
                // because static binding.
    std::cout << "destroying p2...\n";
  }

  p1->bar();
}

void TestArrayOwner() {
  std::cout << "TestArrayOwner...................." << std::endl;
  // 1. new[] object.
  std::unique_ptr<Foo[]> p1(new Foo[4]);  // p1 owns Foo
  if (p1) p1[0].bar();

  {
    std::unique_ptr<Foo[]> p2(std::move(p1));  // now p2 owns Foo
    f(p2[0]);

    p1 = std::move(p2);  // ownership returns to p1
    p2[0].bar();
    std::cout << "destroying p2...\n";
  }

  p1[0].bar();
}

int main() {
  TestAutoDestroy();
  TestOwner();
  TestArrayOwner();
}
