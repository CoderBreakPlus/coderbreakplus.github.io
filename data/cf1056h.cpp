// created time: 2026-09-18 13:24:56
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
const int B = 550;

int n,q,buc[300005];
vector<int>v[300005];
vector<pair<int,int>>pos[300005];

int idx[300005],pos1[300005];
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)pos[i].clear();
	for(int i=1;i<=q;i++){
		int k=read();
		v[i]=vector<int>(k,0);
		for(int j=0;j<k;j++)v[i][j]=read(),pos[v[i][j]].pb(i,j);
	}
	
	for(int i=1;i<=n;i++){
		for(auto [x,y]:pos[i])if(y+1!=v[x].size())
			for(int j=y+1;j<=y+B&&j<v[x].size();j++)buc[v[x][j]]=0;

		for(auto [x,y]:pos[i])if(y+1!=v[x].size())
			for(int j=y+1;j<=y+B&&j<v[x].size();j++){
				if(buc[v[x][j]]&&buc[v[x][j]]!=v[x][y+1]){ puts("Human");return; }
				buc[v[x][j]]=v[x][y+1];
			}
	}

	for(int i=1;i<=q;i++)if(v[i].size()>=B){
		memset(idx,0,sizeof(idx));
		memset(pos1,0,sizeof(pos1));
		for(int j=0;j+1<v[i].size();j++){
			idx[v[i][j+1]]=j+1;

			int t=v[i][j];
			if(!pos1[t])
				pos1[t]=j+1;
		}

		for(int j=1;j<=q;j++)if(i!=j){
			int mx=0;
			for(int k=v[j].size()-1;k>=1;k--){
				chkmax(mx,idx[v[j][k]]);
				int t=v[j][k-1];
				if(pos1[t] && v[i][pos1[t]]!=v[j][k]){
					if(mx>=pos1[t]){ puts("Human");return; }
				}
			}
		}
	}
	puts("Robot");
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