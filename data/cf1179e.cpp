// created time: 2026-09-21 07:47:51
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

ll n,L,B,al[1005],ar[1005],pt[1005],bas[1005];
vector<ll>vc[1005];

ll query(int i,ll x){
	cout<<"? "<<i<<" "<<x<<endl;
	#ifdef LOCAL
		return upper_bound(vc[i].begin(),vc[i].end(),x)-vc[i].begin();
		// return min(5ll,x);
	#endif
	ll ret; cin>>ret; return ret;
}
ll cnt1=0,cnt2=0;
void solve(ll l,ll r,ll L,ll R,vector<ll> vec){
	assert(vec.size()==r-l);
	if(r-l==1){
		al[vec[0]]=L,ar[vec[0]]=R;
		return;
	}
	ll m=(l+r)>>1;

	vector<ll>sl,sr; ll sz=m-l,lst=-1;
	
	auto getval=[&](ll x){
		ll lft=L,rht=R; pt[x]=-1;
		while(lft<=rht){
			ll mid=(lft+rht)>>1;
			if(query(x,mid)>=m*B){
				pt[x]=mid;
				rht=mid-1;
			}else lft=mid+1;
		}
		assert(~pt[x]);
	};

	while(!vec.empty() && sz!=vec.size() && sz!=0){
		shuffle(vec.begin(),vec.end(),rnd);
		vector<ll>lft,rht,middle;
		getval(vec[0]); lst=pt[vec[0]];
		cnt1++;
		for(int i=1;i<vec.size();i++){
			cnt2++;
			ll val=query(vec[i],lst);

			if(val<m*B) rht.pb(vec[i]);
			else if(query(vec[i],lst-1)>=m*B) lft.pb(vec[i]);
			else middle.pb(vec[i]);
		}
		for(ll x:middle) (lft.size()<rht.size())?(lft.pb(x)):(rht.pb(x));
		
		if(lft.size()<sz){
			sz-=lft.size()+1,sl.pb(vec[0]);
			for(ll x:lft) sl.pb(x); vec=rht;
		}else{
			sr.pb(vec[0]);
			for(ll x:rht) sr.pb(x); vec=lft;
		}
	}
	while(sz--) sl.pb(vec.back()),vec.pop_back();
	while(!vec.empty()) sr.pb(vec.back()),vec.pop_back();

	solve(l,m,L,lst,sl);
	solve(m,r,lst,R,sr);
}
void procedure(){
	cin>>n>>L; B=L/n;
	#ifdef LOCAL
	for(int i=1;i<=n;i++){
		for(int j=1;j<=L;j++)vc[i].pb(rng(0,1e18));
		sort(vc[i].begin(),vc[i].end());
	}
	#endif
	vector<ll>vec;
	for(ll i=1;i<=n;i++)vec.pb(i);
	solve(0,n,0,1e18,vec);
	cout<<"!"<<endl;
	for(ll i=1;i<=n;i++) cout<<al[i]<<" "<<ar[i]<<endl;
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