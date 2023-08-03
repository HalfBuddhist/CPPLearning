/**
 * @file object_serialization.cpp
 * @author your name (you@domain.com)
 * @brief
 * 在自定义对象命名空间中定义两个函数即可像basic
 * value一样进行反序列化和序列化：from_json(const json& j,T&
 * value)、to_json(json& j,const T& value)
 * @version 0.1
 * @date 2022-07-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;

using nlohmann::json;

//定义Animal类，其包含两个成员变量kind与height
class Animal {
 public:
  Animal() {}
  Animal(string kind, double height) {
    this->kind = kind;
    this->height = height;
  }
  string kind;
  double height;
};

//定义from_json(const json& j,T& value)函数，用于序列化
void from_json(const json& j, Animal& animal) {
  animal.kind = j["kind"].get<string>();
  animal.height = j["height"].get<double>();
}

//定义to_json(json& j,const T& value)函数，用于反序列化
void to_json(json& j, const Animal& animal) {
  j["kind"] = animal.kind;
  j["height"] = animal.height;
}

// main.cpp文件
int main() {
  Animal animal{"dog", 50};
  json j = animal;  //像basic value一样将自定义对象赋值给json value
  cout << j << endl;

  j["height"] = 60;  //修改数据
  cout << j << endl;

  //像basic value一样通过get函数获取值，将其值直接赋值给自定义对象
  Animal animalNew = j.get<Animal>();
  cout << animalNew.height << endl;  //输出60
  return 0;
}
