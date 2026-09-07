// created time: 2026-09-05 09:54:37
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }

const ull Base = 131, Mod = (ll)1e16 + 2137;
int n,u,v,w,sz[100005],mxs[100005],vis[100005],wh,rt;
vector<pair<int,int>>E[100005];

ull hsh[3][100005],pw[100005];
bool ok[100005];

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(auto [y,w]:E[x]){
		if(vis[y]||y==fa)continue;
		findcent(y,x);
		sz[x]+=sz[y];
		chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt]) rt=x;
}

int stk[100005],tp,valid[100005],dep[100005];
int seq[100005],tl,col[100005],mxlen;
map<ull,int>mps,mp[100005];

void dfs(int x,int fa,int c){
	stk[++tp]=x, valid[x]=0, sz[x]=1, col[x]=c;
	if(tp&1){
		int len=(tp-1)/2, y=stk[(tp+1)/2];
		if((hsh[2][y]+(__int128)pw[len]*hsh[0][y])%Mod==hsh[0][x]){
			valid[x]=1;
			chkmax(mxlen,len);
		}
	}
	seq[++tl]=x;

	mps[hsh[1][x]]++;
	if(x==c) mp[c].clear();
	if(c) mp[c][hsh[1][x]]++;

	for(auto [y,w]: E[x]){
		if(y==fa||vis[y])continue;
		dep[y]=dep[x]+1;
		for(int o:{0,1}){
			hsh[o][y]=((ull)hsh[o][x]*Base+(w^o)+1)%Mod;
		}
		hsh[2][y]=(hsh[2][x]+(__int128)pw[dep[x]]*((w^1)+1))%Mod;
		dfs(y,x,fa?c:y), sz[x]+=sz[y];
	}
	tp--;
}
int m;

bool check(int x,int fa){
	stk[++tp]=x;
	bool ret=0;
	for(auto [y,w]: E[x]){
		if(y==fa||vis[y])continue;
		ret|=check(y,x);
		if(ret)break;
	}
	if(!ret && 2*dep[x]>=m && dep[x]<=m){
		// cout<<"working on "<<x<<endl;

		int y=stk[tp-(m-dep[x])];
		// cout<<"y="<<y<<endl;
		if(valid[y]){
			// cout<<"valid!"<<endl;
			ull tmp=(hsh[0][x]+(__int128)(Mod-pw[m-dep[x]])*hsh[0][y])%Mod;
			if(mps.count(tmp)){
				if(!mp[col[x]].count(tmp) || mps[tmp]!=mp[col[x]][tmp]){
					ret=1;
					// cout<<"find on node "<<x<<endl;
				}
			}			
		}
	}
	--tp; return ret;
}

int ans=0;
void solve(int x){
	mxlen=0;
	vis[x]=1,tl=0,mps.clear();
	hsh[0][x]=hsh[1][x]=0,dep[x]=0;
	dfs(x,0,0);
	chkmax(ans, mxlen);

	int L=ans+1, R=(sz[x]-1)/2;
	while(L<=R){
		int mid=(L+R)>>1;
		m=2*mid;
		if(check(x,0)) ans=mid, L=mid+1;
		else R=mid-1;
	}

	for(auto [y,w]:E[x]) if(!vis[y]){
		wh=sz[y], rt=0;
		findcent(y,x);
		solve(rt);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
	}

	memset(vis,0,sizeof(vis));
	mxs[0]=wh=n, rt=0;
	findcent(1,0), solve(rt);
	
	printf("%d\n", 2*ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	pw[0]=1;
	for(int i=1;i<=1e5;i++) pw[i]=(ull)pw[i-1]*Base%Mod;
	// math_init();
	while(T--) procedure();
	return 0;
}