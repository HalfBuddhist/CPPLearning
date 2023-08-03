#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;

int main() {
  using nlohmann::json;

  json j = {{"name", "LeBorn Jame"},
            {"number", 23},
            {"children", {"LeBorn Jr", "Bryce Maximus", "Zhuri"}},
            {"man", true},
            {"wife", {{"name", "Savannah Brinson"}}}};
  cout << j << endl;

  auto name = j["name"].get<std::string>();  //方式一
  cout << name << endl;

  // 方式二,  报错，无此方法。
  //   int number = 0;
  //   j["number"].get_to(number);
  //   cout << number << endl;

  // 获取数组元素方式一，越界后不会抛出异常，直接中断
  auto childOne = j["children"][0].get<std::string>();
  cout << childOne << endl;

  auto childTwo = j["children"].at(1).get<std::string>();  //越界后抛出异常
  cout << childTwo << endl;

  auto wifeName = j["wife"]["name"].get<std::string>();
  cout << wifeName << endl;

  //不推荐使用这种隐式转换的方式
  bool man = j["man"];
  cout << man << endl;
}
