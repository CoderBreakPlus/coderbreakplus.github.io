// created time: 2026-08-30 09:06:30
#include<bits/stdc++.h>
void Answer(int A, int B);
int Ask(int A, int B, int Place[]);

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


int n,place[1505],vis[1505];

vector<int>S;
vector<int>E[1505];

bool ask(int a,int b,vector<int> vec){
	assert(a!=b); if(a>b)swap(a,b);
	for(int i=0;i<n;i++)place[i]=0;
	place[a]=place[b]=1;
	for(int x:vec) place[x]=1;
	return Ask(a,b,place);
}

vector<int>seq;

void solve(int x,int v,vector<int> T){	
	int l=-1,r=v-1,y=v;
	while(l<=r){
		int mid=(l+r)>>1;
		vector<int>tmp=T;
		for(int i=0;i<=mid;i++)tmp.pb(i);

		if(ask(x,T[0],tmp)) y=mid,r=mid-1;
		else l=mid+1;
	}
	assert(y<v);
	if(~y){
		solve(x,y,{y});
		seq.pb(y);
		solve(y,y,T);
	}
}

void add_edge(int x,int y){
	if(x>y)swap(x,y);
	E[x].pb(y),E[y].pb(x);
}
int tim,dfn_seq[1505],dfn[1505],fuck[1505],tmp_vis[1505];
void init(){ tim=0; }
void dfs(int x,int fa){
	dfn[x]=++tim, dfn_seq[tim]=x;
	for(int y:E[x]){
		if(y==fa||fuck[y])continue;
		dfs(y,x);
	}
}

vector<int> what;
void getset(int x,int fa){
	what.pb(x); tmp_vis[x]=1;
	for(int y:E[x]){
		if(y==fa||fuck[y])continue;
		getset(y,x); 
	}
}
void find_edge(int u,vector<int> S){
	if(!ask(S[0],u,S)) return;

	init();
	dfs(S[0],0);

	int l=1,r=tim-1,ans=tim;
	while(l<=r){
		int mid=(l+r)>>1;
		vector<int>tmp;
		for(auto x: S) if(dfn[x]<=mid) tmp.pb(x);

		if(ask(S[0],u,tmp)) ans=mid,r=mid-1;
		else l=mid+1;
	}

	int ban=dfn_seq[ans];
	if(ban<u)
		Answer(ban,u);
	else
		Answer(u,ban);
	tmp_vis[ban]=fuck[ban]=1;

	vector<vector<int>>forya;
	for(int x: S) if(!tmp_vis[x]){
		what={}; getset(x,0);
		forya.pb(what);
	}
	for(int x: S) tmp_vis[x]=0;
	for(auto v: forya) find_edge(u,v);
	fuck[ban]=0;
}
void Detect(int T,int N){
	S={0};vis[0]=1;n=N;
	while(S.size()<n){
		int x=-1;
		for(int i=0;i<n;i++)
			if(!vis[i]){ x=i; break; }

		assert(~x);
		seq={x};
		solve(x,n,S);

		int hd=seq.back();
		init();

		dfs(S[0],0);		
		int l=1,r=tim,ans=tim+1;
		while(l<=r){
			int mid=(l+r)>>1;
			vector<int>tmp;
			for(auto x: S) if(dfn[x]<=mid) tmp.pb(x);

			if(ask(S[0],hd,tmp)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		assert(ans<=tim);

		seq.pb(dfn_seq[ans]);
		reverse(seq.begin(),seq.end());
		
		for(int i=1;i<seq.size();i++){
			find_edge(seq[i], S);
			add_edge(seq[i],seq[i-1]);
			S.pb(seq[i]), vis[seq[i]]=1;
		}
	}
}