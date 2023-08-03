#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;
using nlohmann::json;

int main() {
  json animalArray = {"cat", "dog"};  //定义一个数组类型的json对象
  animalArray.push_back("pig");       //添加元素
  animalArray.emplace_back("duck");  // C++11 新方式添加元素，减少申请内存
  cout << animalArray << endl;

  //使用is_array()函数判断对象类型，使用empty函数判断数量是否为空
  if (animalArray.is_array() && !animalArray.empty()) {
    auto size = animalArray.size();  //使用 size 函数获取元素数量
    auto animalLast = animalArray.at(size - 1).get<std::string>();
    cout << animalLast << endl;
  }

  json animalObject = {{"kind", "dog"},
                       {"height", 50}};  //定义一个对象类型的json对象
  animalObject.emplace(make_pair("color", "red"));  //插入元素
  cout << animalObject << endl;
  animalObject.erase("kind");  //删除键值
  cout << animalObject << endl;

  //判断是否含有某个键值方式一
  //通过contains函数判断是否包含某个key
  if (animalObject.find("height") != animalObject.end()) {
    auto height = animalObject["height"].get<double>();
    cout << height << endl;
  }

  //   判断是否含有某个键值方式二
  //通过count函数计算某一个键的数量
  auto size = animalObject.count("height");
  if (size > 0) {
    auto height = animalObject["height"].get<double>();
    cout << height << endl;
  }

  //判断是否含有某个键值方式三
  auto iter = animalObject.find("height");  //通过find函数查找某个键的迭代器
  if (iter != animalObject.end()) {
    cout << *iter << endl;
  }

  //判断是否含有某个键值方式4, out of data.
  //   if (animalObject.contains("height"))
  //   //通过contains函数判断是否包含某个key
  //   {
  //     auto height = animalObject["height"].get<double>();
  //   }

  //遍历输出键值方式一
  // out of data.
  //   for (auto item : animalObject.items()) {
  //     std::cout << item.key() << " " << item.value() << std::endl;
  //   }

  //遍历输出键值方式2
  for (auto iter = animalObject.begin(); iter != animalObject.end(); ++iter) {
    std::cout << iter.key() << " " << iter.value() << std::endl;
  }

  //遍历输出键值方式3(C++17)
  // too new.
  //   for (auto [key, value] : animalObject.keys()) {
  //     std::cout << key << " " << value << std::endl;
  //   }
}
