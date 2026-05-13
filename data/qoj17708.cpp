// created time: 2026-05-13 10:44:13
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
int n,k;
struct sol{
	int op[200005],x[200005],c[200005],m,id[200005],up;
	void ins(int OP,int X,int C){
		op[++m]=OP, x[m]=X, c[m]=C;
	}

	pair<ll,int> solve(ll k){
		priority_queue<ll,vector<ll>,greater<ll>>f;
		priority_queue<ll>g;

		int cnt=0; ll bas=0;
		for(int I=1;I<=m;I++){
			int i=id[I];
			if(op[i]&1){
				f.push(c[i]);
			}else{
				ll A=1e18,B=1e18;
				if(f.size())A=f.top()+c[i]-k;
				if(g.size())B=c[i]-g.top();
				if(min(A,B)<0)
					if(A<B){
						bas+=A,cnt++,f.pop(),g.push(c[i]);
					}else{
						bas+=B,g.pop(),g.push(c[i]);
					}
			}
		}
		return {bas,cnt};
	}
	void init(){
		for(int i=1;i<=m;i++)id[i]=i;
		sort(id+1,id+m+1,[&](int i,int j){
			return x[i]==x[j]?op[i]>op[j]:x[i]<x[j];
		}); 

		int ok=0;
		for(int I=1;I<=m;I++){
			int i=id[I];
			if(op[i]&1){
				ok++;
			}else if(ok) ok--,up++;
		}
	}
}S[2];
void procedure(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		int t=read()-1,x=read(),y=read(),c=read();
		S[t>>1].ins(t,(t>>1)?y:x,c);
	}
	S[0].init();
	S[1].init();

	if(S[0].up+S[1].up<k){
		puts("-1");
		return;
	}

	ll l=0, r=1e10;
	while(l<r){
		ll mid=(l+r+1)>>1;
		if(S[0].solve(mid).se+S[1].solve(mid).se>k) r=mid-1;
		else l=mid;
	}
	ll ans=S[0].solve(l).fi+S[1].solve(l).fi+l*k;

	printf("%lld\n",ans);
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