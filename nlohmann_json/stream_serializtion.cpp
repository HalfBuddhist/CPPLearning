
#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;

int main() {
  using nlohmann::json;
  //反序列化(Deserialization)：>>
  json j1;
  cin >> j1;

  //序列化(Seriralization)：<<
  cout << j1;

  // 上述操作适用于 istream 和 ostream的子类,
  // 比如我们经常会用到的ifstream和ofstream
  ifstream in("animals.json");  //打开文件，关联到流in
  json animals;
  in >> animals;
  animals.at(0)["height"] = 60;  //修改数据
  in.close();

  ofstream out("animal.json");  //打开文件，关联到流out
  out << std::setw(4) << animals;
  //输出信息，std::setw(4)用于设置增加打印空格
  out.close();

  return 0;
}
