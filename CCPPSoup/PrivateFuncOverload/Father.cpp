//
// Created by Qingwei on 16/6/16.
//

#include "Father.h"

void Father::publicFunc() {
    privateFunc();
}

void Father::privateFunc() {
    cout << "hello father."<< endl;
}
