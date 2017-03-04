/**
 * Inversion can be calculated in O(nlogn) too, using BIT. The tester's code follows this approach.
 *
 * 对于这个算法的整体思想理解如上:
 * 逆序处理, 对于每出现的一个数, 将所有比他大的数出现的逆序加1,并存一个数组里; 当他出现时直接从数组里面读.
 * 如此这样的复杂度为O(n^2)
 *
 * 而下面的算法的处理方式, 并没有将所有大于他的数逆序加1, 而是采用了逆序累加的方法,
 * 每次更新至少前进一个2进制位, 详细见upd method,
 * 这样其复杂度就为O(log n)
 *
 * 对于查找也是采用累加的方法, 每次至少前进一个2进制位, 详细见 get_sum method, 这样其复杂度就为O(log n)
 * 如此整个的复杂度就为O(nlog n)
 *
 * 逆序数组中的每位代表的当前数字的搜索与逆序累加的起点, 下标是指要查询的数字, 而其值只是用于累加, 本身并没有特别意义.
 * 整个过程,我们可以保证在计算逆序时只计算了小于它的值, 因为它是从本位减少.
 *
 * 对于事情的本质, 并没有完全吃透, 只知道可行.
 * 现在可理解事情的本质是将两个O(n),O(1)的操作转化成了两个O(nlogn)的操作.
 * 应用范围: 可用于计算逆序. (这是小于逆序, 对于大于逆序同样适用BIT, 实现上不过将upd与get_sum两个方法反过来, 证明过程类似.)
 */

#include <iostream>

using namespace std;

const int maxN = 2e5 + 5;

int n, a[maxN], ans, T, k;
int bit[maxN];
int invalid;

void del() { //重置变量
    for (k = 0; k < maxN; k++)
        bit[k] = 0;
    ans = 0;
    invalid = 0;
}


/**
 * 从本位开始, 循环对于加上最低有效位(即不为0)位后数的逆序加1, 直到大于n(下面的实现中为maxN, 为了写的方便, 由于有多个测试用便;
 * 我们可以用n, 只不过在每个测试用例时, 动态生成数组与初始化数组).
 *
 * 如何保证在大数出现的时候会正确贡献逆序?
 * 即对于逆序累加时的唯一性(对于这些点,只会累加到一次)与必然性(即一定会累加到这个比它小的值), 我们可以从以下角度来思考,
 * 即这个数肯定会落在我们所选择逆序加1的数(我们称之为锚点)的其中两个中间, 而累加的过程是不断减去最低有效位,
 * 而这个数必然会在左锚点的非有效位上加上若干1, 而累加的过程则会减去他们,故会累加到左锚点. 对于正好在左右锚点上的,
 * 则正好从本位开始时就会累加到, 至此必然性得证.
 *
 * 细心我们分发现更新过程中, 1一直在减少, 至少不增; 而累加过程的1的个数则在一直减少而且严格递减的; 即由此可以证明,
 * 一但找到一个锚点后,便不会再相遇. 唯一性得证.
 *
 */
//更新可能出现的变量的逆序数.
void upd(int x) {
    for (k = x; k < maxN; k += (k & (-k))) //因为只会对于已经出现的更大的数目才会产生逆序.
        bit[k]++;
}


/**
 * 从本位开始, 累加逆序, 其中的每一个元素为减去最低有效位(即不为0)位后数的逆序, 直到等于0
 */
//得到逆序数 of x
int get_sum(int x) {
    int p = 0;
    for (k = x; k > 0; k -= (k & (-k))) //(k & -k)是得到k的最低2进制位,奇数为1,偶数为不为0的最低位所代表的数字.
        p += bit[k];

    return p;
}

void new_years_chaos() {
    scanf("%d", &T);
    while (T--) {
        del();
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        for (int i = n - 1; i >= 0; i--) {
            int sum = get_sum(a[i]);
            if (sum > 2) invalid++;
            ans += sum;
            upd(a[i]);
        }

        if (invalid > 0) printf("Too chaotic\n"); else printf("%d\n", ans);
    }
}

