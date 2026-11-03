// created time: 2026-11-03 08:06:59
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
const int M=2e6+5;

int n,m,fa[M<<1];
vector<int>E[M<<1];

namespace SAM{
	int len[M<<1],fa[M<<1],son[M<<1][4],lst;
	inline void ins(int p,int v){
		len[p]=len[lst]+1;
		while(lst&&!son[lst][v]){
			son[lst][v]=p;
			lst=fa[lst];
		}
		if(!son[lst][v]){
			son[lst][v]=p;
		}else{
			int q=son[lst][v];
			if(len[q]==len[lst]+1){
				fa[p]=q;
			}else{
				int u=++m;
				len[u]=len[lst]+1,fa[u]=fa[q];
				memcpy(son[u],son[q],sizeof(son[u]));
				fa[p]=fa[q]=u;
				while(son[lst][v]==q){
					son[lst][v]=u;
					lst=fa[lst];
				}
			}
		}
		lst=p;
	}
	void clear(){
		for(int i=0;i<=m;i++)len[i]=fa[i]=0,memset(son[i],0,sizeof(son[i]));
		lst=0;
	}
}

int k;
char s[M];
string tmp[M/2];

int vis[M<<1];
int seq[M<<1],tim;

int ans[M];

bool dfs(int x){
	int L=tim+1;
	if(1<=x&&x<=n)seq[++tim]=x;
	bool flg=0;
	for(int y:E[x])flg|=dfs(y);
	int R=tim;
	if(!flg&&vis[x]){
		// cout<<"limit length="<<vis[x]<<endl;
		sort(seq+L,seq+R+1);
		int lst=1;
		for(int i=L;i<=R;i++){
			chkmax(ans[lst],seq[i]);
			lst=seq[i]-vis[x]+2;
		}
		chkmax(ans[lst],n+1);
		return 1;
	}
	return flg;
}
void procedure(int tc){
	k=read();
	for(int i=1;i<=k;i++){
		scanf("%s",s);
		tmp[i]=""; int sz=strlen(s);
		for(int j=0;j<sz;j++)tmp[i].push_back(s[j]);
	}
	scanf("%s",s+1);
	m=n=strlen(s+1);
	for(int i=1;i<=n;i++)
		SAM::ins(i,s[i]-'a'),ans[i]=i;

	for(int i=0;i<=m;i++) E[i].clear(),vis[i]=0;
	for(int i=1;i<=m;i++) E[fa[i]=SAM::fa[i]].pb(i);

	for(int i=1;i<=k;i++){
		int u=0;
		for(char ch:tmp[i]){
			u=SAM::son[u][ch-'a'];
			if(!u)break;
		}
		if(u)chkmax(vis[u],(int)tmp[i].size());
		else chkmax(ans[1],n+1);
	}

	tim=0;
	dfs(0);

	for(int i=1;i<=n;i++)
		chkmax(ans[i],ans[i-1]);

	ll sum=0;
	for(int i=1;i<=n;i++)
		sum+=max(0,n-ans[i]+1);
	printf("%lld\n",sum);
	SAM::clear();
}
int main(){
	assert(freopen("combo.in","r",stdin));
	assert(freopen("combo.out","w",stdout));
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure(i);
	}
	return 0;
}