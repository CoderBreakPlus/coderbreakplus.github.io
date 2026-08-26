// created time: 2026-08-26 14:17:12
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

int n,m,g,b,w[40][40][3],a[40][40],ans[40][40];

int x[40],y[40];
void procedure(){
	n=read(),m=read(),g=read(),b=read();
	for(int i=1;i<=m;i++){
		int a=read()-1,b=read()-1,c=read()-1;
		if(a>b)swap(a,b);
		w[a][b][c]++;
	}

	for(int p=0;p<n;p++)
		for(int q=0;q<n;q++){
			// cout<<"p="<<p<<" q="<<q<<endl;
			memset(a,0,sizeof(a));
			auto addedge = [&](int x,int y,int c){
				// cout<<"add "<<x<<","<<y<<" "<<c<<endl;
				addmod(a[x][y]+=mod-c),addmod(a[y][x]+=mod-c);
				addmod(a[x][x]+=c),addmod(a[y][y]+=c);
			};
			for(int i=0;i<n;i++)
				for(int j=i+1;j<n;j++)
					addedge(i,j,(w[i][j][0]+(ull)p*w[i][j][1]+(ull)q*w[i][j][2])%mod);

			// for(int i=0;i<n;i++){
			// 	for(int j=0;j<n;j++)
			// 		cout<<a[i][j]<<" ";
			// 	cout<<endl;
			// }
			int ret=1;
			for(int i=1;i<n;i++){
				if(!a[i][i]){
					for(int j=i+1;j<n;j++)
						if(a[j][i]){
							swap(a[i],a[j]),ret=mod-ret;
							break;
						}
					if(!a[i][i]){ ret=0; break; }
				}
				ret=(ull)ret*a[i][i]%mod;
				int iv=INV(a[i][i]);
				for(int j=i+1;j<n;j++){
					int cf=(ull)(mod-a[j][i])*iv%mod;
					for(int k=i;k<n;k++)
						a[j][k]=(a[j][k]+(ull)a[i][k]*cf)%mod;
				}
			}

			// cout<<"ret="<<ret<<endl;
			memset(x,0,sizeof(x));
			memset(y,0,sizeof(y));

			x[0]=1;
			for(int i=0;i<n;i++)if(i^p){
				ret=(ull)ret*INV(p+mod-i)%mod;
				for(int j=n-1;j>=0;j--)
					x[j]=((j?x[j-1]:0)+(ull)x[j]*(mod-i))%mod;
			}
			y[0]=1;
			for(int i=0;i<n;i++)if(i^q){
				ret=(ull)ret*INV(q+mod-i)%mod;
				for(int j=n-1;j>=0;j--)
					y[j]=((j?y[j-1]:0)+(ull)y[j]*(mod-i))%mod;
			}

			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					ans[i][j]=(ans[i][j]+(ull)ret*x[i]%mod*y[j])%mod;
		}
	int ret=0;
	for(int i=0;i<=g;i++)
		for(int j=0;j<=b;j++){
			// cout<<i<<","<<j<<" ans="<<ans[i][j]<<endl;
			addmod(ret+=ans[i][j]);
		}
	printf("%d\n",ret);
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