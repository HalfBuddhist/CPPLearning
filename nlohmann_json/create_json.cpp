#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;

int main() {
  using nlohmann::json;

  //方式一：
  json j;
  j["name"] = "LeBorn Jame";                                //字符串
  j["number"] = 23;                                         //整数
  j["man"] = true;                                          //布尔值
  j["children"] = {"LeBorn Jr", "Bryce Maximus", "Zhuri"};  //数组
  j["behavior"]["funny"] = "gigigigigigi";                  //对象中元素值
  j["wife"] = {{"name", "Savannah Brinson"}, {"man", false}};  //对象

  //方式二
  json j2 = {{"name", "LeBorn Jame"},
             {"number", 23},
             {"man", true},
             {"children", {"LeBorn Jr", "Bryce Maximus", "Zhuri"}},
             {"behavior", {{"funny", "gigigigigigi"}}},
             {"wife", {{"name", "Savannah Brinson"}, {"man", false}}}};

  cout << j << endl;
  cout << j2 << endl;

  return 0;
}
