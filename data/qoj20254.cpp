// created time: 2026-09-19
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

int k,n,a[200005];
vector<int>val[200005];

uint f[19][1<<18],tmp[1<<18];
uint A[1<<18],B[1<<18],C[1<<18];

void fwt(uint *a,uint *A,int n){
	for(int i=0;i<(1<<n);i++)A[i]=a[i];
	for(int m=1;m<(1<<n);m<<=1)
		for(int j=0;j<(1<<n);j+=(m<<1))for(int i=0;i<m;i++){
			uint v0=A[i+j],v1=A[i+m+j];
			A[i+j]=v0+v1;
			A[i+m+j]=v0-v1;
		}
}
void convolution(uint *a,uint *b,uint *c,int n){
	// for(int i=0;i<(1<<n);i++){
	// 	cout<<a[i]<<" ";
	// }
	// cout<<endl;
	// for(int i=0;i<(1<<n);i++){
	// 	cout<<b[i]<<" ";
	// }
	// cout<<endl;
	
	fwt(a,A,n),fwt(b,B,n);

	// for(int i=0;i<(1<<n);i++){
	// 	cout<<A[i]<<" ";
	// }
	// cout<<endl;
	// for(int i=0;i<(1<<n);i++){
	// 	cout<<B[i]<<" ";
	// }
	// cout<<endl;
	for(int i=0;i<(1<<n);i++) C[i]=A[i]*B[i];
	fwt(C,c,n);
	for(int i=0;i<(1<<n);i++){
		// cout<<c[i]<<" ";
		c[i]=!!c[i];
	}
	// cout<<endl;

}
void procedure(){
	k=read(),n=read();
	int cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i])
			val[lg2(a[i])].pb(a[i]);
		else
			cnt++;
	}
	f[0][0]=1;
	for(int i=1;i<=k;i++){
		if(val[i-1].empty()){
			memcpy(f[i],f[i-1],sizeof(f[i]));
			continue;
		}
		// cout<<"work on "<<i<<endl;
		memset(tmp,0,sizeof(tmp));
		for(int x:val[i-1])tmp[x]=1;

		// for(int x=0;x<(1<<i);x++)cout<<f[i-1][x];
		// cout<<endl;
		// for(int x=0;x<(1<<i);x++)cout<<tmp[x];
		// cout<<endl;
		convolution(f[i-1],tmp,f[i],i); 

		// for(int x=0;x<(1<<i);x++)cout<<f[i][x];
		// cout<<endl;
	}
	int mn=-1;
	for(int i=0;i<(1<<k);i++)
		if(f[k][i]){mn=i;break;}

	assert(~mn);
	vector<int>ans;
	for(int i=k;i>=1;i--){
		if(val[i-1].empty())continue;
		int ban=-1;
		for(int x:val[i-1])
			if(f[i-1][mn^x]){
				ban=x,mn^=x;
				break;
			}
		assert(~ban);
		int fff=ban;
		for(int x:val[i-1]){
			if(x==ban) ban=-1;
			else ans.pb(x);
		}
		ans.pb(fff);
	}
	while(cnt--)ans.pb(0);

	reverse(ans.begin(),ans.end());

	int out=0;
	for(int x:ans){
		if((out^x)>out) out^=x;
		printf("%d ",x);
	}
	// cerr<<"out="<<out<<endl;
	puts("");
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