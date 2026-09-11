// created time: 2026-09-11 14:01:46
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
// mt19937_64 rnd2(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,m,ans[100005],x,y,z,p[100005],ip[100005];

int query(int a,int b,int c){
	cout<<"? "<<a<<" "<<b<<" "<<c<<endl;
	#ifndef LOCAL
	int x; cin>>x; return x;
	#endif

	int A=abs(p[a]-p[b]),B=abs(p[b]-p[c]),C=abs(p[a]-p[c]);
	return A+B+C-max({A,B,C})-min({A,B,C});
}

void luvf(){
	x=rng(1,n-2),y=rng(1,n-2),z=rng(1,n-2);
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	y++,z+=2;
}
void procedure(){
	cin>>n;
	#ifdef LOCAL
		// for(int i=1;i<=n;i++)p[i]=i;
		// shuffle(p+1,p+n+1,rnd2);

		for(int i=1;i<=n;i++)cin>>p[i],ip[p[i]]=i;
		if(p[1]>p[2]){
			for(int i=1;i<=n;i++)p[i]=n-p[i]+1;
		}
	#endif
	luvf();
	while(query(x,y,z)>=n/6) luvf();

	vector<pair<int,int>>vec;
	for(int i=1;i<=n;i++)if(i!=x&&i!=y)
		vec.pb(query(x,y,i),i);

	sort(vec.begin(),vec.end(),greater<pair<int,int>>());

	int a,b;
	if(vec[0].fi==vec[1].fi){
		// cout<<"type1"<<endl;
		// assert(vec[2].fi==vec[0].fi-1);
		b=vec[2].se;

		int X=query(x,b,vec[0].se),Y=query(x,b,vec[1].se);
		if(X==Y)
			X=query(y,b,vec[0].se),Y=query(y,b,vec[1].se);
		if(X<Y)
			a=vec[0].se;
		else
			a=vec[1].se;
	}else if(vec[1].fi==vec[2].fi){
		a=vec[0].se;

		int X=query(x,a,vec[1].se),Y=query(x,a,vec[2].se);
		if(X==Y)
			X=query(y,a,vec[1].se),Y=query(y,a,vec[2].se);
		if(X<Y)
			b=vec[1].se;
		else
			b=vec[2].se;
	}else{
		a=vec[0].se,b=vec[1].se;
	}
	// cout<<"fucking find "<<a<<","<<b<<endl;
	ans[a]=1,ans[b]=2;
	for(int i=1;i<=n;i++)if(i!=a&&i!=b)
		ans[i]=query(i,a,b)+2;

	if(ans[1]>ans[2]){
		for(int i=1;i<=n;i++)ans[i]=n-ans[i]+1;
	}
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;

	#ifndef LOCAL
	int x; cin>>x; assert(x==1);
	#endif

	#ifdef LOCAL
	// cout<<"ip: "; for(int i=1;i<=n;i++) cout<<ip[i]<<" ";
	// cout<<endl;
	for(int i=1;i<=n;i++) assert(p[i]==ans[i]);
	#endif
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;cin>>T;
	// math_init();
	while(T--) procedure();
	return 0;
}