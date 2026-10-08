// created time: 2026-10-08 19:18:49
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+3579;
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

const int v0=383200759, v1=616802823, is5=153280303;
int n,m,inv[105],ifac[105],fac[105];
vector<int>E[105];
inline void add(int &a,ull b){ a=(a+b)%mod; }

struct poly{
	vector<int> vec;
	poly(){ }
	poly(vector<int> v){ vec=v; }
	inline int& operator[](int x){ return vec[x]; }
	inline const int& operator[](int x)const{ return vec[x]; }
	uint size()const{ return vec.size(); }
	void resize(uint x){ vec.resize(max((uint)vec.size(),x),0); }
	void clr(){ vector<int>().swap(vec); }
};
inline poly& operator+= (poly &A, const poly &B){
	A.resize(B.size());
	for(int i=0;i<B.size();i++) addmod(A[i]+=B[i]);
	return A;
}
inline poly operator+ (poly A,const poly &B){ return A+=B; }
inline poly operator* (const poly &A,const poly &B){
	poly C; C.resize(max(0,(int)(A.size()+B.size()-1)));
	for(int i=0;i<A.size();i++)
		for(int j=0;j<B.size();j++)
			add(C[i+j], (ull)A[i]*B[j]);
	return C;
}
inline poly& operator*= (poly &A,const poly &B){ return A=A*B; }
inline poly& operator*= (poly &A,int B){ for(int &x: A.vec) x=(ull)x*B%mod; return A; }

poly dp[105][105][105], tmp[105][105];
int sz[105];

void dfs(int x,int fa){
	sz[x]=0;
	for(int y:E[x])if(y!=fa)dfs(y,x);

	dp[x][0][0]=poly({1});
	for(int y:E[x])if(y!=fa){
		for(int i=0;i<=sz[y];i++) for(int j=0;i+j<=sz[y];j++)
			for(int k=0;k<=sz[x];k++) for(int l=0;k+l<=sz[x];l++)
				tmp[i+k][j+l]+=dp[y][i][j]*dp[x][k][l];
		sz[x]+=sz[y];
		for(int i=0;i<=sz[x];i++) for(int j=0;i+j<=sz[x];j++){
			swap(dp[x][i][j],tmp[i][j]);
			tmp[i][j].clr();
		}
	}

	for(int i=0;i<=sz[x];i++)
		for(int j=0;i+j<=sz[x];j++){
			// gamma = (1,0)
			// P = dp[x][i][j]
			// H = P * e^((i,j)x)

			// G' = gamma * G + gamma * P * e^((i,j)x)
			// G = Q * e^((i,j)x) + C * e^((1,0)x)

			// Q' + dec * Q = gamma * P
			{
				poly P=dp[x][i][j]; P*=v0;
				int dec=((ull)(i+mod-1)*v0+(ull)j*v1)%mod;
				int idec=INV(dec); poly Q;
				if(!dec){
					Q.resize(P.size()+1);
					for(int i=0;i<P.size();i++)
						Q[i+1]=(ull)P[i]*inv[i+1]%mod;
				}else{
					int lst=0;
					Q.resize(P.size());
					for(int i=P.size()-1;i>=0;i--)
						lst=Q[i]=(P[i]+(ull)(i+1)*(mod-lst))%mod*idec%mod;
				}
				tmp[i][j]+=Q, tmp[1][0]+=poly({mod-(Q.size()?Q[0]:0)});
			}
			{
				poly P=dp[x][i][j]; P*=v1;
				int dec=((ull)i*v0+(ull)(j+mod-1)*v1)%mod;
				int idec=INV(dec);
				poly Q;
				if(!dec){
					Q.resize(P.size()+1);
					for(int i=0;i<P.size();i++)
						Q[i+1]=(ull)P[i]*inv[i+1]%mod;
				}else{
					int lst=0;
					Q.resize(P.size());
					for(int i=P.size()-1;i>=0;i--)
						lst=Q[i]=(P[i]+(ull)(i+1)*(mod-lst))%mod*idec%mod;
				}
				Q*=(mod-1);
				tmp[i][j]+=Q, tmp[0][1]+=poly({mod-(Q.size()?Q[0]:0)});
			}
		}
	sz[x]++;
	for(int i=0;i<=sz[x];i++)
		for(int j=0;i+j<=sz[x];j++){
			swap(dp[x][i][j],tmp[i][j]), tmp[i][j].clr();
			dp[x][i][j]*=is5;
		}
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}

	dfs(1,0);
	int ans=0;
	for(int i=0;i<=n;i++) for(int j=0;i+j<=n;j++){
		int now=((ull)v0*i+(ull)v1*j)%mod;
		int fall=1;
		for(int k=0;k<=m&&k<dp[1][i][j].size();k++){
			add(ans,(ull)dp[1][i][j][k]*fall%mod*qpow(now,m-k));
			fall=(ull)fall*(m-k)%mod;
		}
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int i=1;i<=100;i++)inv[i]=INV(i);
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}