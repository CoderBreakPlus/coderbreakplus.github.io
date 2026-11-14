// created time: 2026-10-26 13:54:17
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

int n;
vector<int>E[300005];
const int V=19;
int f[300005][V],mx[300005],tmp[1<<V];
int ans;
inline void upd(int &a,ull b){ a=(a+b)%mod; }

void dfs(int x,int fa){
	vector<pair<int,int>>son;
	int m=0;
	for(int y:E[x])if(y!=fa){
		dfs(y,x);
		son.pb(mx[y],y);
		chkmax(m,mx[y]);
	}
	chkmin(m,(int)son.size()+1);
	++m;

	sort(son.begin(),son.end());
	// while(!son.empty()&&son.back().fi>=m)son.pop_back();
	// cout<<"node "<<x<<" m="<<m<<endl;
	memset(tmp,0,sizeof(int)<<m);
	tmp[0]=1;
	int lst=0;
	for(auto [v,y]: son){
		lst=min(m,v+1);
		for(int j=(1<<lst)-1;j>=0;j--)
			for(int k=0;k<=v;k++)
				if((j>>k)&1) upd(tmp[j],(ull)tmp[j^(1<<k)]*f[y][k]);
	}
	// cout<<endl;

	// for(int i=0;i<(1<<lst);i++)
	// 	cout<<tmp[i]<<" "; cout<<endl;
	memset(f[x],0,sizeof(f[x]));

	// cout<<"lst="<<lst<<endl;
	int tot=0;
	for(int i=0;i<=lst+1;i++){
		int s=(1<<i)-1;
		// cout<<"i="<<i<<endl;
		for(int j=0;j<i;j++){
			int t=s^(1<<j);
			if(t<(1<<lst)){
				// cout<<"add "<<j<<" from "<<t<<" val="<<tmp[t]<<endl;
				addmod(f[x][j]+=tmp[t]);
			}
		}
		if(s<(1<<lst)){
			addmod(tot+=tmp[s]);
		}
	}
	addmod(ans+=tot);
	// cout<<"tot="<<tot<<endl;
	mx[x]=lst;
	while(mx[x]>=0&&!f[x][mx[x]])mx[x]--;
	// cout<<"mx = "<<mx[x]<<endl;
	// for(int i=0;i<=mx[x];i++) cout<<f[x][i]<<" "; cout<<endl;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	ans=0;
	dfs(1,0);
	printf("%d\n",ans);
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