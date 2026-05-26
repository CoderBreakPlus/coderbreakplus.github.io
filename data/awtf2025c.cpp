// created time: 2026-05-26 20:04:25
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

#define LL __int128

int n;
LL a[300005],c[300005],s[300005];
LL L[300005],R[300005],b[300005],sL[300005],sR[300005];
bool check(LL M){
	for(int i=1;i<=n;i++)
		c[i]=i*M-s[i],L[i]=c[i],R[i]=c[i]+a[i];//cout<<(ll)L[i]<<" "<<(ll)R[i]<<endl;
	for(int i=2;i<=n;i++)chkmax(L[i],L[i-1]);
	for(int i=n-1;i>=1;i--)chkmin(R[i],R[i+1]);
	LL sumL=0,sumR=0;
	for(int i=1;i<=n;i++){
		if(L[i]>R[i])return 0;
		sumL+=L[i],sumR+=R[i];
	}

	LL nd=s[n]/2;
	for(int i=1;i<=n;i++)nd+=c[i];
	if(sumL>nd||nd>sumR) return 0;

	LL l=L[1],r=R[n],ans=l;
	for(int i=1;i<=n;i++)sL[i]=sL[i-1]+L[i],sR[i]=sR[i-1]+R[i];

	// cout<<(ll)M<<" sumL="<<(ll)sumL<<" sumR="<<(ll)sumR<<endl;
	while(l<=r){
		LL mid=(l+r)>>1; LL cur=0;
		int pL=upper_bound(R+1,R+n+1,mid)-R;
		int pR=lower_bound(L+1,L+n+1,mid)-L-1;
		if(pL==n+1) cur=sR[n];
		else if(pR==0) cur=sL[n];
		else cur=mid*(pR-pL+1)+sR[pL-1]+sL[n]-sL[pR];
		if(cur<=nd) ans=mid,l=mid+1;
		else r=mid-1;
	}
	LL res=0;
	for(int i=1;i<=n;i++){
		b[i]=max(L[i],min(R[i],ans));
		res+=b[i];
	}
	res=nd-res;
	for(int i=n;i>=1;i--){
		if(!res)break;
		if(b[i]<R[i]&&b[i]==ans)res--,b[i]++;
	}
	LL qz=0;
	for(int i=1;i<=n;i++){
		b[i]-=c[i];
		qz+=b[i];
		if(2*qz-b[i]<s[i]) return 0;
	}
	return 1;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]=read());
	LL l=0,r=2e9,ans=2e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	printf("%lld\n",(ll)ans);
}
signed main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}