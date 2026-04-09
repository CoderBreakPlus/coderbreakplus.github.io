// created time: 2026-04-09 08:22:30
// https://qoj.ac/contest/1924/problem/10122
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
int n,k; string s[100005];
const ull mod = (ull)1e18 + 3, base = rng(1e8,1e9);

map<ull,int>id; int t;
set<int>in[200005],out[200005];

ull hi[100005],ho[100005];

int getid(ull x){
	if(!id.count(x))id[x]=++t;
	return id[x];
}
void procedure(){
	cin>>n>>k;
	for(int i=1;i<=k;i++)cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<k;j++)ho[i]=((__int128)ho[i]*base+s[j][i])%mod;
		for(int j=2;j<=k;j++)hi[i]=((__int128)hi[i]*base+s[j][i])%mod;

		// cout<<hi[i]<<" "<<ho[i]<<endl;
		in[getid(hi[i])].emplace(i);
		out[getid(ho[i])].emplace(i);
	}
	for(int i=1;i<=t;i++)if(in[i].size()!=out[i].size()){cout<<"NO\n";return;}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		set<int> &p=in[getid(ho[i])];
		int x=*p.begin(); p.erase(p.begin());
		cout<<x<<" ";
	}
	cout<<"\n";
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios::sync_with_stdio(0);cin.tie(0);
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}