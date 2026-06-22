// created time: 2026-06-22 18:39:54
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

int n,val[200005],cnt[18],pop[18]; char s[18][200005];
int seq[18];

void procedure(){
	n=read();
	int p=lg2(2*n+1);
	for(int i=0;i<p;i++){
		scanf("%s",s[i]+1);
		pop[i]=0,seq[i]=i;
		for(int j=1;j<=n;j++)pop[i]+=(s[i][j]=='1');
	}

	// cout<<"testcase"<<endl;

	
	for(int i=0;i<p;i++){
		cnt[i]=0;
		for(int j=1;j<=n;j++)cnt[i]+=((j>>i)&1);
	}

	sort(seq,seq+p,[](int x,int y){ return pop[x]>pop[y]; });

	ll ans=1,ok=1,prv=-1;
	for(int i=0;i<p;i++){
		// cout<<seq[i]<<endl;
		if(pop[seq[i]]!=prv) ok=1,prv=pop[seq[i]];
		else ok++,ans*=ok;
	}

	set<int>st;
	for(int i=1;i<=n;i++){
		int v=0;
		for(int j=0;j<p;j++)
			v|=((s[seq[j]][i]-'0')<<j);
		st.emplace(v);
	}
	if(st.size()==n && *st.begin()==1 && *prev(st.end())==n){
		printf("%lld\n", ans);
	}else
		puts("0");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}