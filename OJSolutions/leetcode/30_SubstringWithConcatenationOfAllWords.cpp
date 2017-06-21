#include <iostream>
#include "../general.h"

using namespace std;

//O(nhl), 分析见Java version
vector<int> findSubstring(string s, vector<string> &words) {
    unordered_map<string, int> counts;
    for (string word : words)
        counts[word]++;
    int n = s.length(), num = words.size(), len = words[0].length();
    vector<int> indexes;
    for (int i = 0; i < n - num * len + 1; i++) {
        unordered_map<string, int> seen;
        int j = 0;
        for (; j < num; j++) {
            string word = s.substr(i + j * len, len);
            if (counts.find(word) != counts.end()) {
                seen[word]++;
                if (seen[word] > counts[word])
                    break;
            }
            else break;
        }
        if (j == num) indexes.push_back(i);
    }
    return indexes;
}

// author analyze:
// travel all the words combinations to maintain a window
// there are wl(word len) times travel
// each time, n/wl words, mostly 2 times travel for each word
// one left side of the window, the other right side of the window
// so, time complexity O(wl * 2 * N/wl) = O(2N)
// including hash, the complexity is O(nl+hl^2), 因为l小于n多, 所以好于O(nhl)的算法.
/**
 * 依次HASH匹配字符串, 维护一个匹配到的滑窗, 使用双指针, 不匹配或者匹配过多次则左指针移, 匹配右指针移, 直到遇到所有的match
 * 由于以l为单位进行移动, 所以只找到整倍l开始位置的匹配串.
 * 所以要以开始位置对l的取模可能的值进行枚举,l次.
 * O(nl + hl^2) - better or worse than above depends on l's and n's size.
 * n: words cnt; l: word length; h: the source string len;
 */
vector<int> findSubstring_fast(string S, vector<string> &words) {
    vector<int> ans;
    int h = S.size(), n = words.size();
    if (h <= 0 || n <= 0) return ans;

    // init word occurence
    unordered_map<string, int> dict;
    for (int i = 0; i < n; ++i) dict[words[i]]++; //(n*l)

    // travel all sub string combinations, O(h*l^2)
    int l = words[0].size();
    for (int i = 0; i < l; ++i) {//因为是整体以l为单位进行移动, 所以设定可能的检查位置.
        int left = i, count = 0;
        unordered_map<string, int> tdict;
        for (int j = i; j <= h - l; j += l) { //O(l*h/l = h)
            string str = S.substr(j, l);
            // a valid word, accumulate results
            if (dict.count(str)) {//O(h*l)
                tdict[str]++;
                if (tdict[str] <= dict[str])
                    count++;
                else {
                    // a more word, advance the window left side possiablly
                    while (tdict[str] > dict[str]) {
                        string str1 = S.substr(left, l);
                        tdict[str1]--;
                        if (tdict[str1] < dict[str1]) count--;
                        left += l;
                    }
                }
                // come to a result
                if (count == n) {
                    ans.push_back(left);
                    // advance one word
                    tdict[S.substr(left, l)]--;
                    count--;
                    left += l;
                }
            }
                // not a valid word, reset all vars
            else {
                tdict.clear();
                count = 0;
                left = j + l;
            }
        }
    }

    return ans;
}

int main() {

#ifdef _DEBUG
    time_t begin_t = clock();
    freopen("/Users/Qingwei/Documents/workspace/Clion/OJSolutions/input.txt", "r", stdin);
#endif


#ifdef _DEBUG
    cerr << "**********************" << endl;
    cerr << float(clock() - begin_t) / CLOCKS_PER_SEC << " seconds" << endl;
#endif

    return 0;
}