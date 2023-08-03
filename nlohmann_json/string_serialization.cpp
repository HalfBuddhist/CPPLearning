#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;

int main() {
  using nlohmann::json;
  //反序列化(Deserialization)：_json/parse()
  json j1 = "{\"kind\":\"dog\",\"height\":50}"_json;  //方式一，通过"_json"实现
  cout << "j1_json: \t" << j1 << endl;

  //使用原生字符串关键字R来避免转移字符，但这一句并没有序列化，j2只保存字符串而已
  json j2 = R"({"kind":"dog","height":50})";
  //方式二，通过静态函数"parse"实现。
  json j3 = json::parse(R"({"kind":"dog","height":50})");
  //使用 parse 函数时，如果字符串不符合 json
  //规范导致解析失败，默认会抛出异常，可以使用 try...catch
  //结构捕获异常进行处理；或者设置 parse 函数的第三个函数参数为
  // false，此时解析失败不会抛出异常，但解析得到的结果为 null。
  cout << "j3_parse_rstring: \t" << j3 << endl;

  //序列化(Serialization)：dump(number)，number为打印出的空格数
  std::string animal1 = j1.dump();  // animal1值为{"kind":"dog","height":50}
  std::string animal2 = j1.dump(4);
  // animal2值为
  //  {
  //       "kind":"dog",
  //       "height":50,
  //  }
  cout << "Serialized j1: \t" << animal1 << endl;
  cout << "Serialized j2: \t" << animal2 << endl;
}
