// created time: 2026-04-01 19:21:22
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n; ll ans[5000005];

map<int,ll>mx[10005],mn[10005];
int ID[5000005], c;

int id(int x){ if(!ID[x]) ID[x]=++c; return ID[x]; }

int solvemx(int x){
	int i=id(x);
	if(x==0) return i;
	if(x<=1) {
		mx[i][0]=1; // 不能找到
		return i;
	}
	if(!mx[i].empty()) return i;
	int lc=solvemx((x-1)/2), rc=solvemx(x/2);
	for(auto [a,b]: mx[lc]) mx[i][a+x/2+1] += b;
	for(auto [a,b]: mx[rc]) mx[i][a+(x-1)/2+1] += b;
	mx[i][(x-1)/2] ++;
	return i;
}
int solvemn(int x){
	int i=id(x);
	if(x==0) return i;
	if(x<=1) {
		mn[i][0]=1; // 不能找到
		return i;
	}
	if(!mn[i].empty()) return i;
	int lc=solvemn((x-1)/2), rc=solvemn(x/2);
	for(auto [a,b]: mn[lc]) mn[i][a+x/2+1] += b;
	for(auto [a,b]: mn[rc]) mn[i][a+(x-1)/2+1] += b;
	mn[i][x/2] ++;
	return i;
}

void procedure(){
	n=read();
	map<int,int>mp, mp2; mp[n]=1;
	while(!mp.empty()){
		mp2.clear();
		auto add = [&](int u,int v){
			if(u<=1) return;
			mp2[u] += v;
		};
		for(auto [x,w]: mp){
			if(x==2){
				ans[n-1]+=w;
				continue;
			}
			// cout<<"solving "<<x<<" "<<w<<endl;
			add((x-1)/2, w), add(x/2, w);
			int lc=solvemx((x-1)/2), rc=solvemn(x/2);
			// cout<<"splitting: "<<endl;
			for(auto [a,b]: mx[lc]) for(auto [c,d]: mn[rc]){
				// cout<<a<<","<<b<<" "<<c<<","<<d<<" at "<<n-x+a+c+1<<" += "<<b*d*w<<endl;
				ans[n-x+a+c+1] += b*d*w;
			}
			for(int i=1;i<=x/2;i++)
				// cout<<"right "<<i<<" add "<<n-i-1<<" with "<<w<<endl,
				ans[n-i] += w;
			for(int i=1;i<=(x-1)/2;i++)
				// cout<<"left "<<i<<" add "<<n-i-1<<" with "<<w<<endl,
				ans[n-i] += w;
		}
		swap(mp,mp2);
	}
	for(ll i=0;i<=n;i++) printf("%lld ",ans[i]);
	puts("");
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