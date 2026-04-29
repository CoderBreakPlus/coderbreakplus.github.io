// created time: 2026-04-29 14:02:55
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
int N,Q;

vector<int>qry[250005];

struct DS{
	int c[250005];
	void upd(int x,int w){ while(x<=n)c[x]+=w,x+=(x&-x); }
	int qry(int x){ int ret=0; while(x)ret+=c[x],x-=(x&-x); }

	set<tuple<int,int,int>>S;
	void init(){ S.emplace(1,1e9,n+1); }

	void cut(int x){
		auto [l,r,w]=*prev(S.lower_bound({x+1,-1,0}));
		if(l!=x){
			S.erase({l,r,w});
			S.emplace({l,x-1,w}),S.emplace({x+1,r,w});
		}
	}
	void cover(int l,int r,int c){

	}
}T1,T2;
vector<int> array_operation(vector<int> A, vector<int> B, vector<int> L, vector<int> R){
	N=A.size(),Q=L.size();
	vector<int> col(Q),ans(Q);
	T1.init(),T2.init();

	for(int i=0;i<Q;i++)
		qry[L[i]].pb(R[i],i);

	for(int i=n-1;i>=0;i--){
		
	}
	return ret;
}