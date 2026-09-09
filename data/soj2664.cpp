// created time: 2026-09-08 07:44:55
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
// #ifdef LOCAL
	// #include"grader.cpp"
// #endif
#include"show.h"
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

void init(int c,int t){

}

int rt[200005],N;
vector<int> vec[200005];
int pool[5000005];

struct BIT{
	int *c, sz;
	vector<int> a;
	void upd(int x,int w){
		x = lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
		while(x<=sz){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		x = upper_bound(a.begin(), a.end(), x) - a.begin();
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	void clear(){
		sz = 0, a.clear();
	}
}t[200005];
void upd(int x,int c,int w){
	x++;
	while(x<=N){
		t[x].upd(c,w);
		x+=(x&-x);
	}
}
int qry(int x,int r){
	x++;
	int ret=0;
	while(x){
		ret+=t[x].qry(r);
		x-=(x&-x);
	}
	return ret;
}
vector<int> qr[200005];

int lst[200005];
vector<int> show(int n,int q,vector<int> a,vector<pair<int,int>>ops){
	vector<int>ans(q);
	N=n+2;

	for(int i=1;i<=N;i++){
		int x=i;
		while(x<=N){
			t[x].a.pb(a[i-1]);
			x+=(x&-x);
		}
	}

	int *cur = pool;
	for(int i=1;i<=N;i++){
		sort(t[i].a.begin(), t[i].a.end());
		t[i].a.erase(unique(t[i].a.begin(), t[i].a.end()), t[i].a.end());

		t[i].c = cur;
		cur += (t[i].sz = t[i].a.size());
	}

	for(int i=0;i<q;i++){
		ops[i].fi--,ops[i].se--;
		auto [l,r]=ops[i];
		qr[l].pb(i);
	}

	for(int x=n-1;x>=0;x--){
		if(lst[a[x]]){
			upd(lst[a[x]],a[x],-1);
		}
		upd(x,a[x],1);
		lst[a[x]]=x;

		for(int i:qr[x]){
			auto [l,r]=ops[i];
			int m=r-l+3;
			ans[i]=qry(r,m-1);
			if(ans[i]<qry(r,n))ans[i]++;
		}
	}
	for(int i=0;i<q;i++) ans[i]=ops[i].se-ops[i].fi+3-ans[i];

	for(int i=0;i<=N;i++)qr[i].clear(),t[i].clear();
	memset(pool, 0, sizeof(pool));
	memset(lst, 0, sizeof(lst));
	return ans;
}