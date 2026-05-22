// created time: 2026-05-22 18:56:35
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
mt19937_64 rnd(1233);
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,tb[505][505];
vector<pair<int,int>>ans,ans2;

void link(int x,int y){
	if(x>y)swap(x,y);
	ans.pb(x,y);
}
int qry(vector<int> v){
		cout<<"? "<<v.size()<<" ";
		for(int x:v) cout<<x<<" ";cout<<endl;
	#ifndef LOCAL
		int res;cin>>res;return res^1;
	#endif
	#ifdef LOCAL
		for(int x:v)for(int y:v)
			if(tb[x][y])return 1;
		return 0;
	#endif
}

void check(int x,vector<int>cur){
	int s=0, sz=cur.size();
	while(s<sz){
		int l=s,r=sz-1,ans=sz;
		while(l<=r){
			int mid=(l+r)>>1;
			vector<int>ok={x};
			for(int i=l;i<=mid;i++) ok.pb(cur[i]);
			if(qry(ok)){
				ans=mid;
				r=mid-1;
			}else l=mid+1;
		}
		// if(ans==sz)break;
		link(x,cur[ans]);
		s=ans+1;

		vector<int>tmp={x};
		for(int i=ans+1;i<sz;i++)
			tmp.pb(cur[i]);
		if(!qry(tmp)) break;
	}
}
void solve(vector<int>v){
	if(v.empty())return;
	int sz=v.size();
	vector<int>cur={v[0]},icur;
	for(int i=1;i<sz;i++){
		cur.pb(v[i]);
		if(qry(cur)) cur.pop_back(),icur.pb(v[i]);
	}
	for(int x:icur) check(x,cur);
	solve(icur);
}
void procedure(){	
	cin>>n;
	ans.clear(),ans2.clear();

	#ifdef LOCAL
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)tb[i][j]=0;
		int m = 500, b = n*(n-1)/2/m;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)if(rnd()%b==0){
				ans2.pb(i,j),tb[i][j]=tb[j][i]=1;
			}
	#endif
	vector<int>res;
	for(int i=1;i<=n;i++) res.pb(i);
	solve(res);

	sort(ans.begin(),ans.end());

	cout<<"! "<<ans.size()<<" ";
	for(auto [x,y]: ans) cout<<x<<" "<<y<<" ";
	cout<<endl;

	#ifdef LOCAL
		// cout<<"! "<<ans2.size()<<" ";
		// for(auto [x,y]: ans2) cout<<x<<" "<<y<<" ";
		// cout<<endl;
		assert(ans==ans2);
	#endif
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T;cin>>T;
	// math_init();
	while(T--) procedure();
	return 0;
}