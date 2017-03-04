// There is nothing in a caterpillar that tells you its going to be a butterfly --------------------- !
#include <iostream>
#include <vector>
using namespace std;

#define rep(i, n) for(int i=0;i<n;i++)
#define ll  long long int
#define pi pair<ll,ll>
#define pii pair<ll,pi>
#define f first
#define mp make_pair
#define mod 1000000007
#define s second
#define pb push_back

int main() {
    string S;
    cin >> S;
    vector<char> ans;
    rep(i, S.length()) {
        if (ans.size() == 0 or S[i] != ans.back()) ans.pb(S[i]);
        else ans.pop_back();
    }
    if (ans.size() == 0) cout << "Empty String";
    else {
        for (auto x:ans) cout << x;
    }
}