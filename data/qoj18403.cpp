// created time: 2026-06-01 15:10:47
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

int n,m,id;
const int N=1200000;
int fa[3600005];
map<pair<int,int>,int>mp;

int getid(int x,int y){
	if(!mp.count({x,y})){
		++id,mp[{x,y}]=id;
		fa[id]=id, fa[id+N]=id+N, fa[id+N*2]=id+N*2;
	}
	return mp[{x,y}];
}
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
void link(int x,int y){
	fa[find(x)]=find(y);
}
void merge(int x,int y){
	// cout<<"add "<<x<<" "<<y<<endl;
	link(x, y+N);
	link(x+N, y+2*N);
	link(x+2*N, y);
}
void procedure(){
	m=read(),id=0;
	mp.clear();
	for(int i=1;i<=m;i++){
		int a=read(),b=read(),c=read();
		merge(getid(a,b),getid(b,c));
		merge(getid(a,c),getid(c,b));
		merge(getid(b,a),getid(a,c));
		merge(getid(b,c),getid(c,a));
		merge(getid(c,a),getid(a,b));
		merge(getid(c,b),getid(b,a));
	}
	for(int i=1;i<=id;i++){
		if(find(i)==find(i+N)){
			puts("yes");
			return;
		}
	}
	puts("no");
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