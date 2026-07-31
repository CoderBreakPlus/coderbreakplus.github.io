// created time: 2026-07-31 13:03:51
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

int n,q;
char s[500005];

namespace A{
	int x[500005],y[500005],buc[500005],sa[500005],rk[500005],ht[500005],m;
	int f[20][500005];

	int query(int x,int y){
		assert(x!=y);
		if((x=rk[x])>(y=rk[y]))swap(x,y);
		int p=lg2(y-x++);
		return min(f[p][x],f[p][y-(1<<p)+1]);
	}
	void init(){
		int m=256;
		memset(buc,0,sizeof(buc));
		for(int i=1;i<=n;i++)buc[x[i]=s[i]]++;
		for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
		for(int i=n;i>=1;i--)sa[buc[x[i]]--]=i;

		for(int p=1;p<=n;p<<=1){
			int c=0;
			for(int i=n-p+1;i<=n;i++)y[++c]=i;
			for(int i=1;i<=n;i++)
				if(sa[i]>p) y[++c]=sa[i]-p;

			memset(buc,0,sizeof(buc));
			for(int i=1;i<=n;i++) buc[x[i]]++;
			for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
			for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];

			swap(x,y);
			m=x[sa[1]]=1;
			for(int i=2;i<=n;i++)
				if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+p]==y[sa[i-1]+p]) x[sa[i]]=m;
				else x[sa[i]]=++m;
		}

		for(int i=1;i<=n;i++) rk[sa[i]]=i;
		for(int i=1,k=0;i<=n;i++){
			if(rk[i]==1)continue;
			if(k)k--;
			while(s[i+k]==s[sa[rk[i]-1]+k])k++;
			ht[rk[i]]=k;
		}

		for(int i=1;i<=n;i++) f[0][i]=ht[i];
		for(int i=1;(1<<i)<=n;i++)
			for(int j=1;j<=n-(1<<i)+1;j++)
				f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
	}
}
int rad[500005];
set<int>S[500005];
int lcp(int x,int y){
	return min({rad[x], rad[y], A.query(x,y)});
}
bool comp(int x,int y){
	int d=lcp(x,y);
	return (d==rad[x]?0:s[x+d]) < (d==rad[y]?0:s[y+d]);
}
namespace B{
	char t[1000005];
	int ext[1000005];
	void init(){
		t[0]='!',t[1]='$';
		for(int i=1;i<=n;i++) t[i*2]=s[i],t[i*2+1]='$';
		t[n*2+2]='@';

		int mid=0,r=0;
		for(int i=1;i<=n;i++){
			if(i<mid+r) ext[i]=min(ext[2*mid-i],mid+r-i);
			while(t[i-ext[i]]==t[i+ext[i]]) ++ext[i];
			if(i+ext[i]>mid+r) mid=i,r=ext[i];
		}
	}
}
int ord[500005];

void procedure(){
	n=read(),q=read();
	scanf("%s",s+1); s[n+1]=0;
	A::init(),B::init();
	for(int i=1;i<=n;i++) ord[i]=i;

	// odd
	for(int i=1;i<=n;i++) rad[i]=B::ext[2*i-1]/2;
	sort(ord+1,ord+n+1,comp);

	// 
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