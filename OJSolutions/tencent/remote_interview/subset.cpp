#include <iostream>
#include <stack>

#define _DEBUG
#define SIZE 25   // number of the elements
#define N 2  // branch numbers

using namespace std;

int a[SIZE]; //elements of the set,

void output() {
    for (int i = 0; i < SIZE; i++) {
        if (a[i] == 2) {
            cout << (char) (i + 'a');
        }
    }
    cout << endl;
}

/**
 * SIZE * (N^(SIZE)), time complexity.
 */
int main() {
    int depth = 0; //current set branch location.
    while (depth >= 0) {
        if (depth == SIZE) {
            output();
            depth--;
        } else {
            a[depth] = (a[depth] + 1) % (N + 1); //0 indicate no set
            if (a[depth] == 0)
                depth--; //backtracking.
            else
                depth++;
        }
    }
    return 0;
}