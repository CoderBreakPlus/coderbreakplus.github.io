// created time: 2026-08-25 10:13:59
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

int n,m;
int fa[2000005];
int code(int i,int j){ return i*(m+1)+j; }

int find(int x){if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}
char s[1005][1005];
int a[1005][1005];

pair<int,int> w[1000005];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)fa[code(i,j)]=code(i,j);

	int t=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			w[++t]={i,j};
		}
	sort(w+1,w+t+1,[&](pair<int,int> A,pair<int,int> B){
		auto [p,q]=A;
		auto [r,s]=B;
		return a[p][q]>a[r][s];
	});

	ll ans=0;
	for(int i=1;i<=t;i++){
		auto [x,y]=w[i];

		// cout<<"link "<<x<<" "<<y<<endl;
		int p=code(x-1,y-1),q=code(x,y);
		int r=code(x-1,y),t=code(x,y-1);

		if(s[x][y]=='/')swap(p,r),swap(q,t);
		if(find(p)!=find(q)) fa[find(p)]=find(q);
		else ans+=a[x][y],fa[find(r)]=find(t);//cout<<"fail"<<endl;
	}
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