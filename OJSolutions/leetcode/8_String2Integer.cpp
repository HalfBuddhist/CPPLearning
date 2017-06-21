#include <iostream>

using namespace std;

class Solution {
public:
    int myAtoi(string str1) {
        const char *str = str1.c_str();
        return atoi(str);
    }

    int atoi(const char *str) {
        int sign = 1, base = 0, i = 0;
        while (str[i] == ' ') { i++; }
        if (str[i] == '-' || str[i] == '+') {
            sign = 1 - 2 * (str[i++] == '-');
        }
        while (str[i] >= '0' && str[i] <= '9') {
            if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
                if (sign == 1) return INT_MAX;
                else return INT_MIN;
            }
            base = 10 * base + (str[i++] - '0');
        }
        return base * sign;
    }
};

int main() {
    Solution s;
    int a = s.myAtoi("   -1223345");
    cout << a << endl;
    return 0;
}