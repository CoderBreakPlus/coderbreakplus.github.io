// created time: 2026-10-17 08:24:37
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n,k,mod;
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
const int N = 10000000;
int fac[N+5],inv[N+5];
int pw2[N+5],iv2[N+5];
void math_init(){
	fac[0]=inv[0]=pw2[0]=iv2[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod,addmod(pw2[i]=pw2[i-1]*2);
	inv[N]=qpow(fac[N],mod-2),iv2[N]=qpow(pw2[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod,addmod(iv2[i]=iv2[i+1]*2);
}
inline int binom(int x,int y){
	if(x==-1&&y==-1)return 1;
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
struct Mod{
	ll m,p;
	void init(int pp){m=((__int128)1<<64)/pp;p=pp;}
	inline ll operator()(ll x){
		ll r=x-((__int128)x*m>>64)*p;
		if(r>=p)r-=p;
		return r;
	}
}node;
namespace k1{
	void main(){
		int ans=0;
		for(int k=0;k<=n;k++){
			if(k&1)
				ans=(ans+(ull)(mod-binom(n,k))*pw2[(n-k)*(n-k-1)/2])%mod;
			else
				ans=(ans+(ull)binom(n,k)*pw2[(n-k)*(n-k-1)/2])%mod;
		}
		printf("%d\n",ans);
	}
}
namespace k2{
	int cf0[3005];
	void main(){
		cf0[0]=1;
		if(n)cf0[1]=1;
		for(int i=2;i<=n;i++)
			cf0[i]=(cf0[i-1]+(ll)(i-1)*cf0[i-2])%mod;
		int ans=0;
		for(int k=0;k<=n;k++){
			int cf1=1;
			int cf2=(ll)binom(n,k)*pw2[(n-k)*(n-k-1)/2]%mod;
			for(int d=0;d<=k;d++){
				int all=(ll)cf0[k-d]*cf1%mod*cf2%mod*binom(k,d)%mod;
				if(k&1)all=mod-all;
				addmod(ans+=all);
				cf1=(ll)cf1*(n-k)%mod;
			}
		}
		printf("%d\n",ans);
	}
}
namespace k3{
	int f[6005][3005],sum[3005];
	inline void upd(int &a,ll b){ a=node(a+b); }
	void main(){
		f[0][0]=1;
		for(int j=0;j<=2*n;j++){
			memset(sum,0,sizeof(sum));
			for(int i=0;i<=n;i++){
				if(i>=3)
					upd(f[j][i],node((ll)sum[i-3]*fac[i-1])*iv2[1]);
				
				ll F=f[j][i];
				addmod(f[j][i+1]+=F);

				sum[i]=node((ll)f[j][i]*inv[i]);
				if(i) addmod(sum[i]+=sum[i-1]);
			}
			memset(sum,0,sizeof(sum));
			for(int i=0;i<n;i++){
				ll F=f[j][i];
				upd(f[j+2][i+1], F*iv2[1]);
				upd(f[j+1][i+1], (mod-F)*iv2[1]);
			}
			for(int i=0;i<=n;i++){
				int F=node(node((ll)f[j][i]*inv[i])*(mod-i));
				sum[i]=F;
				if(i) addmod(sum[i]+=sum[i-1]);
				if(i>=2) upd(f[j+2][i],node((ll)sum[i-2]*fac[i-1])*iv2[1]);
			}
			memset(sum,0,sizeof(sum));
			for(int i=0;i<=n;i++){
				int F=node((ll)f[j][i]*inv[i]);
				sum[i]=F;
				if(i) addmod(sum[i]+=sum[i-1]);
				if(i>=2) upd(f[j+2][i],node(node((ll)sum[i-2]*fac[i-1])*iv2[1])*i);
			}
		}
		int ans=0;
		for(int i=0;i<=n;i++){
			int tot=0,now=1;
			for(int j=0;j<=2*n;j++){
				int all=node((ll)now*f[j][i]);
				addmod(tot+=all);
				now=node((ll)now*(n-i+1));
			}
			if(i&1)tot=mod-tot;
			ans=(ans+(ll)tot*binom(n,i)%mod*pw2[(n-i)*(n-i-1)/2])%mod;
		}
		printf("%d\n",ans);
	}
}
void procedure(){
	n=read(),k=read(),mod=read();
	node.init(mod);
	math_init();

	if(k==1){
		k1::main();
	}else if(k==2){
		k2::main();
	}else
		k3::main();
}
int main(){
	#ifdef LOCAL
		assert(freopen("leader.in","r",stdin));
		assert(freopen("leader.out","w",stdout));
	#endif
	procedure();
	return 0;
}