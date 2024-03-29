#include <iostream>
#include <memory>

struct Task {
  int mId;
  Task(int id) : mId(id) { std::cout << "Task::Constructor" << std::endl; }
  ~Task() { std::cout << "Task::Destructor" << std::endl; }
};

int main() {
  // 通过原始指针创建 unique_ptr 实例
  std::unique_ptr<Task> taskPtr(new Task(23));

  //通过 unique_ptr 访问其成员
  int id = taskPtr->mId;
  std::cout << id << std::endl;

  // 通过 make_unique 来创建
  auto myPi = std::make_unique<double>(3.1415);
  std::cout << *myPi << std::endl;

  return 0;
}
