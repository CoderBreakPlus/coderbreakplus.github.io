// created time: 2026-05-30 12:23:38
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

int n,dfn[100005],out[100005],tim;
vector<int>E[100005];
vector<pair<int,int>>M[100005];

void dfs(int x,int fa){
	dfn[x]=++tim;
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
	}
	out[x]=tim;
}

void procedure(){
	n=read();
	for(int i=0;i<=n;i++)M[i].clear(),E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		M[w].pb(u,v);
		E[u].pb(v),E[v].pb(u);
	}
	int ans=0;
	#define T4 tuple<int,int,int,int>
	for(auto [x,y]:M[0]){
		tim=0;
		dfs(x,y);
		int cut=tim;
		dfs(y,x);

		vector<T4>F,G;
		F={{1,cut,cut+1,n}};

		for(int i=1;;i++){
			vector<T4>H;
			for(auto [x,y]:M[i]){
				if(dfn[x]>dfn[y])swap(x,y);
				if(dfn[y]>cut){
					H.pb(1,cut,dfn[y],out[y]);
				}else{
					H.pb(dfn[y],out[y],cut+1,n);
				}
			}
			G.clear();
			for(auto [a,b,c,d]: F)
				for(auto [e,f,g,h]: H){
					int l=max(a,e),r=min(b,f),s=max(c,g),t=min(d,h);
					if(l>r||s>t)continue;
					G.pb(l,r,s,t);
				}
			sort(G.begin(),G.end(),[](const T4& x,const T4& y){
				auto [a,b,c,d]=x;
				auto [e,f,g,h]=y;
				ll s1 = (ll)(b-a+1)*(d-c+1);
				ll s2 = (ll)(f-e+1)*(h-g+1);
				if(s1 != s2) return s1 > s2;
				if(a != e) return a < e;
				if(b != f) return b < f;
				if(c != g) return c < g;
				return d < h;
			});
			
			G.erase(unique(G.begin(), G.end()), G.end());

			F.clear();
			for(int i=0; i<G.size(); i++){
				auto [a,b,c,d]=G[i];
				bool flg=1;
				for(int j=0; j<F.size(); j++){
					auto [e,f,g,h]=F[j];
					if(e<=a && b<=f && g<=c && d<=h){
						flg=0;
						break;
					}
				}
				if(flg){
					F.push_back(G[i]);
					if(F.size()>200)break;
					// assert(F.size() <= 200);
				}
			}
			if(G.empty()){
				chkmax(ans, i);
				break;
			}
		}
	}
	printf("%d\n", ans);
	#undef T4
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