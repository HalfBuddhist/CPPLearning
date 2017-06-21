//============================================================================
// Name        : Permutation.cpp
// Author      : Wade.Liu
// Version     :
// Copyright   : CSU
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <time.h>

#define maxn 100
#define _DEBUG

using namespace std;

void outp(int p[], int n) //输出一个排列
{
    int i;
    cout << " ";
    for (i = 1; i <= n; i++)
        cout << p[i] << " ";
    cout << endl;
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

void dict(int p[], int n) //字典序法
{
    int i, j;
    outp(p, n);
    i = n - 1;
    while (i > 0) {
        if (p[i] < p[i + 1]) {
            for (j = n; j >= i + 1; j--)
                if (p[i] <= p[j])
                    break;
            swap(p[i], p[j]);
            for (j = n; j >= 1; j--) {
                i += 1;
                if (i >= j)
                    break;
                swap(p[i], p[j]);
            }
            outp(p, n);
            i = n;
        }
        i -= 1;
    };
}

/************************************************************************/
/* function:		中介数判断
 /* parameter:		m-中介数，n-element number
 /************************************************************************/
bool midn(int m[], int n) {
    int k = n - 1;//中介数少一位。
    while (1) {
        m[k] += 1;
        if (m[k] < n - k + 1)
            break;
        m[k] = 0;
        k -= 1;
    }
    int s = 0;
    bool b = false;
    for (k = 1; k <= n;)
        s += m[k++];
    if (s == 0)
        b = true; //中介数到了末尾
    return b;
}

/************************************************************************/
/* function:		递增进位制
 /* parameter:		p-element array, n-element number
 /************************************************************************/
void incr(int p[], int n) {
    int m[maxn]; //middle number array
    int i, j, a;
    for (i = 1; i <= n;)
        m[i++] = 0;
    while (i > 0) {
        for (i = 1; i <= n;)
            p[i++] = 0;//用于存放数据，并同时做为标志位。
        for (i = 1; i <= n; i++) {
            a = m[i] + 1;
            j = n;
            while (j > 0) {
                if (p[j] == 0) {
                    a -= 1;
                    if (a == 0)
                        break;
                }
                j -= 1;
            }
            p[j] = n - i + 1;
        }
        outp(p, n);
        if (midn(m, n) == true)
            break;
    }
}

/************************************************************************/
/* function:		递减进位制法
 /* parameter:		p-element array, n-element number
 /************************************************************************/
void degr(int p[], int n) {
    int i, j;
    while (1) {
        outp(p, n);
        if (p[1] != n) {
            i = 0;
            while (p[++i] != n);
            swap(p[i], p[i - 1]);
        } else {
            i = 1;
            while (i < n) //检验是否是最终的排列。
            {
                if (p[i] != p[i + 1] + 1)
                    break;
                i += 1;
            }
            if (i == n)
                break;

            j = i; //j为第一个不满足的严格降1的前1个
            while (p[i] != p[j] - 1)//找到j的次小数i，因为此时发生了进位，
                i += 1;
            swap(p[i], p[i - 1]);

            for (i = 1; i <= n - j;)
                p[i++] = p[i + j];
            for (i = 1; i <= j; i++)
                p[n - i + 1] = n - i + 1;
        }
    }
}

void conv(int p[], int n) {

    bool *bDirection = new bool[n + 1]; //remember the direction of value n, false-point to left, true-point to right
    memset(bDirection, 0, sizeof(bool) * (n + 1));

    bool flag = true;
    int maxx = -1;
    int position;

    while (true) {
        outp(p, n);
        for (int i = n; i >= 2; i--) {
            if (flag) //from n to 1
            {
                swap(p[i], p[i - 1]);
            } else //from 1 to n
            {
                swap(p[n + 1 - i], p[n + 2 - i]);
            }
            outp(p, n);
        }

        //find the next big and movable element
        for (int i = 1; i <= n; i++) {
            if (bDirection[p[i]] == false) //point to the left
            {
                if (i - 1 >= 1 && p[i - 1] < p[i] && p[i] > maxx) {
                    maxx = p[i];
                    position = i;
                }
            } else //point to the right
            {
                if (i + 1 <= n && p[i + 1] < p[i] && p[i] > maxx) {
                    maxx = p[i];
                    position = i;
                }
            }
        }
        if (maxx == -1) {//均不可以移动，则所有的排列已生成
            break;
        }
        //exchange
        if (bDirection[maxx] == false) //point to the left
        {
            swap(p[position], p[position - 1]);
        } else {
            swap(p[position], p[position + 1]);
        }

        //change the direction of the bigger element
        for (int i = 1; i <= n; i++) {
            if (p[i] > maxx) {
                bDirection[p[i]] = !bDirection[p[i]];
            }
        }

        maxx = -1;
        flag = !flag;
    }

    delete[] bDirection;
}

bool test(int p[], int n) {
    bool b = false;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (p[i] == p[j]) {
                b = true;
                break;
            }
    return b;
}

void Nnum(int p[], int n) {
    while (n > 0) {
        if (test(p, n) == false)
            outp(p, n);
        p[n] += n - 1;
        for (int j = n; j > 1; j--) {
            if (p[j] > n) {
                p[j] %= n;
                p[j - 1] += 1;
                if (p[1] > n) {
                    n = 0;
                    break;
                }
            }
        }
    }
}

/************************************************************************/
/* 递归生成法
 /************************************************************************/

void recu(int p[], int n, int k) {
    if (k == n)
        outp(p, n);
    else {
        for (int i = k; i <= n; i++) {
            swap(p[k], p[i]);
            recu(p, n, k + 1);
            swap(p[k], p[i]);
        }
    }
}

void cyc(int p[], int n, int k) {
    if (k > n)
        outp(p, n);
    else {
        for (int i = 0; i < k; i++) {
            int t = p[1];
            for (int j = 2; j <= k; j++)
                p[j - 1] = p[j];
            p[k] = t;
            cyc(p, n, k + 1);
        }
    }

}

void remo(int p[], int n, int k) {
    bool b;
    if (k > n)
        outp(p, n);
    else {
        for (int i = 1; i <= n; i++) {
            b = false;
            p[k] = i;
            for (int j = 1; j < k; j++)
                if (i == p[j]) {
                    b = true;
                    break;
                }
            if (b == false)
                remo(p, n, k + 1);
        }
    }
}

int main() {

#ifdef _DEBUG
    freopen("src\\in.txt", "r", stdin);
    //freopen("src\\out.txt", "w", stdout);
#endif

    int i, m;
    int p[maxn];
    int n;
    clock_t start, finish;
    cout << "输入排列元素总数n=";
    cin >> n;
    for (i = 1; i <= n; i++)
        p[i] = i;
    cout << "1——字典序法" << endl;
    cout << "2——递增进位数制法" << endl;
    cout << "3——递减进位数制法" << endl;
    cout << "4——邻位交换法" << endl;
    cout << "5——n进制数法" << endl;
    cout << "6——递归生成法" << endl;
    cout << "7——循环移位法" << endl;
    cout << "8——回溯法" << endl;
    cout << "请选择: ";
    cin >> m;
    printf("\n");
    start = clock();
    switch (m) {
        case 1:
            dict(p, n);
            break;
        case 2:
            incr(p, n);
            break;
        case 3:
            degr(p, n);
            break;
        case 4:
            conv(p, n);
            break;
        case 5:
            Nnum(p, n);
            break;
        case 6:
            recu(p, n, 1);
            break;
        case 7:
            cyc(p, n, 1);
            break;
        case 8:
            remo(p, n, 1);
    }
    finish = clock();
    cout << "程序执行时间：" << (double) (finish - start) / CLOCKS_PER_SEC << "秒"
    << endl;
    system("pause");
    return 0;
}
