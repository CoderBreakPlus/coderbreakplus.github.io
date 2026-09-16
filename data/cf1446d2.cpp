// created time: 2026-09-16 14:50:47
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

int n,a[200005],cnt[200005],nxt[200005],prv[200005],ans;
vector<int>p[200005];

int lf[200005],rh[200005],v[200005];

int seq[200005],t;
int pool[400005];
int *buc=pool+200000;

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)p[i]={0};
	for(int i=1;i<=n;i++)
		p[a[i]=read()].pb(i);
	for(int i=1;i<=n;i++)p[i].pb(n+1);

	int mx=0;
	for(int c=1;c<=n;c++)if(p[c].size()>p[mx].size())mx=c;

	for(int x:p[mx]) nxt[x]=prv[x]=x,cnt[x]++;
	for(int i=1;i<=n+1;i++)cnt[i]+=cnt[i-1];
	
	for(int i=n;i>=0;i--)
		nxt[i]=nxt[i]?:nxt[i+1];
	for(int i=1;i<=n+1;i++)
		prv[i]=prv[i]?:prv[i-1];

	memset(pool,-1,sizeof(pool));
	for(int c=1;c<=n;c++)if(mx!=c&&p[c].size()>=3){
		int sz=p[c].size()-2;
		for(int i=0;i<=sz;i++) v[i]=cnt[p[c][i+1]]-cnt[p[c][i]];
		for(int i=1;i<=sz;i++) lf[i]=1+max(0,lf[i-1]-v[i-1]);
		for(int i=sz;i>=1;i--) rh[i]=1+max(0,rh[i+1]-v[i]);

		t=0;
		for(int i=0;i<=sz;i++){
			if(i) seq[++t]=p[c][i];
			if(lf[i]+rh[i+1]+2>=v[i]){
				int cur=p[c][i];
				while(nxt[cur+1]<p[c][i+1]){
					cur=nxt[cur+1];
					seq[++t]=cur;
				}
				continue;
			}
			int x=p[c][i],y=p[c][i+1];
			for(int s=1;s<=lf[i]+1;s++) seq[++t]=x=nxt[x+1];
			for(int s=1;s<=rh[i+1]+1;s++) seq[++t]=y=prv[y-1];
			reverse(seq+t-rh[i+1],seq+t+1);
		}

		seq[0]=0,seq[t+1]=n+1;

		int sum=0;
		buc[0]=0;
		for(int i=1;i<=t;i++){
			sum+=(a[seq[i]]==mx?-1:1);
			if(~buc[sum]){
				chkmax(ans, seq[i+1]-seq[buc[sum]]-1);
			}else buc[sum]=i;
		}

		for(int i=-t;i<=t;i++) buc[i]=-1;
		for(int i=0;i<=sz+1;i++) lf[i]=rh[i]=v[i]=0;
	}

	printf("%d\n",ans);
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