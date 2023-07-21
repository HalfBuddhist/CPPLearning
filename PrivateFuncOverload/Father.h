//
// Created by Qingwei on 16/6/16.
//

#ifndef SYSTAXOFCCPP_FATHER_H
#define SYSTAXOFCCPP_FATHER_H

#include <iostream>
using namespace std;

class Father {
public:
    void publicFunc();

protected:
    string tag = "father";

private:
    void privateFunc();
};


#endif //SYSTAXOFCCPP_FATHER_H
