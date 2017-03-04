#include <iostream>

using namespace std;

const int MAXN = 1005;  //树中可能的结点个数.

/**
 * node in the palindrome tree.
 */
struct node {
    int next[26];
    // 指向回文扩充的边, 0 为没有
    int sufflink; // suffix edge
    int len; // length
    int num; //添加到这个结点时, 加入的回文串的个数.
};

int len;            // len of the target string.
char s[MAXN];       // the target string
node tree[MAXN];    // the palindrome tree
int num;            // node 1 - root with len -1, node 2 - root with len 0, num, 节点个数
int suff;           // max suffix palindrome, 当前最大的回文串后缀, t
long long ans;      // stat the num of the palindrome of the total string.

bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';

    //find A - the longest.
    while (true) {
        curlen = tree[cur].len; //在最大后缀串中的遍历时的当前长度.
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            break;
        cur = tree[cur].sufflink;
    }
    if (tree[cur].next[let]) {
        suff = tree[cur].next[let]; //get the cur max suffix of p
        return false; //this edge already exist
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].next[let] = num;

    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }

    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].sufflink = tree[cur].next[let];
            //?为什么这个next一定会存在呢? 一定会存在, 最差也就是为空呗, 所以它一定是存在的.
            break;
        }
    }
    tree[num].num = 1 + tree[tree[num].sufflink].num;
    return true;
}

void initTree() {
    num = 2;
    suff = 2;
    tree[1].len = -1;
    tree[1].sufflink = 1;
    tree[2].len = 0;
    tree[2].sufflink = 1;
}

int main() {
    scanf("%s", s);
    len = strlen(s);

    initTree();

    for (int i = 0; i < len; i++) {
        addLetter(i);
        ans += tree[suff].num;
    }
    cout << ans << endl;
    return 0;
}