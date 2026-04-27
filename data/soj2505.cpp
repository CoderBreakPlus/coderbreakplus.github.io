// created time: 2026-04-24 10:12:43
// http://10.49.18.71/problem/2505
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m;

vector<int>E[200005];
int d[200005],u[200005],v[200005],tmp[200005],d2[200005];
int fa[200005];
int find(int x){
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
struct Graph{
	multiset<int>S[200005];
	void add(int u,int v){
		// #ifdef LOCAL
		// cout<<"add "<<u<<" "<<v<<endl;
		// #endif
		S[u].emplace(v),S[v].emplace(u);
	}
	int stk[400005],tp;

	void clear(){
		tp=0;
		for(int i=1;i<=n;i++) S[i].clear();
	}
	void dfs(int u){
		while(!S[u].empty()){
			int v=*S[u].begin();
			S[u].erase(S[u].begin());
			S[v].erase(S[v].find(u));
			dfs(v);
		}
		stk[++tp]=u;
	}
}G;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int seq[200005],sq,esp[200005];
void procedure(int o){
	n=read(),m=read();
	for(int i=1;i<=n;i++)E[i].clear(),d[i]=esp[i]=0;
	for(int i=1;i<=n;i++)fa[i]=i;

	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		d[u[i]]++,d[v[i]]++;
		E[u[i]].pb(v[i]),E[v[i]].pb(u[i]);
		fa[find(u[i])]=find(v[i]);
	}
	if(!m){
		puts("0\n0\n");
		return;
	}
	int ok=0,flg=1,s=0,st=0;
	for(int i=1;i<=n;i++){
		if(!d[i])continue;

		if(!st) st=i;

		s+=(d[i]&1);
		if(d[i]&1)st=i;

		if(!ok)ok=find(i);
		else if(ok!=find(i))flg=0;
	}
	if(flg && s<=2){
		for(int i=1;i<=m;i++) G.add(u[i],v[i]);
		G.dfs(st);
		printf("%d\n",G.tp);
		for(int i=G.tp;i>=1;i--) printf("%d ",G.stk[i]);puts("");
		puts("0");puts("");
		G.clear();
		return;
	}
	int sbm=0;
	for(int i=1;i<=n;i++){
		if(d[i]&1){
			sbm++;
			esp[i]++;
			for(auto x: E[i]) esp[x]++;
		}
	}
	vector<int>valid_t;
	for(int i=1;i<=n;i++)
		if(esp[i]>=sbm-1){
			valid_t.pb(i);
		}
	shuffle(valid_t.begin(),valid_t.end(),rnd);

	for(int t: valid_t){
		for(int i=1;i<=n;i++) tmp[i]=d2[i]=0;
		vector<int>vec;
		for(int i=1;i<=n;i++){
			if(i==t) continue;
			if(d[i]&1) vec.pb(i),tmp[i]=1; 
		}
		for(int i=1;i<=n;i++) fa[i]=i;

		auto output = [&](int y,int w=0){
			G.dfs(y);
			printf("%d\n",G.tp);
			for(int i=G.tp;i>=1;i--) printf("%d ",G.stk[i]); puts("");

			printf("%d\n",2*((int)vec.size()-w));
			for(auto x: vec) if(x!=y)printf("%d %d ",x,t);
			puts("");

			G.clear();
		};

		// t->t
		int mc=0;
		sq=0;
		for(int i=1;i<=m;i++){
			if(v[i]==t)swap(u[i],v[i]);
			if(u[i]==t && tmp[v[i]]){ mc++; tmp[v[i]]=0; continue; }

			seq[++sq]=i;
			d2[u[i]]++, d2[v[i]]++;
			fa[find(u[i])]=find(v[i]);
		}
		if(mc+1<vec.size())continue;
		// okc++;
		// cerr<<okc<<endl;

		int ok=0,ok2=0,flg=1;
		for(int i=1;i<=n;i++){
			if(!d2[i] && i!=t) continue;
			int w=find(i);
			if(!ok) ok=w;
			else if(ok!=w && !ok2) ok2=w;
			else if(ok!=w && ok2!=w) flg=0;
		}

		if(mc==vec.size()){
			if(!ok2){
				for(int i=1;i<=sq;i++)G.add(u[seq[i]],v[seq[i]]);
				output(t); // t->t，最后干掉菊花
				return;
			}else if(flg){
				for(auto y: vec){
					if(!d2[y]) continue;
					if(find(t)!=find(y)){
						for(int i=1;i<=sq;i++)G.add(u[seq[i]],v[seq[i]]);
						G.add(t,y);
						output(y,1); // 形成菊花，但是留一条边给欧拉路径
						return;
					}
				}
			}
		}else if(!ok2 && mc+1==vec.size()){
			int y;
			for(y=1;y<=n;y++) if(tmp[y]) break;
			for(int i=1;i<=sq;i++)G.add(u[seq[i]],v[seq[i]]);
			output(y,1); // y->t，干掉菊花
			return;
		}
	}
	// cerr<<okc<<endl;
	puts("-1");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure(i==22);
	}
	return 0;
}