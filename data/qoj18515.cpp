// created time: 2026-06-18 07:29:41
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
int n,qmax,ans[30005],cnt,lst;
char b[30005];

char query(int x){
	cout<<"? "<<x<<endl;
	cnt++;
	char s[5];
	#ifdef LOCAL
		if(!lst) s[0]='=';
		else{
			if(ans[lst]>ans[x]) s[0]='>';
			else if(ans[lst]==ans[x]) s[0]='<';
			else s[0]='<';
		}
		lst=x;
	#endif
	#ifndef LOCAL
		cin>>s;
	#endif
	if(s[0]=='-') exit(0);
	else return s[0];	
}

int lst1[30005],lst2[30005];
void procedure(){
	cin>>n>>qmax;
	int pos=0;
	#ifdef LOCAL
		for(int i=1;i<=n;i++) ans[i]=i;
		shuffle(ans+1,ans+n+1,rnd);
		for(int i=1;i<=n;i++)
			if(ans[i]==1)pos=i;
	#endif

	vector<int>a;
	for(int i=1;i<=n;i++)a.pb(i);
	shuffle(a.begin(),a.end(),rnd);

	int lst=0, ans=0, fk=0;
	for(int i=1;i<n;i++){
		char p=query(a[i]);
		if(p=='<') lst=i;
		else{
			fk++;
			char q=query(a[ans]);
			lst=ans;
			if(q=='<') ans=i;
		}
	}
	// cerr<<"fk="<<fk<<endl;
	cout<<"! "<<a[ans]<<endl;
	#ifdef LOCAL
		cout<<"ans="<<pos<<" cnt="<<cnt<<endl;
	#endif
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