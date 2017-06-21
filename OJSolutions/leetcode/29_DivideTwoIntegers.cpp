#include <iostream>

#define _DEBUG

using namespace std;


class Solution {
public:
    /**
     * 使用long来解决INT32_MIN绝对值无法存储会越界的问题.
     * 模拟2进制的试商除法来实现
     * 因为2进制商不是1就是0, 所以实际上是不存在试商的, 只需要判断大小, 大为1, 小为0
     */
    int divide(int dividend1, int divisor1) {
        // zero resovle
        if (divisor1 == 0) throw runtime_error("divided by zero");
        if (dividend1 == 0) return 0;

        //对被除数和除数取绝对值
        long a = (long) dividend1, b = (long) divisor1;
        long dividend = a < 0 ? -a : a; //无法处理min值
        long divisor = b < 0 ? -b : b;
        //获得被除数的反序 比如dividend=101011 invert=1110101,invert最高位会多一个1,
        //这是为了防止dividend=1010,则直接反转为0101,这个时候原来的最低位的0就会丢失
        long invert = 2; // 可能会溢出
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
        if ((a ^ b) < 0) {
            return (int) -quotient;
        }
        return (int) quotient >= 0 ? (int) quotient : INT32_MAX;
    }

    /**
     * 将INT32_MIN的绝对值拆分成(INT32_MAX + 1) 来解决,先处理前者相除, 然后在余数上+1来处理得到最后的商与余数.
     * 模拟2进制的试商除法来实现
     * 因为2进制商不是1就是0, 所以实际上是不存在试商的, 只需要判断大小, 大为1, 小为0
     */
    int divide_int(int dividend, int divisor) {
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
        } else return quotient < 0 ? INT32_MAX : quotient;

    }
};


int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif
    Solution s;
    cout << s.divide_int(INT32_MIN, -1) << endl
    << s.divide_int(-33, 4) << endl;


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}