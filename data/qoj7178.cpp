// created time: 2026-09-12 15:24:00
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,l[200005],r[200005];

vector<tuple<int,int,int>>vec;
vector<pair<int,int>>ans;
void procedure(){
	n=read(),m=read();
	int L0 = 2, R0 = n+m;
	int L1 = -m+1, R1 = n-1;
	// line 0: y = -x + [2, n+m]
	// line 1: y =  x + [-m+1, n-1]

	// y = -x + i
	// y = x + j
	// x = (i-j)/2
	// y = (i+j)/2
	auto merge = [&](int i,int j){
		// cout<<"was "<<i<<" "<<j<<endl;
		assert((~i^j)&1);
		int x = (i-j)/2, y = (i+j)/2;
		// cout<<"merging "<<x<<" "<<y<<endl;
		assert(1 <= x && x <= m && 1 <= y && y <= n);
		ans.pb(y,x);
	};
	// cout<<"shabi"<<endl;
	{
		for(int i=L0;i<=R0;i+=2){
			// 2 <= i-j <= 2*m
			// 2 <= i+j <= 2*n

			// i-2*m <= j && j <= i-2
			// 2-i <= j && j <= 2*n-i
			
			int l = max({L1, i-2*m, 2-i}), r = min({R1, i-2, 2*n-i});
			vec.pb(l,r,i);
		}
		sort(vec.begin(), vec.end(), greater<>());
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;

		for(int i=L1+((L0^L1)&1);i<=R1;i+=2){
			// cout<<"prepare for "<<i<<endl;
			while(!vec.empty() && get<0>(vec.back()) <= i) q.push({get<1>(vec.back()),get<2>(vec.back())}),vec.pop_back();
			while(!q.empty() && q.top().fi < i) q.pop();
			if(!q.empty()){
				merge(q.top().se, i);
				q.pop();
			}
		}
	}

	{
		for(int i=L0+1;i<=R0;i+=2){
			// 2 <= i-j <= 2*m
			// 2 <= i+j <= 2*n

			// i-2*m <= j && j <= i-2
			// 2-i <= j && j <= 2*n-i
			
			int l = max({L1, i-2*m, 2-i}), r = min({R1, i-2, 2*n-i});
			vec.pb(l,r,i);
		}
		sort(vec.begin(), vec.end(), greater<>());
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;

		for(int i=L1+((L0^L1^1)&1);i<=R1;i+=2){
			// cout<<"prepare for "<<i<<endl;
			while(!vec.empty() && get<0>(vec.back()) <= i) q.push({get<1>(vec.back()),get<2>(vec.back())}),vec.pop_back();
			while(!q.empty() && q.top().fi < i) q.pop();
			if(!q.empty()){
				merge(q.top().se, i);
				q.pop();
			}
		}
	}

	printf("%d\n", (int)ans.size());
	for(auto [x,y]: ans)
		printf("%d %d\n",x,y);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}