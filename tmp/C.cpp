// created time: 2026-06-19 10:19:57
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

int n,q,a[300005],f[20][300005],g[20][300005];
int nxt[300005],stk[300005],tp;
int getmn(int x,int y){ return a[x]<a[y]?x:y; }
int getmx(int x,int y){ return a[x]>a[y]?x:y; }

int qmn(int l,int r){
	l=max(1,l),r=min(r,n);
	if(l>r) return n+1;
	int p=lg2(r-l+1);
	return getmn(f[p][l],f[p][r-(1<<p)+1]);
}
int qmx(int l,int r){
	l=max(1,l),r=min(r,n);
	if(l>r) return n+1;
	int p=lg2(r-l+1);
	return getmx(g[p][l],g[p][r-(1<<p)+1]);
}
int ans[300005];
int seq[300005],pos[300005],t;

int jp[20][300005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(),f[0][i]=g[0][i]=i, nxt[i]=n+1;

	for(int i=1;i<=n;i++){
		while(tp && a[stk[tp]]<a[i]) nxt[stk[tp--]]=i;
		stk[++tp]=i;
	}
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=getmn(f[i-1][j],f[i-1][j+(1<<i-1)]),
			g[i][j]=getmx(g[i-1][j],g[i-1][j+(1<<i-1)]);

	int c=1;
	pos[0]=1;
	for(t=1;c<=n;t++){
		ans[t]=a[c];
		c=qmn(c+1,nxt[c]);
		pos[t]=c;
	}

	for(int i=1;i<=n+1;i++) jp[0][i] = qmn(i+1, nxt[i]);
	for(int i=1;i<=19;i++)
		for(int j=1;j<=n+1;j++)
			jp[i][j]=jp[i-1][jp[i-1][j]];

	while(q--){
		int k=read(),w=read(),i=1,c=1;
		while(i<=w){
			if(i==k){
				printf("%d\n", a[qmx(c,n)]);
				break;
			}else if(i==k-1){
				if(i==w) {printf("%d\n", a[c]);break;}
				c=min(n,nxt[c]),i++;
			}else{
				int up=min(k-2,w);
				for(int o=lg2(up-i);o>=0;o--)
					if(i+(1<<o)<=up && jp[o][c]+k-i-(1<<o)<=n)
						i+=(1<<o), c=jp[o][c];
				if(i==w) {printf("%d\n", a[c]);break;}

				c=qmn(c+1,min(n-k+i+1,nxt[c]));
				if(c+k-i==n+1){
					printf("%d\n", a[n-k+w]);
					break;
				}
				i++;
			}
		}
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