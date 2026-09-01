// created time: 2026-09-01 13:19:09
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
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
const int N = 400000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=(ull)fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=(ull)inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[x-y]%mod;
}

int n,p[200005],ip[200005],PW[200005],*pw=PW+1;
int vis[200005],qz[200005];

void upd(int &a, ull b){ a=(a+b)%mod; }

struct Quiz{
	int n,k,now;
	Quiz(){ n=k=0, now=1; }
	void addn(){
		now=(2ull*now+mod-binom(n++,k))%mod;
	}
	void deln(){
		now=(ull)(now+binom(--n,k))*((mod+1)/2)%mod;
	}
	void addk(){
		addmod(now+=binom(n,++k));
	}
	void delk(){
		addmod(now+=mod-binom(n,k--));
	}
	int qry(int N,int K){
		if(N<0||K<0)return 0;
		while(n<N)addn(); while(n>N)deln();
		while(k<K)addk(); while(k>K)delk();
		return now;
	}
}A0,A1,B0,B1;
struct Move{
	int fr,bk,now;
	void add0(){
		ull Now = now*2;
		int tmp=A0.qry(bk,fr); ull tmp2=tmp+mod-binom(bk-1,fr);
		Now+=bk*(tmp2+mod-pw[bk-1])+fr*(pw[bk]+2ull*(mod-tmp))+2ull*(pw[fr+bk]+mod-A1.qry(fr+bk,bk-1))
		+(ull)(mod-2)*tmp+(ull)(pw[fr]-1)*(mod-pw[bk]);

		fr++;
		
		tmp=A0.qry(bk,fr),tmp2=binom(bk-1,fr)+mod-tmp;
		Now+=bk*(tmp2+pw[bk-1])+fr*(2ull*tmp+mod-pw[bk]);

		now=Now%mod;
	}
	void del0(){
		ull Now=now;
		int tmp=A0.qry(bk,fr); ull tmp2=tmp+mod-binom(bk-1,fr);
		Now+=bk*(tmp2+mod-pw[bk-1])+fr*(pw[bk]+2ull*(mod-tmp));

		fr--;

		tmp=A0.qry(bk,fr),tmp2=binom(bk-1,fr)+mod-tmp;

		Now+=(ull)2*tmp+(ull)(pw[fr]-1)*pw[bk]+(ull)(mod-2)*(pw[fr+bk]+mod-A1.qry(fr+bk,bk-1))%mod
		+bk*(tmp2+pw[bk-1])+fr*(2ull*tmp+mod-pw[bk]);

		now=(ull)Now%mod*((mod+1)/2)%mod;
	}
	void add1(){
		ull Now = now*2;
		int tmp=B0.qry(fr,bk); ull tmp2=tmp+mod-binom(fr-1,bk);
		Now+=fr*(tmp2+mod-pw[fr-1])+bk*(pw[fr]+2ull*(mod-tmp))+2ull*(pw[bk+fr]+mod-B1.qry(bk+fr,fr-1))
		+(ull)(mod-2)*tmp+(ull)(pw[bk]-1)*(mod-pw[fr]);

		bk++;
		
		tmp=B0.qry(fr,bk),tmp2=binom(fr-1,bk)+mod-tmp;
		Now+=fr*(tmp2+pw[fr-1])+bk*(2ull*tmp+mod-pw[fr]);

		now=Now%mod;
	}
	void del1(){
		ull Now=now;
		int tmp=B0.qry(fr,bk); ull tmp2=tmp+mod-binom(fr-1,bk);
		Now+=fr*(tmp2+mod-pw[fr-1])+bk*(pw[fr]+2ull*(mod-tmp));

		bk--;

		tmp=B0.qry(fr,bk),tmp2=binom(fr-1,bk)+mod-tmp;
		
		Now+=(ull)2*tmp+(ull)(pw[bk]-1)*pw[fr]+(ull)(mod-2)*(pw[bk+fr]+mod-B1.qry(bk+fr,fr-1))%mod
		+fr*(tmp2+pw[fr-1])+bk*(2ull*tmp+mod-pw[fr]);

		now=(ull)Now%mod*((mod+1)/2)%mod;
	}
}Box;

const int B = 320;

int c[200005];
void upd(int x,int w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
int qry(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}

int AA[200005],BB[200005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)ip[p[i]=read()]=i;

	int ans=0;
	
	for(int x=n;x>=1;x--){
		int i=ip[x];
		AA[i]=qry(i), BB[i]=n-i-qry(n)+qry(i);		
		ans = (ans + (ull)AA[i] * pw[n-2]) % mod;
		upd(i,1);
	}

	vector<int> vec;
	for(int i=1;i<=n;i++)vec.pb(i);

	sort(vec.begin(), vec.end(), [](int x, int y){
	    int bx = AA[x] / B, by = AA[y] / B;
	    if (bx != by) return bx < by;
	    return (bx & 1) ? BB[x] < BB[y] : BB[x] > BB[y];
	});

	for(int i:vec){
		int fr=AA[i],bk=BB[i];
		while(Box.fr<fr) Box.add0();
		while(Box.fr>fr) Box.del0();
		while(Box.bk<bk) Box.add1();
		while(Box.bk>bk) Box.del1();
		ans = (ans + (ull)Box.now * pw[n-1-fr-bk]) % mod;
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	pw[0]=1;
	for(int i=1;i<=2e5;i++)pw[i]=(ull)pw[i-1]*2%mod;

	math_init();
	while(T--) procedure();
	return 0;
}