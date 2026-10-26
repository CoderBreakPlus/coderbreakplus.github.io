// created time: 2026-10-24 09:50:44
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
const int N = 200005;
int n,a[N];
vector<int>E[N];
vector<int>dp0[N],dp1[N];
struct Edge{ int y,w,has1; };
vector<Edge>son[N];
inline void upd(int &a,ull b){ a=(a+b)%mod; }
inline int submod(int a,int b){ return a>=b?a-b:a-b+mod; }

void shift_chain(int y,int w,int has1){
	if(!w)return;
	int sz=max(dp0[y].size(),dp1[y].size());
	vector<int>b0(sz+w),b1(sz+w);
	for(int i=0;i<(int)dp0[y].size();i++)b0[i+w]=dp0[y][i];
	for(int i=0;i<(int)dp1[y].size();i+=2){
		if(has1)addmod(b0[i+w]+=dp1[y][i]);
		else b1[i+w]=dp1[y][i];
	}
	dp0[y].swap(b0),dp1[y].swap(b1);
}
void calc(int x){
	if(son[x].empty()){
		if(a[x]==1){
			dp0[x].resize(2,0);
			dp0[x][1]=1;
		}else{
			dp1[x].resize(3,0);
			dp1[x][2]=1;
		}
	}else{
		int sz=1e9;
		for(auto [y,w,has1]:son[x]){
			shift_chain(y,w,has1);
			chkmin(sz,(int)max(dp0[y].size(),dp1[y].size()));
		}

		vector<array<array<int,2>,3>>tmp(sz+2);
		for(int i=0;i<=sz;i++)for(int p=0;p<3;p++){
			tmp[i][p][0]=1;
			tmp[i][p][1]=0;
		}
		for(auto [y,w,has1]:son[x]){
			vector<int>f0(dp0[y].size()+2),f1((dp1[y].size()+1)/2+2);
			int sum=0;
			for(int j=(int)dp0[y].size()-1;j>=0;j--){
				addmod(sum+=dp0[y][j]);
				addmod(f0[j]=f0[j+1]+sum);
			}
			sum=0;
			for(int j=((int)dp1[y].size()+1)/2-1;j>=0;j--){
				addmod(sum+=dp1[y][j*2]);
				addmod(f1[j]=f1[j+1]+sum);
			}
			for(int i=0;i<=sz;i++)for(int p=0;p<3;p++){
				int t=(i+1)/2+(p+1)/2;
				int h0=i+p<(int)f0.size()?f0[i+p]:0;
				int h1=t<(int)f1.size()?f1[t]:0;
				int h=h0+h1;
				addmod(h);
				int v0=tmp[i][p][0],v1=tmp[i][p][1];
				tmp[i][p][0]=(ull)v0*h0%mod;
				tmp[i][p][1]=((ull)v1*h+(ull)v0*h1)%mod;
			}
			vector<int>().swap(dp0[y]),vector<int>().swap(dp1[y]);
		}

		dp0[x].resize(sz+a[x]);
		dp1[x].resize(sz+a[x]);
		for(int i=0;i<sz;i++){
			int v0=submod(submod(tmp[i][0][0],tmp[i][1][0]),submod(tmp[i+1][0][0],tmp[i+1][1][0]));
			int v1=submod(submod(tmp[i][0][1],tmp[i][2][1]),submod(tmp[i+1][0][1],tmp[i+1][2][1]));
			int s0=i,s1=i-(i&1);
			if(a[x]==1){
				addmod(dp0[x][s0+1]+=v0);
				addmod(dp0[x][s1+1]+=v1);
			}else{
				if(!s0) addmod(dp1[x][2]+=v0);
				else addmod(dp0[x][s0+2]+=v0);
				addmod(dp1[x][s1+2]+=v1);
			}
		}
	}
}
void dfs(int x,int fa){
	for(int y:E[x])if(y!=fa){
		int pre=x,cur=y,w=0,has1=0;
		while(E[cur].size()==2){
			w+=a[cur],has1|=(a[cur]==1);
			int nxt=E[cur][0]==pre?E[cur][1]:E[cur][0];
			pre=cur,cur=nxt;
		}
		dfs(cur,pre);
		son[x].push_back({cur,w,has1});
	}
	calc(x);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),E[i].clear(),son[i].clear(),dp0[i].clear(),dp1[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int ans=0;
	for(int i=0;i<dp0[1].size();i++)upd(ans,(ull)dp0[1][i]*(i+1));
	for(int i=0;i<dp1[1].size();i+=2)upd(ans,(ull)dp1[1][i]*(i/2+1));
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("a.in","r",stdin));
		assert(freopen("a.out","w",stdout));
	#endif
	ll T=read();
	while(T--) procedure();
	return 0;
}
