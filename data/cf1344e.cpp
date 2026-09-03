// created time: 2026-09-03 16:24:24
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

int n,m,s[100005],t[100005],son[100005],hv[100005],dfn[100005],out[100005],dft;


namespace Sol{
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>sl;
	pair<ll,ll> seq[10000005]; int c;
	void push(ll l,ll r){
		sl.push({l,r});
		seq[++c]={l,r};
		// cout<<"push "<<l<<" "<<r<<endl;
	}
	void main(){
		ll t=1, ans=-1;
		priority_queue<ll,vector<ll>,greater<ll>>q;
		while(!sl.empty() || !q.empty()){
			if(q.empty()) chkmax(t, sl.top().fi);
			while(!sl.empty() && sl.top().fi<=t)
				q.push(sl.top().se), sl.pop();

			q.pop();
			if(!q.empty() && q.top()<=t){
				ans=t;
				break;
			}
			t++;
		}
		if(~ans){
			ll cnt=0;
			for(int i=1;i<=c;i++)
				if(seq[i].se < ans) cnt++;
			printf("%lld %lld\n", ans, cnt);
		}else{
			printf("-1 %lld\n", c);
		}
	}
}
vector<pair<int,int>>E[100005];
set<int>S[100005];

ll dep[100005];

void dfs(int x){
	dfn[x]=++dft;
	for(auto [y,w]:E[x]){
		dep[y]=dep[x]+w;
		dfs(y);
		if(S[y].size()>S[hv[x]].size())hv[x]=y; 
	}
	if(!hv[x]){out[x]=dft;return;}
	vector<pair<ll,int>>vec;
	for(auto [y,w]:E[x]){
		if(y==hv[x])continue;
		int lst = -1;

		for(int i: S[y]){
			auto it = S[hv[x]].insert(i).fi;
			if(it!=S[hv[x]].begin()&&*prev(it)!=lst)
				vec.pb(t[i]+dep[x],i);
			if(next(it)!=S[hv[x]].end())
				vec.pb(t[*next(it)]+dep[x],*next(it));
			lst=i;
		}
		S[y].clear();
	}
	// cout<<"at "<<x<<endl;
	if(!S[hv[x]].empty()){
		int fir=*S[hv[x]].begin();
		vec.pb(t[fir]+dep[x],fir);

		sort(vec.begin(),vec.end());
		vec.erase(unique(vec.begin(),vec.end()),vec.end());

		// cout<<"dfn = "<<dfn[s[fir]]<<endl;
		// cout<<"during "<<dfn[son[x]]<<" and "<<out[son[x]]<<endl;
		for(int i=0;i<vec.size();i++){
			if(!i && dfn[son[x]]<=dfn[s[fir]] && dfn[s[fir]]<=out[son[x]]);
			else{
				// cout<<"se = "<<vec[i].se<<endl;
				auto it = S[hv[x]].find(vec[i].se);
				Sol::push((it==S[hv[x]].begin()?0:t[*prev(it)]+dep[x])+1, vec[i].fi);
			}
		}
	}
	swap(S[x],S[hv[x]]);
	for(int i: S[hv[x]]) S[x].insert(i);

	// for(int i: S[x]) cout<<t[i]+dep[x]<<" "; cout<<endl;
	out[x]=dft;
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w), son[u]=v;
	}
	for(int i=1;i<=m;i++){
		s[i]=read(),t[i]=read();
		S[s[i]].insert(i);
	}
	dfs(1);
	Sol::main();
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