//
// Created by Qingwei on 16/6/16.
//

#include <iostream>
#include "Father.h"
#include "Son.h"
using namespace std;

void TestPrivateOverload(){
    cout<<"*****TestPrivateOverload******"<<endl;
    Son son;
    son.publicFunc();
//    cout << son.tag;

    Father father;
}
