// created time: 2026-08-19 09:27:52
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,m,c,u[2005],v[2005];
vector<int>E[2005];
struct Tarjan{
	int dfn[2005],low[2005],vis[2005],tim;
	int stk[2005],tp;

	vector<int>st[2005]; int c;
	vector<int>E[2005];

	int col[2005];
	void init(){
		tim=tp=c=0;
		for(int i=1;i<=n;i++)
			dfn[i]=low[i]=vis[i]=stk[i]=0,E[i].clear(),st[i].clear();
	}
	void add(int u,int v){ E[u].pb(v); }

	void tarjan(int x){
		low[x]=dfn[x]=++tim;
		vis[x]=1,stk[++tp]=x;
		for(int y:E[x]){
			if(!dfn[y]){
				tarjan(y);
				low[x]=min(low[x],low[y]);
			}else if(vis[y])
				low[x]=min(low[x],dfn[y]);
		}
		if(low[x]==dfn[x]){
			++c;
			do{
				st[c].pb(stk[tp]),vis[stk[tp]]=0;
			}while(stk[tp--]!=x);
		}
	}
	void main(){
		for(int i=1;i<=n;i++){
			if(!dfn[i])tarjan(i);
		}
		for(int i=1;i<=c;i++)sort(st[i].begin(),st[i].end());
		sort(st+1,st+c+1);
		for(int i=1;i<=c;i++)
			for(int x:st[i]) col[x]=i;
	}
}T,F;

int all=0;
namespace Sub4{
	int n, dis[2005][2005],ord[2005],iord[2005],d[2005],tt;
	vector<int>E[2005],G[2005];

	map<pair<int,int>,int>S;
	void add(int u,int v){
		S[{u,v}]++;
		if(S[{u,v}]>1){
			all++;
			return;
		}
		E[u].pb(v); d[v]++;
	}
	pair<int,int> sub4(){
		queue<int>q;
		for(int i=1;i<=n;i++)
			if(!d[i]) q.push(i);

		while(!q.empty()){
			int x=q.front();q.pop();
			ord[x]=++tt; iord[tt]=x;
			for(int y:E[x]) if(!--d[y])q.push(y);
		}

		for(int i=1;i<=n;i++)
			for(int j:E[i]){
				G[ord[i]].pb(ord[j]);
			}

		memset(dis,0xc0,sizeof(dis));
		for(int i=1;i<=n;i++){
			dis[i][i]=0;
			for(int j=i;j<=n;j++){
				for(int k:G[j])chkmax(dis[i][k],dis[i][j]+1);
			}
		}
		int cnt=all,cf=1;
		for(int i=1;i<=n;i++)
			for(int j:G[i]){
				if(dis[i][j]>1){
					cnt++;
				}else{
					cf=(ull)cf*S[{iord[i],iord[j]}]%mod;
				}
			}
		return {cnt,cf};
	}
}

bool vis[2005],mk[2005];
vector<int>G[2005];

int in[2005], out[2005], ban[2005];
pair<int,int> sub6(vector<int> node, vector<int> edge){
	int ans1 = edge.size(), ans2 = 1;
	for(int i: edge){
		if(ban[i]) continue;
		F.init();
		for(int j: edge) if(j!=i) F.add(u[j],v[j]);
		F.main();
		
		bool one = 1;
		for(int x: node) one &= (F.col[x] == F.col[node[0]]);
		if(one){
			ans1 --;
			continue;
		}

		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));

		vector<int>shit;
		for(int j: edge){
			if(F.col[u[j]]!=F.col[v[j]]){
				out[F.col[u[j]]]++;
				in[F.col[v[j]]]++;
				shit.pb(j);
			}
		}

		bool link = 1;
		for(int x: node) link &= (in[x] <= 1 && out[x] <= 1);
		
		if(link){
			for(int j: shit) ban[j] = 1;
			ans1 --;
			ans2 = (ull)ans2 * shit.size() % mod;
		}
	}
	return {ans1, ans2};
}
void procedure(){
	n=read(),m=read(),c=read();
	for(int i=0;i<m;i++){
		u[i]=read(),v[i]=read();
		E[u[i]].pb(v[i]);
	}
	T.init();
	for(int i=0;i<m;i++)T.add(u[i],v[i]);
	T.main();
	Sub4::n=T.c;
	for(int i=0;i<m;i++){
		if(T.col[u[i]]!=T.col[v[i]]){
			Sub4::add(T.col[u[i]],T.col[v[i]]);
		}
	}
	auto [ans1,ans2]=Sub4::sub4();

	for(int i=1;i<=T.c;i++){
		vector<int>edge;
		for(int x=0;x<m;x++)
			if(T.col[u[x]]==i&&T.col[v[x]]==i)edge.pb(x);
		auto [a,b]=sub6(T.st[i],edge);
		ans1+=a;
		ans2=(ull)ans2*b%mod;
	}
	printf("%d\n%d\n",ans1,ans2);
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