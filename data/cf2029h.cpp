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
template<typename T>inline void addmod(T &x){ x=min<unsigned>(x,x-mod); }
template<typename T>inline void decmod(T &x){ x=min<unsigned>(x,x+mod); }
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

void mul(int &a, int b){ a=(ull)a*b%mod; }
void upd(int &a, ull b){ a=(a+b)%mod; }

int n,m,p[21][21],q[21][21],r[21][21],s[21][21];
int sp[1<<21],sq[1<<21],sr[1<<21],ss[1<<21],f[1<<21],ex[1<<21];

int calc_p(int x,int y){ return (ull)sp[x^y]*sq[x]%mod*sq[y]%mod; }
int calc_q(int x,int y){ return (ull)sq[x^y]*sp[x]%mod*sp[y]%mod; }

int buc[22][1<<21],pre[22][1<<21];
int g[1<<21],h[1<<21],tmp[1<<21];

void fwt(int *a){
	for(int m=1;m<(1<<n);m<<=1)
		for(int j=0;j<(1<<n);j+=(m<<1))
		for(int k=0;k<m;k++) addmod(a[j+m+k]+=a[j+k]);
}
void ifwt(int *a){
	for(int m=1;m<(1<<n);m<<=1)
		for(int j=0;j<(1<<n);j+=(m<<1))
		for(int k=0;k<m;k++) decmod(a[j+m+k]-=a[j+k]);
}
void DejaVu(int w){
	memcpy(tmp, buc[w], sizeof(tmp));
	ifwt(tmp);
	for(int i=0; i<(1<<n); i++)
		if(__builtin_popcount(i)==w) g[i]=tmp[i];
}
void procedure(){
	n=read(),m=read();
	for(int i=0;i<(1<<n);i++)sp[i]=sq[i]=sr[i]=ss[i]=1;
	
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)
		p[i][j]=q[i][j]=1;
	while(m--){
		int u=read()-1,v=read()-1,P=read(),Q=read();
		P=Q-P;
		p[u][v]=p[v][u]=(ull)P*INV(Q)%mod;
		q[u][v]=q[v][u]=(ull)Q*INV(P)%mod;
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			mul(sp[(1<<i)^(1<<j)],p[i][j]),mul(sq[(1<<i)^(1<<j)],q[i][j]);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)if((j>>i)&1)
			mul(sp[j],sp[j^(1<<i)]),mul(sq[j],sq[j^(1<<i)]);
			
	for(int i=0;i<(1<<n);i++)
		pre[__builtin_popcount(i)][i]=sp[i];
		
	for(int w=0;w<=n;w++) fwt(pre[w]);
	
	f[1]=1;
	
	for(int w=1;w<n;w++){
		DejaVu(w),DejaVu(w-1);
		memcpy(h,g,sizeof(h));
		for(int i=0;i<(1<<n);i++)mul(h[i],sq[i]);
		ifwt(h);
		
		// f[i] exact
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<(1<<n);i++){
			if(__builtin_popcount(i)!=w)continue;
			if(w>1)f[i]=h[i];
			int w=calc_p(i,(1<<n)-1-i);
			ex[i]=INV(mod+1-w);
			int v=(ull)f[i]*w%mod*ex[i]%mod*sp[i]%mod;
			tmp[i]=v;
		}
		fwt(tmp);
		for(int x=0;w+x<=n;x++) for(int i=0;i<(1<<n);i++)
			upd(buc[w+x][i], (ull)tmp[i]*pre[x][i]);
	}
	int ans=0;
	for(int i=1;i+1<(1<<n);i++){
//		cout<<f[i]<<"*"<<INV(ex[i])<<endl;
		upd(ans, (ull)f[i]*ex[i]);
	}
	
	printf("%d\n",ans);
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