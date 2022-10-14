#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <bits/stdc++.h>
#include "set.hpp"
using namespace std;
int main() {
    int q; cin >> q;
    Set<int> s;
    while(q--) {
        int t, x; cin >> t >> x;
        if(t == 0) {
            s.insert(x);
        } else if(t == 1) {
            s.erase(x);
        } else {
            auto l = s.begin();
            auto r = s.end();
            int v = 0;
            for(int i = 29; i >= 0; i--) {
                int v2 = v | (1 << i);
                auto it = s.lower_bound(v2);
                if(l == it || (it != r && x >> i & 1)) {
                    v = v2;
                    l = it;
                } else {
                    r = it;
                }
            }
            cout << (x^v) << endl;
        }
    }
}
