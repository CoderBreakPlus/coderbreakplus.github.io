// created time: 2026-11-15 14:10:37
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

int n,m,k,N,a[12];
bool e[12][12];
pair<int,int> seq[6];
ull cf[12];
int p[12],v[6][6];

unordered_map<ull,int>mp;
ull pw[12],ans;

void color(int i,int v,ull val){
	if(i==N){
		if(!mp.count(val)){
			mp[val]=1;
			ans+=cf[v];
		}
		return;
	}
	auto [x,y]=seq[i];
	ull hsh=pw[x]+pw[y];
	for(int now=0;now<=v;now++)
		color(i+1,max(now+1,v),val+hsh*now);
}
bool f[1<<6][6];int g[6];
bool check(){
	memset(g,0,sizeof(g));
	for(int i=0;i<N;i++){
		auto [a,b]=seq[i];
		for(int j=i+1;j<N;j++){
			auto [c,d]=seq[j];
			if((e[a][c]&&e[b][d])||(e[a][d]&&e[b][c])){
				g[i]|=(1<<j);
				g[j]|=(1<<i);
			}
		}
	}
	memset(f,0,sizeof(f));
	for(int i=0;i<N;i++)f[1<<i][i]=1;
	for(int i=1;i<(1<<N);i++){
		for(int j=0;j<N;j++)if(f[i][j]){
			int res=((1<<N)-1-i)&g[j];
			while(res){
				int k=__builtin_ctz(res);
				f[i^(1<<k)][k]=1;
				res^=(1<<k);
			}
		}
	}
	for(int i=0;i<N;i++){
		if(f[(1<<N)-1][i]&e[seq[i].fi][seq[i].se])return 1;
	}
	return 0;
}
void dfs(int i,int s){
	if(i==N){
		// for(int i=0;i<N;i++)cout<<seq[i].fi<<","<<seq[i].se<<" ";
		// cout<<endl;
		if(check()){
			// cout<<"#passed"<<endl;
			color(0,0,0);
		}
		return;
	}
	int x=__builtin_ctz(s),tmp=s^(1<<x);
	while(tmp){
		int y=__builtin_ctz(tmp);
		seq[i]={x,y};
		dfs(i+1,s^(1<<x)^(1<<y));
		tmp^=(1<<y);
	}
}
void procedure(){
	n=read(),m=read(),k=read();N=n/2;
	pw[0]=1;
	for(int i=1;i<n;i++)
		pw[i]=pw[i-1]*N;
	for(int i=0;i<m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=e[v][u]=1;
	}

	for(int i=0;i<=k;i++){
		cf[i]=1;
		for(int x=k;x>k-i;x--)cf[i]*=x;
	}
	dfs(0,(1<<n)-1);
	printf("%llu\n",ans);
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