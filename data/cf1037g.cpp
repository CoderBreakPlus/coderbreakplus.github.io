// created time: 2026-09-18 08:14:23
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
int n,m;
vector<pair<int,int>>vc[100005];

int pr[26][100005],nx[26][100005],val[26][100005];
int sl[26][100005],sr[26][100005];

void procedure(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)
		pr[s[i]-'a'][i]=nx[s[i]-'a'][i]=i;

	for(int o=0;o<26;o++){
		for(int i=1;i<=n;i++)
			pr[o][i]=(pr[o][i]?:pr[o][i-1]);
		nx[o][n+1]=n+1;
		for(int i=n;i>=1;i--)
			nx[o][i]=(nx[o][i]?:nx[o][i+1]);
	}
	for(int i=1;i<=n;i++){
		for(int o=0;o<26;o++)if(s[i]-'a'!=o)
			vc[i].pb(nx[o][i]-1,0),
			vc[pr[o][i]+1].pb(i,0);
	}
	auto qry=[&](int l,int r){
		unsigned ret=0;
		for(int o=0;o<26;o++){
			int L=nx[o][l],R=pr[o][r];
			if(L>R)continue;
			int cur=sl[o][l]^sr[o][r]^val[o][L]^val[o][R];
			ret|=(1<<cur);
		}
		return __builtin_ctz(~ret);
	};
	for(int l=n;l>=1;l--){
		sort(vc[l].begin(),vc[l].end());
		vc[l].erase(unique(vc[l].begin(),vc[l].end()),vc[l].end());

		for(int o=0;o<26;o++)val[o][l-1]=val[o][l];
		for(auto &[r,v]:vc[l]){
			v=qry(l,r);
			bool f0=(r<n&&nx[s[r+1]-'a'][l]==r+1);
			bool f1=(l>1&&pr[s[l-1]-'a'][r]==l-1);
			if(f0) sl[s[r+1]-'a'][l]=v;
			if(f1) sr[s[l-1]-'a'][r]=v;
			if(f0&&f1&&s[l-1]==s[r+1]) val[s[l-1]-'a'][l-1]^=v;
		}
	}
	m=read();
	while(m--){
		int l=read(),r=read();
		puts(qry(l,r)?"Alice":"Bob");
	}
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