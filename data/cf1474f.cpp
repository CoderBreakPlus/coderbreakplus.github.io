// created time: 2026-09-17 08:38:25
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

int n,m,c,d[55];
ll s[55],t[55];
int f[55][55][55],g[55][55][55],pre[55][55][55];

int find_id(ll x){ return lower_bound(t,t+n+1,x)-t; }
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(ll x,int y){
	if(x==-1&&y==-1)return 1;
	if(x<0 || y<0 || x<y) return 0;
	x%=mod;
	int ans=inv[y];
	for(int i=x;i>x-y;i--)ans=(ull)ans*(mod+i)%mod;
	return ans;
}

void procedure(){
	m=read(); read(); s[0]=1e18;
	bool flg=1;

	for(int i=1;i<=m;i++){
		d[i]=read();
		flg&=(d[i]<=0);
		if((ll)d[i]*d[i-1]>0)s[n]+=d[i];
		else s[n+1]=s[n]+d[i],++n;
	}

	if(flg){
		printf("1 %d\n",(int)((-s[n]+(ll)1e18+1)%mod));
		return;
	}
	s[n+1]=-1e18;
	for(int i=0;i<=n;i++)t[i]=s[i];
	sort(t,t+n+1);
	c=unique(t,t+n+1)-(t+1);

	for(int i=0;i<c;i++) 
		for(int j=0;j<=n;j++)for(int k=0;j+k<=n;k++)
			pre[i][j][k]=binom(t[i+1]-t[i]-k-1,j-1);
	ll mx=0; int ans=0;
	ll lst=-1145141919810ll;

	for(int x=0;x<n;x++){
		ll tmp=0;
		for(int y=x;y<=n;y++)chkmax(tmp,s[y]);
		ll dis=tmp-s[x];
		if(dis>mx) mx=dis, ans=0;
		else if(dis<mx) continue;

		if(s[x]==lst)continue;
		lst=s[x];
		memset(f,0,sizeof(f));

		f[find_id(s[x])][0][0]=1;
		for(int z=x;z<=n;z++){
			int w=n;
			int type=(s[z+1]>s[z]);
			if(type){
				for(int i=0;i<c;i++){
					if(!(s[z]<=t[i] && t[i+1]<=s[z+1])) continue;
					for(int j=n;j>=0;j--)for(int k=0;j+k<=n;k++){
						addmod(f[i][j+1][k] += f[i][j][k]);
					}
					if(i){
						for(int j=n;j>=0;j--)for(int k=0;j+k<=n;k++){
							f[i][1][0]=(f[i][1][0]+(ull)f[i-1][j][k]*pre[i-1][j][k])%mod;
						}
					}
				}
			}else{
				for(int i=c;i>=0;i--){
					if(!(s[z]>=t[i] && t[i]>=s[z+1])) continue;
					for(int j=n;j>=0;j--)for(int k=n-j;k>=0;k--){
						if(!j&&!k&&s[z+1]==t[i])continue;
						if((j||k)&&s[z]==t[i])continue;

						addmod(f[i][j][k+1] += f[i][j][k]);
					}
					if(i && s[z+1]<t[i]){
						int ok=0;
						for(int j=n;j>=0;j--)for(int k=0;j+k<=n;k++){
							ok=(ok+(ull)f[i-1][j][k]*pre[i-1][j][k])%mod;
						}
						addmod(f[i][0][1]+=ok);
						if(t[i]==tmp){
							addmod(ans+=ok);
						}
					}
				}
			}
		}
	}
	printf("%lld %d\n",mx+1,ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}