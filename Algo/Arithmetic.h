#ifndef ALGO_ARITHMETIC_H
#define ALGO_ARITHMETIC_H


class Arithmetic {

public:
    /**
     * 计算机加法效率实现, 并没有模拟实现, 只是采用了其同样利用位异或,与位与这些位操作与移位操作来实现.
     */
    int add(int a, int b);

    /**
     * 通过『减一个数等于加上一个负数』的思想, 来将减法转化为加法来实现.
     */
    int subtract(int a, int b);

    /**
     * 枚举因子相加, 注意处理越界与整形极值的情况
     * 如果结果overflow, 返回的结果没有任何意义, 仅是中间的一个计算结果.
     */
    int multiply_bf(int a, int b);

    /**
     * 使用russian peasant's algorithm.
     * 里面其实是使用了非模拟的加法, 如要self-contained, 可以容易改为使用模拟加法.
     * 取相反数也可以对应的用补码操作来代替.
     */
    int multiply_rpa(int a, int b);

    /**
     * 其实同上
     */
    int multiply(int a, int b);

    /**
     * 迭代相减
     * 里面其实是使用了非模拟的加减法, 如要self-contained, 可以容易改为使用模拟加减法.
     * 取相反数也可以对应的用补码操作来代替.
     */
    int divide_bf(int dividend, int divisor);

    /**
     * 取余
     * 方法同上
     */
    int remainder_bf(int dividend, int divisor);

    /**
     * 使用long来解决INT32_MIN绝对值无法存储会越界的问题.
     * 模拟2进制的试商除法来实现
     * 因为2进制商不是1就是0, 所以实际上是不存在试商的, 只需要判断大小, 大为1, 小为0
     */
    int divide_long(int dividend, int divisor);

    /**
     * 方法同上, 求余
     */
    int remainder_long(int dividend, int divisor);

    /**
     * 将INT32_MIN的绝对值拆分成(INT32_MAX + 1) 来解决,先处理前者相除, 然后在余数上+1来处理得到最后的商与余数.
     * 模拟2进制的试商除法来实现
     * 因为2进制商不是1就是0, 所以实际上是不存在试商的, 只需要判断大小, 大为1, 小为0
     */
    int divide(int dividend, int divisor);

    /**
     * 方法同上, 求余
     */
    int remaind(int dividend, int divisor);

    /**
     * 原理可行,也是最初上面借助原理的地方, 但是无法处理所有整数相除情况, 比如一些边界的情况,如 INT32_MIN/1;
     */
    int divideEx(int a, int b);

    /**
     * 解释同上
     */
    int remainderEx(int a, int b);
};


#endif //ALGO_ARITHMETIC_H
