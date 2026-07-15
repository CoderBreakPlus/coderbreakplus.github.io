// created time: 2026-07-15 16:05:18
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
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
int n,m,a[5000005],b[100005];
int s[100005],t;
ll f[5000005];
i128 ans[100005];

inline i128 calc(int j,int i){
    int w=b[i]-a[j];
    if(w<0) w=-w;
    return f[j]+(i128)w*w*w;
}

void solve(int l,int r,int ql,int qr){
	if(l>r)return;
	int mid=(l+r)>>1;

	ans[mid]=calc(s[ql],mid); int jc=ql;
	for(int i=ql+1;i<=qr;i++){
		i128 now=calc(s[i],mid);
		if(now<=ans[mid])ans[mid]=now,jc=i;
	}
	solve(l,mid-1,ql,jc),solve(mid+1,r,jc,qr);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)f[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();

	for(int i=1;i<=n;i++){
		while(t&&calc(i,t)<calc(s[t],t))t--;
		if(t<m)s[++t]=i;
	}
	solve(1,m,1,t);

	for(int i=1;i<=m;i++){
		string tmp;
		if(!ans[i]) {printf("0 ");continue;}
		while(ans[i]) tmp+='0'+ans[i]%10, ans[i]/=10;
		reverse(tmp.begin(),tmp.end());
		for(char ch:tmp) putchar(ch); putchar(' ');
	}
	puts("");
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