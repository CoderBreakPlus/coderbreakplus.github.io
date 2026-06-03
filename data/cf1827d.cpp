#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> Pr;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define mid ((l+r)>>1)
#define popcnt __builtin_popcountll

inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
ll n,p[500005],dfn[500005],out[500005],seq[500005],tim,cent,son,val;
vector<ll>E[500005]; set<ll>S[500005];

ll c[500005];
inline void upd(ll x,ll w=1){
	for(; x<=n; x+=(x&(-x))){
		c[x] += w;
	}
}
inline ll query(ll x){
	ll res = 0;
	for(; x; x-=(x&(-x))){
		res += c[x];
	}
	return res;
}
void dfs(ll x){
	dfn[x]=(++tim); seq[tim]=x;
	for(auto y: E[x]){
		dfs(y);
		S[x].insert(dfn[y]);
	}
	out[x]=tim;
}
inline ll sub_tree(ll x){
	return query(out[x]) - query(dfn[x]-1);
}
inline ll out_tree(ll x){
	return query(n) - query(out[x]) + query(dfn[x]-1);
}
inline ll find_subtree(ll x,ll y){
	if(dfn[x] <= dfn[y] && dfn[y] <= out[x]){
		return seq[*(--S[x].upper_bound(dfn[y]))];
	}else return -1;
}
inline ll get_val(ll x,ll id){
	if(id == -1) return out_tree(x);
	else return sub_tree(id);
}
void Main(){
	n=read();
	for(ll i=1;i<=n;i++) c[i]=0, E[i].clear(), S[i].clear();
	tim=son=val=0; cent=1;
	for(ll i=2;i<=n;i++){
		p[i]=read();
		E[p[i]].pb(i);
	}
	dfs(1); upd(dfn[1]);
	for(ll i=2;i<=n;i++){
		upd(dfn[i]);
		ll id = find_subtree(cent, i);
		if(2 * get_val(cent, id) > i){
			ll cent2 = (id == -1)? p[cent]: id;
			son = (cent == p[cent2])? -1: cent2;
			val = i - get_val(cent, id);
			cent = cent2;
		}else if(get_val(cent, id) > val){
			son = id;
			val = get_val(cent, id);
		}
		printf("%lld\n", i-val*2);
	}
}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--) Main();
	return 0;
}

