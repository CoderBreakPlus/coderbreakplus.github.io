// created time: 2026-09-22 16:35:08
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2005;
int n, m, q;
bitset <N> bs[N], bef, base;
typedef pair <int, int> pii;
set <pii> s, ans;
int cnt[N];
void del(int p) {
	auto it = s.lower_bound({cnt[p], p});
	auto itl = prev(it), itr = next(it);
	if(itl != s.begin()) {
		int p1 = (*itl).second, p2 = (*it).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.erase({min(p1, p2), max(p1, p2)});
		}
	}
	if(itr != s.end()) {
		int p1 = (*it).second, p2 = (*itr).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.erase({min(p1, p2), max(p1, p2)});
		}
	}
	if(itl != s.begin() && itr != s.end()) {
		int p1 = (*itl).second, p2 = (*itr).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.insert({min(p1, p2), max(p1, p2)});
		}
	}
	s.erase(it);
}
void add(int p) {
	s.insert({cnt[p], p});
	auto it = s.lower_bound({cnt[p], p});
	auto itl = prev(it), itr = next(it);
	if(itl != s.begin() && itr != s.end()) {
		int p1 = (*itl).second, p2 = (*itr).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.erase({min(p1, p2), max(p1, p2)});
		}
	}
	if(itl != s.begin()) {
		int p1 = (*itl).second, p2 = (*it).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.insert({min(p1, p2), max(p1, p2)});
		}
	}
	if(itr != s.end()) {
		int p1 = (*it).second, p2 = (*itr).second;
		if((bs[p1] & bs[p2]) != bs[p1]) {
			ans.insert({min(p1, p2), max(p1, p2)});
		}
	}
}
signed main(void) {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i ++) {
    	s.insert({0, i});
    }
    while (q --) {
    	int a, l, r;
    	cin >> a >> l >> r;
    	base.set();
    	base >>= (2005 - (r - l + 1));
    	base <<= l;
    	del(a);
    	bs[a] ^= base;
    	cnt[a] = bs[a].count();
    	add(a);
    	if(ans.size()) {
    		auto [x1, x2] = (*ans.begin());
    		auto now = (bs[x1] ^ bs[x2]);
    		auto t = (bs[x1] & now);
    		int y1 = t._Find_first();
    		t = (bs[x2] & now);
    		int y2 = t._Find_first();
    		cout << min(x1, x2) << ' ' << min(y1, y2) << ' ' << max(x1, x2) << ' ' << max(y1, y2) << endl;
    	}
    	else cout << -1 << endl;
    }
    return 0;
}
