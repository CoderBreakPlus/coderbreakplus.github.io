// created time: 2026-09-10
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

int n,k,a[1005],f[1005],buc[1005];
ull w[1005];

unordered_map<ull,pair<int,int>>S;

void procedure(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	ull all=0;
	for(int i=1;i<=k;i++)all^=(w[i]=rnd());

	for(int i=1;i<=k;i++)
		for(int j=i+1;j<=k;j++)
			S[all^w[i]^w[j]]={i,j};

	for(int i=n;i>=k;i-=2){
		f[i]=0;
		memset(buc,0,sizeof(buc));
		ull tmp=all;

		map<pair<int,int>,int>mp;
		for(int j=i+2;j<=n;j+=2){
			tmp^=w[a[j-1]]^w[a[j]];
			buc[a[j-1]]++,buc[a[j]]++;
			if(S.count(tmp)&&!mp.count(S[tmp])){
				chkmax(f[i],f[j]+(j-i)/2-1);
				mp[S[tmp]]=1;
			}
		}

		if(mp.size()==k*(k-1)/2) continue;

		int cnt=0,sb=-1;
		for(int j=1;j<=k;j++){
			sb+=(buc[j]+1)/2;
			// cout<<"contri "<<buc[j]+1<<endl;
			if(!(buc[j]&1))cnt++;//cout<<"need balance "<<j<<endl;
		}
		// cout<<"sb = "<<sb<<endl;

		int f1=cnt*(cnt-1)/2;
		int f0=cnt*(k-cnt);
		
		for(auto [p,q]: mp){
			auto [x,y]=p;
			// cout<<"ban "<<x<<","<<y<<endl;
			if(!(buc[x]&1)&&!(buc[y]&1))f1--;
			else if(!(buc[x]&1)||!(buc[y]&1))f0--;
		}
		if(f1) sb++;
		else if(!f0) sb--;
		chkmax(f[i], sb);
		// cout<<"at "<<i<<" f = "<<f[i]<<endl;
	}

	int pt=k; ull now=0;
	for(int i=1;i<=k;i++)now^=w[a[i]];
	while(pt<n && now!=all){
		now^=w[a[++pt]];
		now^=w[a[++pt]];
	}

	if(pt==n&&now!=all){
		memset(buc,0,sizeof(buc));
		for(int j=1;j<=n;j++)buc[a[j]]++;

		int ans=0;
		for(int j=1;j<=k;j++)ans+=buc[j]/2;
		printf("%d\n",ans);
		return;
	}

	printf("%d\n",f[pt]+(pt-k)/2);
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