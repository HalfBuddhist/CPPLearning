#include <iostream>

#define _DEBUG

using namespace std;

#include "Arithmetic.h"

int Arithmetic::add(int a, int b) {
    int sum = a;
    int carry = b;
    while (carry) {
        int tmps = sum;
        sum = tmps ^ carry;
        carry = (tmps & carry) << 1;
    }
    return sum;
}

int Arithmetic::subtract(int a, int b) {
    int subtrahend = add(~b, 1);
    int sub = add(a, subtrahend);
    return sub;

    //another way, 这样就体现不了负数就是补码来实现的, 补码的实现过程也体现不了
    return add(a, -b);
}

int Arithmetic::multiply_bf(int a, int b) {
    //overflow test
    if (a == INT32_MIN) {
        return b == 0 ? 0 : a;
    }
    if (b == INT32_MIN) {
        return a == 0 ? 0 : b;
    }

    //将乘数和被乘数都取绝对值, 可能存在越界的情况, 比如a = -Int32_MIN
    int multiplier = a < 0 ? add(~a, 1) : a;
    int multiplicand = b < 0 ? add(~b, 1) : b;
    //交换按大小
    if (multiplier > multiplicand) {
        swap(multiplicand, multiplier);
    }
    //计算绝对值的乘积
    int product = 0, last = 0;
    int count = 0;
    while (count < multiplier) {
        product = add(product, multiplicand);
        if (product < last) {
            //over flow, break and exit
            break;
        }
        last = product;
        count = add(count, 1);
    }
    //计算乘积的符号
    if ((a ^ b) < 0) {
        product = add(~product, 1);
    }
    return product;
}

int Arithmetic::multiply_rpa(int a, int b) {
    //overflow test
    if (a == INT32_MIN) {
        return b == 0 ? 0 : a;
    }
    if (b == INT32_MIN) {
        return a == 0 ? 0 : b;
    }

    //recude cost
    if (abs(a) < abs(b)) {
        swap(a, b);
    }

    int multiplier = b < 0 ? add(~b, 1) : b;
    int product = a;
    int r = 0;
    while (multiplier > 0) { // = 0?
        if (multiplier & 0x0001) { //odd
            r += product; //or use add function r = add (r, product)
        }
        product <<= 1;
        multiplier >>= 1;
    }

    if (b >= 0) return r;
    else return -r; // or add(~product, 1);
}

int Arithmetic::multiply(int a, int b) {
    //overflow test
    if (a == INT32_MIN) {
        return b == 0 ? 0 : a;
    }
    if (b == INT32_MIN) {
        return a == 0 ? 0 : b;
    }

    //将乘数和被乘数都取绝对值
    int multiplier = a < 0 ? add(~a, 1) : a;
    int multiplicand = b < 0 ? add(~b, 1) : b;
    //交换按大小
    if (multiplier > multiplicand) {
        swap(multiplicand, multiplier);
    }
    //计算绝对值的乘积
    int product = 0;
    while (multiplier) {
        if (multiplier & 0x1) {
            product = add(product, multiplicand);
        }
        multiplicand = multiplicand << 1;
        multiplier = multiplier >> 1;
    }
    //计算乘积的符号
    if ((a ^ b) < 0) {
        product = add(~product, 1);
    }
    return product;
}

int Arithmetic::divide_bf(int dividend, int divisor) {
    // zero resovle
    if (divisor == 0) throw runtime_error("divided by zero");
    if (dividend == 0) return 0;

    bool a = dividend > 0, b = divisor > 0;
    int cur = dividend;
    int quotient = 0;
    while (!((cur > 0) ^ a)) {
        if (!(a ^ b)) cur -= divisor;
        else cur += divisor;
        quotient++;
    }
    if (!(a ^ b))
        cur += divisor;
    else cur -= divisor; //cur is the remainder
    quotient--;

    return !(a ^ b) ? quotient : -quotient;
}

int Arithmetic::remainder_bf(int dividend, int divisor) {
    // zero resovle
    if (divisor == 0) throw runtime_error("divided by zero");
    if (dividend == 0) return 0;

    bool a = dividend > 0, b = divisor > 0;
    int cur = dividend;
    int quotient = 0;
    while (!((cur > 0) ^ a)) {
        if (!(a ^ b)) cur -= divisor;
        else cur += divisor;
        quotient++;
    }
    if (!(a ^ b))
        cur += divisor;
    else cur -= divisor; //cur is the remainder
    quotient--;

    return cur;
}


int Arithmetic::divide(int dividend, int divisor) {
    // zero resovle
    if (divisor == 0) throw runtime_error("divided by zero");
    if (dividend == 0) return 0;

    if (divisor == INT32_MIN) { // necessary to put the abs(divisor) in division
        if (dividend == divisor) return 1;
        else return 0;
    }

    //模拟真实的2进制除法
    int additional = 0;
    int divident_a = dividend >= 0 ? dividend : -dividend;
    int divisor_a = divisor >= 0 ? divisor : -divisor; //add(~divisor, 1) replaced if no - operator
    if (dividend == INT32_MIN) {
        divident_a = INT32_MAX;
        additional = 1;
    }

    //calculate length
    int cnt = 0, t = divident_a;
    int invert = 0;
    while (t > 0) {
        invert <<= 1;
        invert |= t & 0x1;
        t >>= 1;
        cnt++;
    }

    //模拟除法
    int quotient = 0;
    int remainder = 0;
    while (cnt-- > 0) {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert >>= 1;
        quotient <<= 1;
        if (remainder >= divisor_a) {
            quotient |= 0x1;
            remainder -= divisor_a;
        }
    }
    //处理越界的情况
    if (additional) {
        if (remainder + 1 >= divisor_a) {
            quotient += 1;
            remainder = remainder + 1 - divisor_a;
        } else {
            remainder += 1;
        }
    }

    //求商的符号
    if ((dividend ^ divisor) < 0) {//negtive
        return -quotient;
    } else return quotient;

}

int Arithmetic::remaind(int dividend, int divisor) {
    // zero resovle
    if (divisor == 0) throw runtime_error("divided by zero");
    if (dividend == 0) return 0;

    if (divisor == INT32_MIN) { // necessary to put the abs(divisor) in division
        if (dividend == divisor) return 0;
        else return dividend;
    }

    //模拟真实的2进制除法
    int additional = 0;
    int divident_a = dividend >= 0 ? dividend : -dividend;
    int divisor_a = divisor >= 0 ? divisor : -divisor; //add(~divisor, 1) replaced if no - operator
    if (dividend == INT32_MIN) {
        divident_a = INT32_MAX;
        additional = 1;
    }

    //calculate length
    int cnt = 0, t = divident_a;
    int invert = 0;
    while (t > 0) {
        invert <<= 1;
        invert |= t & 0x1;
        t >>= 1;
        cnt++;
    }

    //模拟除法
    int quotient = 0;
    int remainder = 0;
    while (cnt-- > 0) {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert >>= 1;
        quotient <<= 1;
        if (remainder >= divisor_a) {
            quotient |= 0x1;
            remainder -= divisor_a;
        }
    }
    //处理越界的情况
    if (additional) {
        if (remainder + 1 >= divisor_a) {
            quotient += 1;
            remainder = remainder + 1 - divisor_a;
        } else {
            remainder += 1;
        }
    }

    //求余数的符号
    if (dividend < 0) {
        return add(~remainder, 1);
        //return (int)-remainder;
    }
    return remainder;
}


int Arithmetic::divide_long(int dividend1, int divisor1) {
    // zero resovle
    if (divisor1 == 0) throw runtime_error("divided by zero");
    if (dividend1 == 0) return 0;

    //对被除数和除数取绝对值
    long a = (long) dividend1, b = (long) divisor1;
    long dividend = a < 0 ? -a : a;
    long divisor = b < 0 ? -b : b;
    //获得被除数的反序 比如dividend=101011 invert=1110101,invert最高位会多一个1,
    //这是为了防止dividend=1010,则直接反转为0101,这个时候原来的最低位的0就会丢失
    long invert = 2;
    while (dividend) {
        invert |= dividend & 0x1;
        invert = invert << 1;
        dividend = dividend >> 1;
    }
    long quotient = 0;
    long remainder = 0;
    while (invert > 1)//排除最高位的1
    {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert = invert >> 1;
        quotient = quotient << 1;
        if (remainder >= divisor) {
            quotient |= 0x1;
            remainder -= divisor;
        }
    }

    //求商的符号
    if ((a ^ b) < 0) {//negtive
        return (int) -quotient;
    } else return (int) quotient;
}

int Arithmetic::remainder_long(int dividend1, int divisor1) {
// zero resovle
    if (divisor1 == 0) throw runtime_error("divided by zero");
    if (dividend1 == 0) return 0;

    //对被除数和除数取绝对值
    long a = (long) dividend1, b = (long) divisor1;
    long dividend = a < 0 ? -a : a;
    long divisor = b < 0 ? -b : b;
    //获得被除数的反序 比如dividend=101011 invert=1110101,invert最高位会多一个1,
    //这是为了防止dividend=1010,则直接反转为0101,这个时候原来的最低位的0就会丢失
    long invert = 2;
    while (dividend) {
        invert |= dividend & 0x1;
        invert = invert << 1;
        dividend = dividend >> 1;
    }
    long quotient = 0;
    long remainder = 0;
    while (invert > 1)//排除最高位的1
    {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert = invert >> 1;
        quotient = quotient << 1;
        if (remainder >= divisor) {
            quotient |= 0x1;
            remainder -= divisor;
        }
    }

    //求余数的符号
    if (a < 0) {
        return add(~(int) remainder, 1);
        //return (int)-remainder;
    }
    return (int) remainder;
}


//求商
int Arithmetic::divideEx(int a, int b) {
    //对被除数和除数取绝对值
    int dividend = a < 0 ? add(~a, 1) : a; //无法处理min值
    int divisor = b < 0 ? add(~b, 1) : b;
    //获得被除数的反序 比如dividend=101011 invert=1110101,invert最高位会多一个1,
    //这是为了防止dividend=1010,则直接反转为0101,这个时候原来的最低位的0就会丢失
    int invert = 2; // 可能会溢出
    while (dividend) {
        invert |= dividend & 0x1;
        invert = invert << 1;
        dividend = dividend >> 1;
    }
    int quotient = 0;
    int remainder = 0;
    while (invert > 1)//排除最高位的1
    {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert = invert >> 1;
        quotient = quotient << 1;
        if (remainder >= divisor) {
            quotient |= 0x1;
            remainder = subtract(remainder, divisor);
        }
    }
    //求商的符号
    if ((a ^ b) < 0) {
        quotient = add(~quotient, 1);
    }
    return quotient;
}

//求余
int Arithmetic::remainderEx(int a, int b) {
    //对被除数和除数取绝对值
    int dividend = a < 0 ? add(~a, 1) : a;
    int divisor = b < 0 ? add(~b, 1) : b;
    //获得被除数的反序 比如dividend=101011 invert=1110101,invert最高位会多一个1,
    //这是为了防止dividend=1010,则直接反转为0101,这个时候原来的最低位的0就会丢失
    int invert = 2;
    while (dividend) {
        invert |= dividend & 0x1;
        invert = invert << 1;
        dividend = dividend >> 1;
    }
    int quotient = 0;
    int remainder = 0;
    while (invert > 1)//排除最高位的1
    {
        remainder = remainder << 1;
        remainder |= invert & 0x1;
        invert = invert >> 1;
        quotient = quotient << 1;
        if (remainder >= divisor) {
            quotient |= 0x1;
            remainder = subtract(remainder, divisor);
        }
    }
    //求商的符号
    if (a < 0) {
        remainder = add(~remainder, 1);
    }
    return remainder;
}

//tests
int main() {
    Arithmetic a;
    cout << a.add(INT32_MAX - 1, 1) << endl;
    cout << a.subtract(INT32_MIN, INT32_MIN + 1) << endl;

    cout << a.multiply_bf(INT32_MIN, 1) << endl;
    cout << a.multiply_bf(1, INT32_MIN) << endl;
    cout << a.multiply_bf(-INT32_MIN / 2, 2) << endl;
    cout << a.multiply_bf(INT32_MAX, 1) << endl;
    cout << a.multiply_bf(300, 22) << endl;
    cout << a.multiply_bf(300, 0) << endl;
    cout << "++++++++++++++++++++++++++++++++++" << endl;

    cout << a.multiply_rpa(INT32_MIN, 1) << endl;
    cout << a.multiply_rpa(1, INT32_MIN) << endl;
    cout << a.multiply_rpa(-INT32_MIN / 2, 2) << endl;
    cout << a.multiply_rpa(INT32_MAX / 2, 2) << endl;
    cout << a.multiply_rpa(300, 22) << endl;
    cout << a.multiply_rpa(300, 0) << endl;

    cout << "++++++++++++++++++++++++++++++++++" << endl;
    cout << a.multiply(INT32_MIN, 1) << endl;
    cout << a.multiply(1, INT32_MIN) << endl;
    cout << a.multiply(-INT32_MIN / 2, 2) << endl;
    cout << a.multiply(INT32_MAX, 1) << endl;
    cout << a.multiply(300, 22) << endl;
    cout << a.multiply(300, 0) << endl;
    cout << "++++++++++++++++++++++++++++++++++" << endl;
    cout << a.divide_bf(INT32_MIN, 113123) << endl;
    cout << a.divide_bf(-11, 2) << endl;
    cout << "++++++++++++++++++++++++++++++++++" << endl;
    cout << INT32_MIN % 113123 << " " << -11 % 2 << endl;
    cout << a.remainder_bf(INT32_MIN, 113123) << endl;
    cout << a.remainder_bf(-11, 2) << endl;
    cout << "++++++++++++++++++++++++++++++++++" << endl;
//    cout << a.divideEx(INT32_MIN, 1) << endl;
    cout << a.divideEx(-11313, 33) << endl;
    cout << a.divideEx(INT32_MAX, 1) << endl;
    cout << INT32_MIN / 2 << " " << -11313 / 33 << endl;
    cout << "++++++++++++++divide_long+++++++++++++" << endl;
    cout << a.divide_long(INT32_MIN, 2) << endl;
    cout << a.divide_long(-11313, 33) << endl;
    cout << a.divide_long(INT32_MAX, 1) << endl;
    cout << a.divide_long(INT32_MIN, -1) << endl;
    cout << "++++++++++++++divide+++++++++++++" << endl;
    cout << a.divide(4, 2) << endl;
    cout << a.divide(INT32_MIN, 2) << endl;
    cout << a.divide(INT32_MIN, INT32_MIN) << endl;
    cout << a.divide(-11313, 33) << endl;
    cout << a.divide(INT32_MAX, 1) << endl;
    cout << a.divide(INT32_MIN, -1) << endl;
    cout << "++++++++++++++remainder_long+++++++++++++" << endl;
    cout << a.remainder_long(INT32_MIN, 2) << endl;
    cout << a.remainder_long(-11313, 33) << endl;
    cout << a.remainder_long(INT32_MAX, 1) << endl;
    cout << a.remainder_long(INT32_MIN, -1) << endl;
    cout << INT32_MIN % 2 << " " << -11313 % 33 << endl;
    cout << "++++++++++remaind++++++++++++" << endl;
    cout << a.remaind(INT32_MIN, 2) << endl;
    cout << a.remaind(-11313, 33) << endl;
    cout << a.remaind(INT32_MAX, 1) << endl;
    cout << a.remaind(INT32_MIN, -1) << endl;
    cout << INT32_MIN % 2 << " " << -11313 % 33 << endl;
    cout << "++++++++++++++++++++++++++++++++++" << endl;
    cout << INT32_MAX * 2 << endl;
    cout << -300 % -10 << "\t" << -300 / -10 << endl;
    return 0;
}
