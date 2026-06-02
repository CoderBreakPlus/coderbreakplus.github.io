// created time: 2026-06-02 13:57:35
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

int n,q,p[500005],l[500005],r[500005],x[500005];
vector<int>sl[500005],sr[500005],fac[500005];

int fa[500005],sz[500005],tag[500005],pos[500005],val[500005],ans1[500005],ans2[500005];
int merge(int x,int y){
	if(!x||!y)return x|y;
	if(sz[x]>sz[y])swap(x,y);
	fa[x]=y,tag[x]-=tag[y],sz[y]+=sz[x];
	return y;
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),x[i]=read();
		sl[l[i]].pb(i),sr[r[i]].pb(i);
	}
	for(int i=1;i*i<=n;i++)
		for(int j=i*i;j<=n;j+=i)fac[j].pb(i);

	for(int i=1;i<=q;i++) 
		fa[i]=i,sz[i]=1;

	for(int i=1;i<=n;i++){
		for(int d: sl[i]){
			pos[val[x[d]]=merge(val[x[d]],d)]=x[d];
		}
		for(int x: fac[p[i]]){
			int y=p[i]/x;
			if(x==y){
				if(val[x])tag[val[x]]++;
				continue;
			}
			swap(val[x],val[y]);
			if(val[x]) pos[val[x]]=x,tag[val[x]]++;
			if(val[y]) pos[val[y]]=y,tag[val[y]]++;
		}
		for(int j=2;p[i]*j<=n;j++){
			if(val[p[i]*j]){
				tag[val[p[i]*j]]++;
				if(p[i]>1){
					pos[val[j]=merge(val[j],val[p[i]*j])]=j;
					val[p[i]*j]=0;
				}
			}
		}
		for(int d: sr[i]){
			int dd=d;
			int cur=tag[d];
			while(d!=fa[d]) d=fa[d],cur+=tag[d];
			ans1[dd]=pos[d], ans2[dd]=cur;
		}
	}
	for(int i=1;i<=q;i++)
		printf("%d %d\n",ans1[i],ans2[i]);
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