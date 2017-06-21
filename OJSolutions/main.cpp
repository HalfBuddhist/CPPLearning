#include <stdio.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;
#define _DEBUG

void GetIntA(int *p) {
    p = (int *) malloc(sizeof(int));
    return;
}

int *GetIntB() {
    int kk;
    return &kk;
}


int main() {

#ifdef _DEBUG
//    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif

//    int *a;
//    a = NULL;
//    *a = 1;

    int *p;
    p = NULL;
//    GetIntA(p);
//    *p = 0x22;
//    p = NULL;
    p = GetIntB();
    *p = 33;
    cout << *p;

    return 0;
}