#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

int n,m,a[15],b[15];
string s[200005];
bool ok[15][15][26];

void procedure(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i],b[i]--;
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>s[i];
		for(int j=0;j<s[i].size();j++)
			ok[s[i].size()][j][s[i][j]-'a']=1;
	}

	for(int i=1;i<=m;i++){
		if(s[i].size()!=n){
			cout<<"No\n";
			continue;
		}
		bool f=1;
		for(int j=1;j<=n;j++){
			f&=(ok[a[j]][b[j]][s[i][j-1]-'a']);
			// if(!f){
			// 	cout<<"fail on "<<j<<endl;
			// }
		}
		if(f) cout<<"Yes\n";
		else cout<<"No\n";
	}	
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}