// created time: 2026-08-26 15:51:31
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
inline ull lg2(ull x){ return 63^__builtin_clzll(x); }
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
const int B = 64, NN = 10005;
int n,m,k,a[20005][105],sum[20005];
int ord[20005];

int f[105],N;

ull dp[105][NN/B+5];
void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)sum[i]+=(a[i][j]=read());

	for(int i=1;i<=n;i++) ord[i]=i;	
	sort(ord+1,ord+n+1,[&](int x,int y){
		return sum[x]==sum[y]?x>y:sum[x]<sum[y];
	});

	sum[ord[n+1]=n+1]=m*k;
	memset(f,0x3f,sizeof(f));
	f[0]=-1;

	for(int w=1;w<=n;w++){
		int x=ord[w];
		int L=sum[ord[w-1]],M=sum[ord[w]],R=sum[ord[w+1]];
		int cnt=(R-L)/k;

		N=(M-L)/B;
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<=N;j++)dp[i][j]=0;
		dp[0][0]=1;

		for(int j=1;j<=m;j++){
			auto [t,v]=div(a[x][j],B);
			for(int s=cnt;s>=1;s--){
				if(v){
					for(int i=0;i+t<=N;i++){
						dp[s][i+t] |= (dp[s-1][i]&((1ull<<B-v)-1))<<v;
						dp[s][i+t+1] |= dp[s-1][i]>>B-v;
					}
				}else
					for(int i=0;i+t<=N;i++)
						dp[s][i+t] |= dp[s-1][i];
			}
		}

		if(ord[w]>ord[w-1]) 
			for(int i=0;i<=m;i++) f[i]++;

		// cout<<"#adding "<<ord[w]<<endl;
		// for(int i=0;i<=m;i++)cout<<(f[i]>1e9?-1:f[i])<<" "; cout<<endl;

		for(int i=m;i>=0;i--){
			if(f[i]<=M){ f[i]=M; continue; }
			f[i]=0x3f3f3f3f;
			for(int j=max(0,i-cnt),x;j<i;j++){
				int dc=M-f[j]; if(dc<0)continue;

				int final=-1;
				auto [t,v]=div(dc,B);

				ull sta=(v+1==B?0:(1ull<<v+1))-1;

				if(dp[i-j][t]&sta)
					final=B*t+lg2(dp[i-j][t]&sta);
				else
					while(--t>=0)
						if(dp[i-j][t]){ final=B*t+lg2(dp[i-j][t]); break; }

				// assert(final<=dc);
				if(~final){
					chkmin(f[i],M+k*(i-j)-final);
					// if(w==2 && i==50){
					// 	cout<<i<<" come from "<<j<<" was "<<f[j]<<" final="<<final<<endl;
					// }
				}
			}
		}
		// for(int i=0;i<=m;i++)cout<<(f[i]>1e9?-1:f[i])<<" "; cout<<endl;
	}
	int ans=0;
	for(int i=m;i>=0;i--)
		if(f[i]<=1e9){ ans=i; break;}
	printf("%d\n",n*m-ans);
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