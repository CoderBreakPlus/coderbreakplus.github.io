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

vector<pair<int,int>>qry[250005];

struct DS{
	int c[250005];
	void upd(int x,int w){ x++; while(x<=N)c[x]+=w,x+=(x&-x); }
	int qry(int x){ x++; int ret=0; while(x)ret+=c[x],x-=(x&-x); return ret; }

	set<tuple<int,int,int>>S;
	void init(){ S.emplace(1,1e9+1,N+1); }

	void cut(int x){
		auto [l,r,w]=*prev(S.lower_bound({x+1,-1,0}));
		if(l!=x){
			S.erase({l,r,w});
			S.emplace(l,x-1,w),S.emplace(x,r,w);
		}
	}
	void cover(int l,int r,int c){
		// cout<<"at "<<l<<" "<<r<<" "<<c<<endl;
		cut(l),cut(r+1);
		while(1){
			auto it=*S.lower_bound({l,0,0});
			auto [L,R,C]=it;
			// cout<<"deleting "<<L<<" "<<R<<" "<<C<<endl;
			if(L>r)break; S.erase(it);
			upd(C,-(R-L+1));
		}
		S.emplace(l,r,c);
		upd(c,r-l+1);
		// cout<<"upd"<<endl;
	}
}T1,T2;
vector<int> array_operation(vector<int> A, vector<int> B, vector<int> L, vector<int> R){
	N=A.size(),Q=L.size();
	vector<int> ans(Q);
	T1.init(),T2.init();

	for(int i=0;i<Q;i++)
		qry[L[i]].pb(R[i],i);

	for(int i=N-1;i>=0;i--){
		T1.cover(B[i],B[i],i),T2.cover(A[i],B[i],i);
		for(auto [r,id]: qry[i])
			ans[id]=(T1.qry(r)==T2.qry(r));
	}
	return ans;
}