#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * 暴力法为O(n^4)
 *
 * 技巧法O(n^2logn)
 *
 * 细致分析后,可以发现找到bc最关键, 以b为坐标原点平移所点后,计算所有点的极角,并按极角来排序.
 * 记录一个跨越为90度的窗口, 这样我们可以找到所有以b为起点以其余每个点为端点的bc时可取值个数.
 * 之后循环遍历所有的可能BC边, 简单相乘即可得到可能的数目.(注意去重)
 *
 * 我们称这类问题为第六类问题
 * 即涉及到专业知识(如闭型.数论,向量等),模拟题,多个角度(换个角度, 直觉, 如果你没有好的直觉, 那只能多试试做深搜)来考虑问题
 */

const int MAXN = 2510;

void mod(int &x, const int M) {
    while (x >= M) {
        x -= M;
    }
    while (x < 0) {
        x += M;
    }
}

struct Point {
    int x, y;

    Point() {
        x = y = 0;
    }

    Point(int xx, int yy) {
        x = xx;
        y = yy;
    }
};

Point operator-(const Point &A, const Point &B) {
    return Point(A.x - B.x, A.y - B.y);
}

/**
 * 是否在x轴上半部分或者x轴的正半部.
 * true 为上半部, false 为下半部
 */
bool where(const Point &A) {
    return (A.y > 0 || (A.y == 0 && A.x > 0));
}

/**
 * 两个向量OA, OB的叉积.
 * 为正说明前者需要正向右手螺旋(从x正轴向y正轴旋转的方向,即逆时针方向), 旋转小于180度即可到达b, 在x轴同侧下即a<b
 * 为负说明前者要负向右手螺旋,旋转小于180度即可到达b, 在x轴同侧下即a>b
 * 为0则说明ab共线.
 *
 * 叉积的正负说明位置, 0说明共线; 点积的正负说明夹角的锐与钝, 为0说明垂直.
 */
int det(const Point &A, const Point &B) {
    return A.x * B.y - A.y * B.x;
}

/**
 * 比较极角大小
 */
bool cmpAngles(const Point &A, const Point &B) {
    bool whA = where(A), whB = where(B);
    if (whA != whB) {
        return whA;
    }
    return det(A, B) > 0;
}

/**
 * 比较函数
 */
bool cmp(const pair<Point, int> &A, const pair<Point, int> &B) {
    return cmpAngles(A.first, B.first);
}

/**
 * 符号函数
 */
int sgn(int x) {
    if (x > 0) {
        return 1;
    }
    if (x == 0) {
        return 0;
    }
    if (x < 0) {
        return -1;
    }
}


/**
 * 点积
 * 为0则说明垂直.
 */
int cross(const Point &A, const Point &B) {
    return A.x * B.x + A.y * B.y;
}

bool goodAngle(const Point &A, const Point &B) {
    return det(A, B) < 0 && cross(A, B) >= 0;
}


int cntLeft[MAXN][MAXN];
Point a[MAXN]; //store the point
int n; //how many point

/**
 * 距离计算
 */
int dist(int st, int fin, const int M) {
    if (st <= fin) {
        return fin - st;
    }
    else {
        return M - st + fin;
    }
}

/**
 * 向量AB, 转到向量AC是否是以逆时针方向; 或者C是否在AB的左侧
 * 1: 逆时针
 * -1:顺时针
 * 0: 共线三点,无法判断或者不需要旋转
 * 内容即为AB与AC的叉积
 */
int cw(const Point &A, const Point &B, const Point &C) {
    return sgn(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

/**
 * brute force
 */
int brute() {
    int res = 0;
    for (int A = 0; A < n; A++) {
        for (int B = 0; B < n; B++) {
            for (int C = 0; C < n; C++) {
                for (int D = 0; D < n; D++) {
                    if (A == B || A == C || A == D || B == C || B == D || C == D) {
                        continue;
                    }
                    //共线检测,由叉积可得.
                    if (cw(a[B], a[C], a[A]) == 0 || cw(a[B], a[C], a[D]) == 0) {
                        continue;
                    }
                    //前者是同侧的检查; 后者是左右的AD的检查, 即A必须在BC的右边.
                    if (cw(a[B], a[C], a[A]) != -cw(a[B], a[C], a[D]) || cw(a[B], a[C], a[A]) != -1) {
                        continue;
                    }
                    //是否为锐直角.
                    if (cross(a[C] - a[B], a[A] - a[B]) >= 0 && cross(a[B] - a[C], a[D] - a[C]) >= 0) {
                        //cerr << A << " " << B << " " << C << " " << D << endl;
                        res++;
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    freopen("/Users/Qingwei/Documents/workspace/Clion/TheLetterN/input.txt", "r", stdin);

    //input
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        for (int j = 0; j < i; j++) {
            if (a[j].x == a[i].x && a[j].y == a[i].y) {
                assert(false);
            }
        }
    }


    //resolve.
    for (int it = 0; it < n; it++) {
        //sort as the angle.
        vector<pair<Point, int>> v;
        for (int j = 0; j < n; j++) {
            if (it == j) {
                continue;
            }
            v.push_back(make_pair(a[j] - a[it], j));
        }

        sort(v.begin(), v.end(), cmp);

        //find the good angle and fill in the table.
        int u = 0;
        for (int i = 0; i < v.size(); i++) {
            //fin the first legal d.
            int j = i + 1;
            while (j < v.size() && where(v[i].first) == where(v[j].first) && det(v[i].first, v[j].first) == 0) {
                j++;
            }
            j--; //less than the fist legal one.

            if (u >= i && u <= j) {
                u = j + 1;
                mod(u, v.size());
            }

            //find the 90angle, 由于会占到3n/4的复杂度, 所以此种执行的复杂度为O(n^3), 可以通过利用上次
            //查找的结果,即上一个查找的所有结果通过变换都是这次查找的合法情况,
            //末端加上新加入的点,开始端查找第一个合格的angle, 减去中间跳跃的情况,即可获得新的结果窗口.
            //这样复杂度便为O(n^2), 整体最高复杂度为O(n^2log(n))
            while (u != i && !goodAngle(v[i].first, v[u].first)) {
                u++;
                mod(u, v.size());
            }
            int res = dist(u, i, v.size());
            for (int k = i; k <= j; k++) {
                cntLeft[it][v[k].second] = res;
            }
            i = j;
        }
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                ans += cntLeft[i][j] * cntLeft[j][i];
            }
        }
    }

    cout << ans / 2 << endl;
    //cerr << brute() << endl;
    return 0;
}