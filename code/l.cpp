// created time: 2026-11-07 13:39:31
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

int n,p[2005],ip[2005];
vector<pair<int,int>>edge;
vector<int>E[2005];

void add(int x,int y){
	// cout<<"link "<<x<<" "<<y<<endl;
	edge.pb(x,y);
	E[x].pb(y),E[y].pb(x);
}

int query(int l,int r){
	cout<<"? "<<l<<" "<<r<<endl;
	int ret=0;
	#ifdef LOCAL
		for(int i=1;i<n;i++)if(l<=ip[i]&&ip[i]<=r&&l<=ip[i+1]&&ip[i+1]<=r)ret++;
	#endif
	#ifndef LOCAL
		assert(cin>>ret);
	#endif

	for(auto [x,y]:edge)
		ret-=(l<=x&&x<=r&&l<=y&&y<=r);
	return ret;
}
int ans[2005],ians[2005],tim;
void dfs(int x,int fa){
	// cout<<"visit "<<x<<endl;
	ans[++tim]=x,ians[x]=tim;
	for(int y:E[x])if(y!=fa)dfs(y,x);
}
void procedure(){
	edge.clear();
	cin>>n;
	#ifdef LOCAL
	for(int i=1;i<=n;i++)cin>>p[i],ip[p[i]]=i;
	#endif
	for(int r=2,tmp;r<=n;r++)if(tmp=query(1,r)){
		while(tmp){
			int L=2,R=r-1,ans=1;
			while(L<=R){
				int M=(L+R)>>1;
				if(query(M,r)==tmp)ans=M,L=M+1;
				else R=M-1;
			}
			add(ans,r);
			tmp--;
		}
	}
	int rt=1;
	for(int i=2;i<=n;i++){
		if(E[i].size()==1){
			rt=i;
			break;
		}
	}
	dfs(rt,0);
	if(ans[1]>ans[n]){
		for(int i=1;i<=n;i++) ians[i]=n-ians[i]+1;
	}
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<ians[i]<<" ";
	cout<<endl;

	#ifdef LOCAL
	for(int i=1;i<=n;i++) assert(ians[i]==p[i]);
	#endif
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