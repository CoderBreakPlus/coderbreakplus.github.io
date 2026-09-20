// created time: 2026-09-19
// Solved by BreakPlus
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = (a_); i_ <= (b_); ++i_)
#define mid ((L+R) >> 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
using ll = long long;
using pii = pair<int,int>;
using ull = unsigned long long;
const int inf = 0x3f3f3f3f;
const ll inf64 = 0x3f3f3f3f3f3f3f3fll;
int in(void) { int x; scanf("%d", &x); return x; } ll inl(void) { ll x; scanf("%lld", &x); return x; }
void out(int x) { printf("%d ", x); } void outln(int x) { printf("%d\n", x); }
void out(unsigned x) { printf("%u ", x); } void outln(unsigned x) { printf("%u\n", x); }
void out(ll x) { printf("%lld ", x); } void outln(ll x) { printf("%lld\n", x); }
void out(ull x) { printf("%llu ", x); } void outln(ull x) { printf("%llu\n", x); }
template<typename T, typename U> void chkmax(T &a, const U &b) { if(b > a) a = b; } 
template<typename T, typename U> void chkmin(T &a, const U &b) { if(b < a) a = b; } 
const int kN = 205000;
int n;
int main() { 
	multiCase() {
		n = in(); vector<int> p(n + 1);
		_rep(i,1,n) p[in()]=1;
		bool flg = 1;
		_rep(i,(n+1)/2,n)flg&=p[i];
		puts(flg?"1":"0");
		// for(auto &u : p) u = in();
		// int L = 1, R = n, ans = 0;
		// while(L <= R) {
		// 	int ocnt = 0; 
		// 	set<int> S;
		// 	for(auto &u : p) if(u < mid || S.count(u)) ++ocnt; else S.insert(u);
		// 	bool flg = 1;
		// 	_rep(i,1,n - 1) {
		// 		if(S.size() < 2) { flg = 0; break; }
		// 		int a = *S.begin(), b = *S.rbegin();
		// 		S.erase(b); b %= max(a, 1);
		// 		if(b < mid) ++ocnt; else S.insert(b);
		// 		if(ocnt) --ocnt; else S.erase(S.begin());
		// 	}  
		// 	if(flg) ans = mid, L = mid + 1; else R = mid - 1;
		// }
		// outln(ans);
	}
	return 0;
}