#include <iostream>
using namespace std;

class CCar {
 private:
  int price;
  friend class CDriver;  //声明 CDriver 为友元类
};

class CDriver {
 public:
  CCar myCar;
  void ModifyCar()  //改装汽车
  {
    myCar.price += 1000;  //因CDriver是CCar的友元类，故此处可以访问其私有成员
  }
};