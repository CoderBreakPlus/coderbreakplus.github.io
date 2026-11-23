// created time: 2026-11-23 15:42:31
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

int n,k,w[2000005],c[2000005];
ll C;
ll pool[1<<23],t[1<<22];
int pt;

void solve(int d,int v,int l,int r,ll *s){
	if(l>r)return;
	// cout<<"solve "<<d<<" "<<v<<" "<<l<<" "<<r<<endl;
	// for(int i=0;i<(1<<d);i++) cout<<s[i]<<" "; cout<<endl;
	ll cur=0;
	for(int i=0;i<(1<<d);i++) cur+=s[i];
	if(d==-1){
		for(int i=l;i<=r;i++)printf("%d\n",v);
		return; 
	}

	int p=l-1;
	while(p<r&&cur<C){
		++p;
		if(((w[p]&v)>>d)==(w[p]>>d))cur+=c[p];
	}
	if(cur<C)++p;

	ll *t=pool+pt; pt+=(1<<d);

	for(int i=0;i<(1<<d);i++) t[i]=s[i]+s[i+(1<<d)];
	solve(d-1,v|(1<<d),l,p-1,t);

	for(int i=0;i<(1<<d);i++) t[i]=s[i];
	for(int i=l;i<p;i++)
		if(((w[i]&v)>>d)==(w[i]>>d)) t[w[i]&((1<<d)-1)]+=c[i];
	solve(d-1,v,p,r,t);

	pt-=(1<<d);
}
void procedure(){
	n=read(),k=read(),C=read();
	ll sum=0;
	int ok=n+1;
	for(int i=1;i<=n;i++){
		w[i]=read(),c[i]=read();
		sum+=c[i];
		if(sum>=C&&ok==n+1)ok=i;
	}
	pt+=(1<<k);
	for(int i=1;i<ok;i++)puts("-1"),pool[w[i]]+=c[i];
	solve(k-1,0,ok,n,pool);
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