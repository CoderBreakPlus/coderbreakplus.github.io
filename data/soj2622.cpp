// created time: 2026-06-22 16:22:03
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

int n,q,a[1000005],l[1000005],r[1000005],k[1000005],fa[1000005][2],ans[1000005];
int code(int x,int y){ return (x<<1)|y; }
vector<int>vec[1000005];

char s[1000005];

inline int find(int x,int y){
	if(fa[x][y]!=x) fa[x][y]=find(fa[x][y],y);
	return fa[x][y];
}
set<int>st;

struct BIT{
	int c[1000005];
	void add(int x,int w){
		while(x<=n) c[x]+=w,x+=(x&-x);
	}
	int qry(int x){
		int ret=0;
		while(x) ret+=c[x],x-=(x&-x);
		return ret;
	}
}T1,T2;

void upd(int p){
	int tmp=T1.qry(p);
	T1.add(p,-1);
	int l=1,r=n,ans=n+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(T2.qry(mid)>tmp) ans=mid,r=mid-1;
		else l=mid+1;
	}
	T2.add(ans,-1);
}
void procedure(){
	n=read(),q=read();
	scanf("%s",s+1);
	st={0};
	for(int i=1;i<=n;i++)
		s[i]-='0',st.emplace(i);
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),k[i]=read();
		if(!k[i])ans[i]=r[i]-l[i]+1;
		else vec[k[i]].pb(i);
	}
	for(int i=1;i<=n;i++){
		fa[i][s[i]]=i;
		fa[i][!s[i]]=i+1;
	}
	for(int i=1;i<=n;i++) T1.add(i,1);
	for(int i=1;i<=n;i++) T2.add(i,1);

	fa[n+1][0]=fa[n+1][1]=n+1;

	for(int k=1;min(find(1,0),find(1,1))<=n;k++){
		T2.add(1,1);
		for(int i=min(find(1,0),find(1,1));i<=n;i=find(i+1,!s[i])){
			upd(i),st.erase(i),fa[i][s[i]]=i+1;
		}
		for(int i:vec[k]){
			int pr=*prev(st.upper_bound(r[i]));
			int idl=T2.qry(l[i]),idr=T1.qry(pr);
			ans[i]=max(0,idr-idl+1);
		}
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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