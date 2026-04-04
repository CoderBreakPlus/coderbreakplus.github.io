// created time: 2026-04-04 12:58:38
// M. Linked VERSE
// https://qoj.ac/contest/3575/problem/17725
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

int n,q,a[300005];

struct Convex{
	vector<pair<ll,ll>>vec;
	void ins(pair<ll,ll> p){ vec.push_back(p); }
	void clear(){ vec.clear(); }
	bool anti(pair<ll,ll> A,pair<ll,ll> B,pair<ll,ll> C){
		return (__int128)(B.se-A.se)*(C.fi-B.fi) < (__int128)(C.se-B.se)*(B.fi-A.fi);
	}
	void simplify(){
		vec.pb(0,0);
		sort(vec.begin(),vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
 
		vector<pair<ll,ll>>vec2;
 
		for(auto p: vec){
			while(vec2.size() >= 2 && anti(vec2[vec2.size()-2], vec2.back(), p)) vec2.pop_back();
			vec2.push_back(p);
		}
		swap(vec,vec2);
	}
}tot,A,B;
void merge(){
	for(int i=(int)A.vec.size()-1; i>=1; i--) A.vec[i].fi-=A.vec[i-1].fi, A.vec[i].se-=A.vec[i-1].se;
	for(int i=(int)B.vec.size()-1; i>=1; i--) B.vec[i].fi-=B.vec[i-1].fi, B.vec[i].se-=B.vec[i-1].se;
 
	vector<pair<ll,ll>>V;
	V.resize(A.vec.size()+B.vec.size()-1);
 
	merge(A.vec.begin()+1,A.vec.end(),B.vec.begin()+1,B.vec.end(),V.begin()+1,
	[](pair<ll,ll> S, pair<ll,ll> T){
		return (__int128)S.se*T.fi > (__int128)T.se*S.fi;
	});
 
	for(int i=1;i<V.size();i++) V[i].fi+=V[i-1].fi, V[i].se+=V[i-1].se;
	for(auto p: V) tot.ins(p);
}
void solve(int l,int r){
	if(l==r){
		if(a[l]==-1)tot.ins({1,0});
		else tot.ins({0,a[l]});
		return;
	}
	int mid=(l+r)>>1;

	A.clear(),B.clear();
	ll c0=0,c1=0;
	for(int i=mid;i>=l;i--){
		if(a[i]==-1) c0++; else c1+=a[i];
		A.ins({c0,c1});
	}
	c0=c1=0;
	for(int i=mid+1;i<=r;i++){
		if(a[i]==-1) c0++; else c1+=a[i];
		B.ins({c0,c1});
	}
	A.simplify(), B.simplify();
	merge();
	solve(l,mid); solve(mid+1,r);
}
pair<ll,ll> qq[1000005];
ll ans[1000005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();

	solve(1,n);
	tot.simplify();

	vector<pair<ll,ll>>ok=tot.vec;
	// for(auto [x,y]: ok){
	// 	cout<<x<<","<<y<<endl;
	// }


	for(int i=1;i<=q;i++){
		qq[i].fi=-read(); qq[i].se=i;
	}
	sort(qq+1,qq+q+1);

	int pt=0;
	for(int i=1;i<=q;i++){
		ll w=qq[i].fi;
		while(pt+1 < ok.size() && ok[pt].fi*w+ok[pt].se < ok[pt+1].fi*w+ok[pt+1].se) pt++;
		ans[qq[i].se] = ok[pt].fi*w+ok[pt].se;
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
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