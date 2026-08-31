// created time: 2026-08-31 08:56:02
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

char s[100005];
int n,fa[100005];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
vector<int> hd;

void query(vector<pair<int,int>> vec){
	if(vec.empty())return;
	cout<<"Q "<<vec.size()<<" ";
	for(auto [x,y]: vec) cout<<x<<" "<<y<<" ";
	cout<<endl;	
	
	if(!(cin>>s))exit(0);
	for(int i=0;i<vec.size();i++)
		if(s[i]=='1')fa[find(vec[i].se)]=find(vec[i].fi);
}
int col[100005];
vector<int>st[4];

void procedure(){
	cin>>n; hd={};
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i:{1,2,3})st[i].clear();

	vector<pair<int,int>>V;
	for(int i=1;i<n;i+=2)V.pb(i,i+1);
	query(V);
	V.clear(); for(int i=2;i<n;i+=2)V.pb(i,i+1);
	query(V);

	for(int i=1;i<=n;i++)if(find(i)==i)hd.pb(i);//cout<<i<<" "; cout<<endl;

	V.clear();
	for(int i=0;i<hd.size();i++){
		if(i%4==2) i+=2;
		if(i+2>=hd.size()) break;
		V.pb(hd[i],hd[i+2]);
	}
	query(V);

	V.clear();
	for(int i=2;i<hd.size();i++){
		if(i%4==0) i+=2;
		if(i+2>=hd.size()) break;
		V.pb(hd[i],hd[i+2]);
	}

	query(V);

	for(int i=0;i<hd.size();i++){
		if(i<=1) {col[hd[i]]=i+1;continue;}
		if(find(hd[i])!=hd[i]) col[hd[i]]=col[find(hd[i])];
		else col[hd[i]]=col[hd[i-1]]^col[hd[i-2]];
	}

	for(int i=1;i<=n;i++)
		st[col[find(i)]].pb(i);

	cout<<"A "<<st[1].size()<<" "<<st[2].size()<<" "<<st[3].size()<<endl;
	for(int i:{1,2,3}){
		for(int x: st[i]) cout<<x<<" ";
		cout<<endl;
	}
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