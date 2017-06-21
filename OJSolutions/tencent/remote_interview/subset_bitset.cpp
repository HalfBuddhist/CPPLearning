#include <iostream>
#include <stack>

#define _DEBUG
#define SIZE 26   // number of the elements
#define N 2  // branch numbers

using namespace std;

int a[SIZE]; //elements of the set,

void output(bitset<SIZE> a) {
    for (int i = 0; i < SIZE; i++) {
        if (a[i] == 1) {
            cout << (char) (i + 'a');
        }
    }
    cout << endl;
}

/**
 * 一：位图法：
    1）构造一个和集合一样大小的数组A，分别与集合中的某个元素对应，数组A中的元素只有两种状态：“1”和“0”，
    分别代表每次子集输出中集合中对应元素是否要输出，这样数组A可以看作是原集合的一个标记位图。
    2）数组A模拟整数“加一”的操作，每“加一”之后，就将原集合中所有与数组A中值为“1”的相对应的元素输出。
    设原集合为<a,b,c,d>，数组A的某次“加一”后的状态为[1,0,1,1]，则本次输出的子集为<a,c,d>。
    具体代码如下：

    SIZE * (N^(SIZE)), time complexity.
    可选的优化:
    在遍历输出子集的过程中，可以对程序做进一步的优化。例如，在第m次迭代中，只需要遍历前k个元素，k=log2(m)+1。
    简单来讲, 就是前面的位还没有来得及减掉, 全为1, 也就是在子集中都出现, 那么只需要检查其余的m位即可,这样虽然数量级不变,
    但是也会有一些性能上的改进.

    空间复杂度：
    该方法每次迭代都是独立进行，与上次迭代的结果没有任何关系。
    因此每次输出子集之后内存都可以被重复利用。只需要一个与原集合同样大小的数组，空间复杂度为O(n)。
 */
int main() {
    bitset<SIZE> bitmap;
    //output the null set
    output(bitmap);
    bitmap.set();
    unsigned long value = bitmap.to_ulong();
    while (value > 0) {
        bitset<SIZE> bit(value);
        output(bit);
        value--;
    }
    return 0;
}