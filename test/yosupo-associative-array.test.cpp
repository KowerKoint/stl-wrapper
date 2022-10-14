#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <bits/stdc++.h>
#include "map.hpp"
using namespace std;
using ll = long long;

int main() {
    int q; cin >> q;
    Map<ll, ll> mp;
    while(q--) {
        int op; cin >> op;
        if(op == 0) {
            ll k, v; cin >> k >> v;
            mp[k] = v;
        } else {
            ll k; cin >> k;
            cout << mp[k] << endl;
        }
    }
}
