// created time: 2026-05-04 14:46:16
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
inline int lowbit(int x){ return x&-x; }
int n,m;
int f[1<<16],g[1<<16],g0[1<<16],h[16][1<<16],val[1<<16],e[16][16];
int df[1<<16],dg[1<<16],dg0[1<<16],dh[16][1<<16],dval[1<<16],de[16][16];
int u[100005],v[100005],w[100005];

void procedure(){
	n=read(),m=read();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			e[i][j]=1;
	for(int i=1;i<=m;i++){
		u[i]=read()-1,v[i]=read()-1,w[i]=read();
		e[u[i]][v[i]]=(ull)e[u[i]][v[i]]*(w[i]+1)%mod;
	}
	for(int i=0;i<n;i++){
		h[i][0]=1;
		for(int j=1;j<(1<<n);j++){
			int x=__builtin_ctz(j);
			h[i][j]=(ull)h[i][j^(1<<x)]*e[x][i]%mod;
		}
	}

	g[0]=1;
	for(int i=0;i<(1<<n);i++){
		for(int j=i&(i-1);j;j=(j-1)&i)if(lowbit(j)==lowbit(i)){
			g0[i]=(g0[i]+(ull)(mod-f[j])*g[i^j])%mod;
		}

		int prod=1;
		for(int j=0;j<n;j++)if((i>>j)&1)prod=(ull)prod*h[j][i]%mod;
		f[i]=prod;

		val[0]=1;
		for(int j=i;j;j=(j-1)&i){
			int k=i^j;
			if(k){
				int t=__builtin_ctz(k);
				val[k]=(ull)val[k^(1<<t)]*h[t][i]%mod;
			}
			if(j==i)
				f[i]=(f[i]+(ull)(mod-g0[j])*val[k])%mod;
			else
				f[i]=(f[i]+(ull)(mod-g[j])*val[k])%mod;
		}
		addmod(g[i]=g0[i]+f[i]);
	}

	// cout<<f[(1<<n)-1]<<endl;

df[(1<<n)-1]=1;
for(int i=(1<<n)-1;i>=0;i--){
	// addmod(g[i]=g0[i]+f[i]);
	addmod(dg0[i]+=dg[i]);
	addmod(df[i]+=dg[i]);

	val[0]=1;
	for(int j=i&(i-1);j;j=(j-1)&i){
		int k=(i^j);
		int t=__builtin_ctz(k);
		val[k]=(ull)val[k^(1<<t)]*h[t][i]%mod;
	}
	for(int k=i;;k=(k-1)&i){
		dval[k]=0;
		if(!k)break;
	}
	for(int k=i&(i-1);;k=(k-1)&i){
		int j=i^k;
		if(j==i){
			// f[i]=(f[i]+(ull)(mod-g0[j])*val[k])%mod;
			dg0[j]=(dg0[j]+(ull)(mod-df[i])*val[k])%mod;
			dval[k]=(dval[k]+(ull)(mod-df[i])*g0[j])%mod;
		}else{
			// f[i]=(f[i]+(ull)(mod-g[j])*val[k])%mod;
			dg[j]=(dg[j]+(ull)(mod-df[i])*val[k])%mod;
			dval[k]=(dval[k]+(ull)(mod-df[i])*g[j])%mod;
		}
		if(k){
			int t=__builtin_ctz(k);
			// val[k]=(ull)val[k^(1<<t)]*h[t][i]%mod;
			dval[k^(1<<t)]=(dval[k^(1<<t)]+(ull)dval[k]*h[t][i])%mod;
			dh[t][i]=(dh[t][i]+(ull)dval[k]*val[k^(1<<t)])%mod;
		}else break;
	}

	int prod=1;
	for(int j=0;j<n;j++)if((i>>j)&1)prod=(ull)prod*h[j][i]%mod;

	// f[i]=prod;
	for(int j=0;j<n;j++)if((i>>j)&1)
		dh[j][i]=(dh[j][i]+(ull)df[i]*prod%mod*INV(h[j][i]))%mod;

	for(int j=i&(i-1);j;j=(j-1)&i)if(lowbit(j)==lowbit(i)){
		// g0[i]=(g0[i]+(ull)(mod-f[j])*g[i^j])%mod;
		df[j]=(df[j]+(ull)(mod-dg0[i])*g[i^j])%mod;
		dg[i^j]=(dg[i^j]+(ull)(mod-dg0[i])*f[j])%mod;
	}
}

	for(int i=0;i<n;i++){
		for(int j=(1<<n)-1;j>=1;j--){
			int x=__builtin_ctz(j);
			// h[i][j]=(ull)h[i][j^(1<<x)]*e[x][i]%mod;
			dh[i][j^(1<<x)]=(dh[i][j^(1<<x)]+(ull)dh[i][j]*e[x][i])%mod;
			de[x][i]=(de[x][i]+(ull)dh[i][j]*h[i][j^(1<<x)])%mod;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%llu\n", (ull)de[u[i]][v[i]]*e[u[i]][v[i]]%mod*INV(w[i]+1)%mod*w[i]%mod);
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