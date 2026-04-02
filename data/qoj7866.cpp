// created time: 2026-04-02 15:05:31
// J. Teleportation
// https://qoj.ac/contest/1459/problem/7866
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,x,a[200005],dis[200005],vis[200005];
vector<pair<int,int>>E[200005];

void procedure(){
	n=read(),x=read();
	for(int i=0;i<n;i++)a[i]=read(),E[i].pb(n+(i+a[i])%n,1);
	for(int i=0;i<n;i++)E[n+i].pb(n+(i+1)%n,1),E[n+i].pb(i,0);

	deque<int>q;
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	q.push_back(0);
	while(!q.empty()){
		int x=q.front();q.pop_front();
		if(vis[x])continue;vis[x]=1;
		for(auto [y,w]:E[x]){
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				if(w) q.push_back(y);else q.push_front(y);
			}			
		}
	}
	printf("%d\n",dis[x]);
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