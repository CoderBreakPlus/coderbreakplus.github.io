
// created time: 2026-08-15
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
int cnt=0;
template<typename T>inline void addmod(T &x){ cnt++; if(x >= mod) x -= mod; }
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

const int B = 50, N = 205;
int n,a[N],f[N][N][N],g[3][N][N][N],h[N/B][N][N][N],M[N][N];

int nxt[N],nx[N][N],tmp[N],buc[N];

int seq[N],tl,id[N],lst[N],ord[N];

void procedure(){
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(buc,0,sizeof(buc));
	memset(id,-1,sizeof(id));
	memset(h,0,sizeof(h));
	memset(lst,0,sizeof(lst));

	tl=0;

	n=read();
	for(int i=1;i<=n;i++)buc[a[i]=read()]++,ord[i]=a[i];
	for(int i=0;i<=n;i++)tmp[i]=n+1;

	for(int i=n;i>=0;i--){
		if(tmp[a[i]]!=n+1)ord[i]=0;
		nxt[i]=tmp[a[i]],tmp[a[i]]=i;
	}

	for(int i=0;i<=n;i++){
		int now=n+1;
		for(int j=n;j>=0;j--){
			nx[j][i]=now;
			if(a[j]==i)now=j;
		}
	}

	for(int i=1;i<=n;i++){
		M[0][i]=1;
		char ss[205];
		scanf("%s",ss);
		for(int j=1;j<=n;j++)M[i][j]=ss[j-1]-'0';
	}

	for(int i=1;i<=n;i++)if(buc[i]>B)seq[tl]=i,id[i]=tl++;
	// cout<<"tl="<<tl<<endl;

	f[0][0][0]=1;
	int ans=mod-1;

	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(a[i]!=a[j]||a[i]!=a[k])continue;

				addmod(g[1][i][j][k]+=g[0][i][j][k]);
				addmod(g[0][nxt[i]][j][k]+=g[0][i][j][k]);

				addmod(g[2][i][j][k]+=g[1][i][j][k]);
				addmod(g[1][i][nxt[j]][k]+=g[1][i][j][k]);
				
				addmod(g[2][i][j][nxt[k]]+=g[2][i][j][k]);
				addmod(f[i][j][k]+=g[2][i][j][k]);

				// trans f

				if(i)
				for(int l=0;l<tl;l++)
					if(M[seq[l]][a[i]]) addmod(f[i][j][k] += h[l][i-1][j-1][k-1]);
				addmod(ans += f[i][j][k]);
				if(!~id[a[i]]){
					for(int l=max({i,j,k})+1;l<=n;l++){
						int c=ord[l];
						if(M[a[i]][c])
							addmod(g[0][nx[i][c]][nx[j][c]][nx[k][c]]+=f[i][j][k]);
					}
				}else
					addmod(h[id[a[i]]][i][j][k] += f[i][j][k]);
			}

			for(int l=0;l<tl;l++)
			for(int k=1;k<=n;k++) addmod(h[l][i][j][k]+=h[l][i][j][k-1]);
		}
		for(int l=0;l<tl;l++){
			for(int j=1;j<=n;j++)
				for(int k=0;k<=n;k++)
					addmod(h[l][i][j][k]+=h[l][i][j-1][k]);
			if(i)
			for(int j=0;j<=n;j++)
				for(int k=0;k<=n;k++)
					addmod(h[l][i][j][k]+=h[l][i-1][j][k]);
		}
	}
	cout<<"cnt="<<cnt<<endl;
	printf("%d\n",ans);
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