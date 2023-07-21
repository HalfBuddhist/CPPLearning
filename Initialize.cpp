#include <iostream>

using namespace std;

/**
 * 在c++中对于变量的初始化,如果是局部变量,则没有隐式的初始化(这点与java是显著性的不同, java是默认的初始化好的),
 * 如果是对于数组的初始化, 如果用代码进行初始化则会增加额外的代码量, 最简单的方法是如下的形式:
 * ar[109][26] = {}, ar[100] = {}
 * 这种没有初始化值的初始化式, 执行的结果是将数组的值全部置为默认初始化值0;
 */
int initialize() {
    int n, i, ans = 0, ar[109][26] = {}, j, flag;
    cin >> n;
    string s;
    for (i = 0; i < n; i++) {
        cin >> s;
        for (j = 0; j < s.size(); j++)
            ar[i][s[j] - 'a']++;
    }
    for (i = 0; i < 26; i++) {
        flag = 0;
        for (j = 0; j < n; j++)
            if (ar[j][i] == 0)flag = 1;
        if (flag == 0)ans++;
    }
    cout << ans << endl;
    return 0;
}