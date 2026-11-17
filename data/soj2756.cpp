// created time: 2026-11-17 09:52:42
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

int n,m,q,l[200005],c[200005];

struct BIT{
	ll c[200005];
	void upd(ll x,ll w){
		while(x<=m+1){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(int x){
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}B0,B1;

void procedure(){
	n=read(),m=read(),q=read();
	for(int i=0;i<n;i++)l[i]=read();

	for(int i=0;i<m;i++){
		int x=read(),y=read();
		if(x<y)c[x]++,c[y]--;
		else c[x]++,c[0]++,c[y]--;
	}
	for(int i=1;i<n;i++)c[i]+=c[i-1];
	for(int i=0;i<n;i++){
		B0.upd(++c[i],l[i]),B1.upd(c[i],(ll)l[i]*c[i]);
	}

	while(q--){
		int x=read(),v=read();
		B0.upd(c[x],v-l[x]);
		B1.upd(c[x],(ll)(v-l[x])*c[x]);
		l[x]=v;

		// cout<<"#query"<<endl;
		// for(int i=0;i<n;i++){
		// 	cout<<c[i]<<" "<<l[i]<<endl;
		// }
		ll sum0=B0.qry(m+1);
		// cout<<"sum0="<<sum0<<endl;
		ll sum1=B1.qry(m+1);

		int L=1,R=m,pt=0;
		while(L<=R){
			int M=(L+R)>>1;
			if(B0.qry(M)<=sum0-B0.qry(M)){
				pt=M;
				L=M+1;
			}else
				R=M-1;
		}
		// cout<<"pt="<<pt<<endl;
		ll vL=B0.qry(pt),vR=sum0-B0.qry(pt+1);

		// cout<<vL<<" and "<<vR<<endl;

		ll sL=B1.qry(pt);
		ll sR=sum1-B1.qry(pt+1)+(vL-vR)*(pt+1);

		// cout<<"fuck "<<sL<<" "<<sR<<endl;
		printf("%lld\n",sR-sL);
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