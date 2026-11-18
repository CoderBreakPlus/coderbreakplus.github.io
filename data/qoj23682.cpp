// created time: 2026-11-18 09:38:29
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

const int N = 200005;
int n,m;
char s[N];
int sum[N],nxt[N],cnt[N];
int f[20][N],bit[2][2*N];

void modify(int *t,int x,int v){
	for(;x<=m;x+=x&-x) chkmin(t[x],v);
}
int query(int *t,int x){
	int ans=n+1;
	for(;x;x-=x&-x) chkmin(ans,t[x]);
	return ans;
}

void procedure(){
	scanf("%s",s+1);
	n=strlen(s+1);
	m=2*n+1;
	sum[0]=n;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+(s[i]==':'?1:-1);

	fill(bit[0],bit[0]+m+1,n+1);
	fill(bit[1],bit[1]+m+1,n+1);
	nxt[n+1]=n+1;
	for(int i=n;i>=0;i--){
		int x=sum[i];
		// '(' 要 sum[j]<x，')' 要 sum[j]>=x。
		nxt[i]=min(query(bit[0],x),query(bit[1],m-x));
		if(s[i]=='(') modify(bit[0],x+1,i);
		if(s[i]==')') modify(bit[1],m-x,i);
	}
	for(int i=n;i>=1;i--){
		int j=nxt[i];
		cnt[i]=(j<=n?cnt[j]+(s[i]!=s[j]):0);
	}

	for(int i=0;i<=n+1;i++) f[0][i]=nxt[i];
	int p=lg2(n);
	for(int k=1;k<=p;k++)
		for(int i=0;i<=n+1;i++)
			f[k][i]=f[k-1][f[k-1][i]];

	int q=read();
	while(q--){
		int l=read(),r=read();
		int st=nxt[l-1],x=st;
		if(st>r){ puts("0"); continue; }
		for(int k=p;k>=0;k--)
			if(f[k][x]<=r) x=f[k][x];
		int ans=1+cnt[st]-cnt[x];
		if(s[x]=='(' ? sum[x]>=sum[r] : sum[x]<sum[r]) ans--;
		printf("%d\n",ans);
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
