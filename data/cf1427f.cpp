// created time: 2026-11-08 18:24:57
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

int n,a[1205];
tuple<int,int,int>pos[405];
int l[405],r[405],col[405],deg[405];
int c;
int stk[1205],tp;
vector<int>vec[1205],E[405];

void procedure(){
	n=read();
	for(int i=1;i<=3*n;i++)a[read()]=1;

	for(int i=1;i<=6*n;i++){
		stk[++tp]=i;
		if(tp>=3&&a[stk[tp]]==a[stk[tp-1]]&&a[stk[tp]]==a[stk[tp-2]])
			pos[++c]={stk[tp-2],stk[tp-1],stk[tp]},tp-=3;
	}
	assert(c==2*n);
	for(int i=1;i<=c;i++){
		auto [x,y,z]=pos[i];
		l[i]=x,r[i]=z,col[i]=a[y];
		vec[z].pb(i);
	}
	tp=0;
	for(int i=1;i<=6*n;i++){
		for(int o:vec[i]){
			while(tp&&l[stk[tp]]>l[o]){
				E[o].pb(stk[tp]);
				deg[stk[tp--]]++;
			}
			stk[++tp]=o;
		}
	}
	int now=0;
	priority_queue<pair<int,int>>q[2];
	for(int i=1;i<=c;i++)
		if(!deg[i])q[col[i]].emplace(E[i].size(),i);
	vector<int>ans;
	for(int i=1;i<=2*n;i++){
		int x=q[now].top().se;q[now].pop();
		ans.pb(x);
		for(int y:E[x]){
			q[col[y]].emplace(E[y].size(),y);
		}
		now^=1;
	}
	reverse(ans.begin(),ans.end());
	for(int i: ans){
		auto [x,y,z]=pos[i];
		printf("%d %d %d\n",x,y,z);
	}
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