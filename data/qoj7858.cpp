// created time: 2026-04-02 14:05:17
// B. Basic Equation Solving
// https://qoj.ac/contest/1459/problem/7858
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
int n; string S[55],T[55]; int op[55];

int code(char s){
	if('0'<=s && s<='9') return s-'0';
	else return s-'A'+10;
}
namespace sol{
	vector<pair<int,int>>s1,s2;
	bool e[36][36];
	bitset<1<<12>ok[1<<12];

	int out[36], f[1<<12], g[1<<12];

	struct dsu{
		int fa[36];
		int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
		void merge(int x,int y){
			x=find(x),y=find(y);
			if(x<y)swap(x,y); fa[x]=y;
		}
		void init(){
			for(int i=0;i<36;i++) fa[i]=i;
		}
	}d1,d2;

	vector<int>node[36];
	int mn[36],mx[36],sta[10];

	int main(){
		// cout<<"maining"<<endl;
		d1.init(),d2.init();
		memset(e,0,sizeof(e));
		memset(out,0,sizeof(out));
		for(auto [x,y]: s1){
			x=code(x),y=code(y);
			d1.merge(x,y);
		}
		for(int i=0;i<36;i++) mn[i]=0,mx[i]=9,node[i].clear();
		for(auto [x,y]: s2){
			x=code(x),y=code(y);
			x=d1.find(x),y=d1.find(y);
			d2.merge(x,y);
			if(x<10 && y<10){
				if(x>=y) return 0;
			}else if(x<10) mn[y]=max(mn[y],x+1);
			else if(y<10) mx[x]=min(mx[x],y-1);
			else e[x][y]=1;
		}
		for(int i=0;i<10;i++)
			if(d1.find(i)!=i) return 0;
		for(int i=10;i<36;i++){
			if(d1.find(i)==i){
				if(mn[i]>mx[i]) return 0;
				node[d2.find(i)].pb(i);
			}
		}
		int ans=1;
		for(int i=0;i<36;i++){
			int sz=node[i].size();
			if(!sz) continue;
			for(int v=0;v<10;v++) sta[v]=0;
			for(int x=0;x<sz;x++){
				for(int y=mn[node[i][x]];y<=mx[node[i][x]];y++) sta[y]|=(1<<x);
				out[x]=0;
				for(int y=0;y<sz;y++){
					if(e[node[i][x]][node[i][y]])
						out[x]|=(1<<y);
				}
			}
			for(int s=0;s<(1<<sz);s++){
				for(int t=s;t<(1<<sz);t=(t+1)|s){
					ok[s][t]=1;

					int sb=(s^t);
					while(sb){
						int x=__builtin_ctz(sb);
						if(out[x]&t){
							ok[s][t]=0;
							break;
						}
						sb^=(1<<x);
					}
				}
			}
			memset(f,0,sizeof(int)*(1<<sz));
			f[0]=1;
			for(int x=0;x<=9;x++){
				memset(g,0,sizeof(int)*(1<<sz));
				for(int s=0;s<(1<<sz);s++){
					if(!f[s])continue;
					int res=((1<<sz)-1-s)&sta[x];
					for(int t=res;;t=(t-1)&res){
						if(ok[s][s|t]) addmod(g[s|t]+=f[s]);
						if(!t)break;
					}
				}
				memcpy(f,g,sizeof(int)*(1<<sz));
			}
			ans=1ull*ans*f[(1<<sz)-1]%mod;
		}
		return ans;
	}
}

int ans;
void dfs(int x,vector<pair<int,int>>s1,vector<pair<int,int>>s2){
	if(x>n){
		sol::s1 = s1, sol::s2 = s2;
		addmod(ans += sol::main());
		return;
	}
	if(op[x]==0){
		for(int i=0;i<S[x].size();i++){
			s1.emplace_back(S[x][i],T[x][i]);
		}
		dfs(x+1,s1,s2);
	}else if(op[x]==-1){
		for(int i=0;i<S[x].size();i++){
			s2.emplace_back(S[x][i],T[x][i]);
			dfs(x+1,s1,s2);
			s2.pop_back();
			s1.emplace_back(S[x][i],T[x][i]);
		}
	}else{
		for(int i=0;i<S[x].size();i++){
			s2.emplace_back(T[x][i],S[x][i]);
			dfs(x+1,s1,s2);
			s2.pop_back();
			s1.emplace_back(S[x][i],T[x][i]);
		}
	}
}

void procedure(){
	cin>>n;
	for(int o=1;o<=n;o++){
		string w;cin>>w;
		for(int i=0;i<w.size();i++){
			if(w[i]=='<'){
				op[o]=-1;
				for(int x=0;x<i;x++)S[o].push_back(w[x]);
				for(int x=i+1;x<w.size();x++)T[o].push_back(w[x]);
			}
			if(w[i]=='='){
				op[o]=0;
				for(int x=0;x<i;x++)S[o].push_back(w[x]);
				for(int x=i+1;x<w.size();x++)T[o].push_back(w[x]);
			}
			if(w[i]=='>'){
				op[o]=1;
				for(int x=0;x<i;x++)S[o].push_back(w[x]);
				for(int x=i+1;x<w.size();x++)T[o].push_back(w[x]);
			}
		}
		bool swp=0;
		if(S[o].size()<T[o].size()) {
			swp=1;
			swap(S[o],T[o]);
		}
		int d=S[o].size()-T[o].size();
		while(d--)T[o]="0"+T[o];
		if(swp) swap(S[o],T[o]);
	}
	dfs(1,{},{});
	cout<<ans<<endl;
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