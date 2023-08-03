#include <iostream>
using namespace std;

class Point {
  // friend Point add(Point, Point); // 友元函数
  // friend Point operator+(const Point &, const Point &);
  friend ostream &operator<<(ostream &cout, const Point &point);
  friend istream &operator>>(istream &cin, Point &point);
  int m_x, m_y;

 public:
  Point(int x, int y) : m_x(x), m_y(y) {}
  void display() { cout << "(x1=" << m_x << ", x2=" << m_y << ")" << endl; }
  // 第一个const表示返回值是个常量，用来防止(p1+p2)=Point(10,20); 这种赋值
  // 括号内第二个const表示传入的参数可以接收const也可以接收非const,
  // 且限制对其参数成员的修改。
  // 第三个const表示常量可以调用该函数,
  // 而且为了限定隐含的this指针，即这个成员函数不能修改其数据成员。
  // 一般在类中这样用，这个成员函数的功能多数是get数据成员，
  // 即获得对象的某个数据，只读不写。
  const Point operator+(const Point &point) const {
    return Point(m_x + point.m_x, m_y + point.m_y);
  }

  const Point operator-(const Point &point) const {
    return Point(this->m_x - point.m_x, this->m_y - point.m_y);
  }

  Point &operator+=(const Point &point) {  // 返回值要注意
    this->m_x += point.m_x;
    this->m_y += point.m_y;
    return *this;
  }

  bool operator==(const Point &point) const {
    return point.m_x == this->m_x && point.m_y == this->m_y;
  }

  bool operator!=(const Point &point) const {
    return point.m_x != this->m_x || point.m_y != this->m_y;
  }

  const Point operator-() const { return Point(-m_x, -m_y); }

  /* // 这样写也可以达到效果，但是会多创建一个对象，不如下面的写法好
  Point operator++() { // ++a
      return Point(++m_x, ++m_y);
  }*/
  Point &operator++() {  // ++a
    ++m_x;
    ++m_y;
    return *this;
  }

  /*const Point operator++(int) { // a++
      return Point(m_x++, m_y++);
  }*/
  const Point operator++(int) {
    Point old = Point(m_x, m_y);
    m_x++;
    m_y++;
    return old;
  }

  Point &operator--() {  // --a
    --m_x;
    --m_y;
    return *this;
  }

  const Point operator--(int) {  // a--
    return Point(m_x--, m_y--);
  }
};

// 重载 "<<"，由于结果是 cout << a;不可以当作成员函数来重载，必须写在全局区。
ostream &operator<<(ostream &cout, const Point &point) {
  cout << "(x=" << point.m_x << ", y=" << point.m_y << ")";
  return cout;
}

// 重载">>",由于接收的参数会修改，不能加const修饰
istream &operator>>(istream &cin, Point &point) {
  cin >> point.m_x >> point.m_y;
  return cin;
}

// const Point operator+(const Point &p1, const Point &p2) { //
// 建议加const，并且设定为引用类型
//     return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
// }

int main() {
  const Point p1(10, 20);
  Point p2(10, 30);
  Point p3(30, 40);

  cout << "point: " << p1 + p2 << endl;

  //   cin >> p2 >> p3;
  //   cout << p2 << p3 << endl;

  // Point p4 = --p2 + Point(10, 20);
  // Point p4 = ++p2 + Point(10, 20);
  // p4.display(); // p2++ 20 50    ++p2 21 51
  // p2.display(); // 11 31

  /*p2++;
  (++p2) = p1;
  (++p2)++;*/
  //(p2++) = p1; //不可以
  // p2.display();

  // Point p4 = -p3;
  // p4.display();

  // Point p4 = p1 + p2 + p3;
  // p1 += p2;
  //(p1 += p2)+=p3;
  // p1.display();

  // cout << (p1 == p2) << endl;

  // p4.display();

  // Point p4 = add(p1, p2);
  // p4.display();

  return 0;
}
