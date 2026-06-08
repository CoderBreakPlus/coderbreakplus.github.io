// created time: 2026-05-14 08:07:14
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

int n,m,q,s[1000005],t[1000005],u[1000005],v[1000005],tim[1000005];
int fa[1000005];
unordered_map<int,int>mp[1000005];

inline int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
inline void merge(int x,int y){ fa[find(x)]=find(y); }
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=0;i<n;i++)mp[i].clear();
	for(int i=1;i<=m;i++){
		s[i]=read(),t[i]=read();
		mp[s[i]][t[i]]=mp[t[i]][s[i]]=i;
		tim[i]=q+1;
	}

	int v2=0,v3=0;
	for(int i=1;i<=q;i++){
		u[i]=(read()+v2)%n,v[i]=(read()+v3)%n;
		if(mp[u[i]].count(v[i])){
			chkmin(tim[mp[u[i]][v[i]]],i);
		}
		v2=(v2*2+1)%n, v3=(v3*3+1)%n;
	}

	int L=1,R=q,ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		for(int i=0;i<n;i++)fa[i]=i;
		for(int i=1;i<=m;i++)
			if(tim[i]>mid){
				merge(s[i],t[i]);
			}

		bool ok=1;
		for(int i=1;i<n;i++)
			ok&=(find(i)==find(0));

		if(ok){
			ans=mid;
			L=mid+1;
		}else R=mid-1;
	}

	for(int i=1;i<=q;i++){
		putchar((i<=ans)+'0');
		putchar('\n');
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}