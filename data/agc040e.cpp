// created time: 2026-11-06 15:23:45
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

int n,a[200005],hz[200005];
int pre[200005],suf[200005];

map<int,int>mp[200005];
void procedure(){
	n=read();
	int cnt=0,c0=0,c1=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i>1){
			c0+=(a[i]>a[i-1]);
			c1+=(a[i]<a[i-1]);
		}
	}
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+(a[i-1]>a[i]);
	}
	for(int i=n;i>=1;i--){
		suf[i]=suf[i+1]+(a[i]<a[i+1]);
	}

	int ans=min(c0+(a[1]>0),c1+(a[n]>0));
	for(int i=1;i<=n;i++){
		chkmin(ans,pre[i-1]+suf[i]+2);
		if(a[i]==0){
			int j=i;
			while(j<n&&a[j+1]==0)j++;
			chkmin(ans,pre[i-1]+suf[j+1]+2);
			i=j;
		}
	}
	for(int i=n;i>=1;i--)hz[i]=hz[i+1]+(a[i]<a[i+1]);

	for(int i=1;i<=n;i++){
		chkmax(mp[i][cnt+2],a[i]);
		if(a[i]>=a[i-1])chkmax(mp[i][cnt+1],a[i]-a[i-1]);
		if(i>1)
		for(auto [x,B]:mp[i-1]){
			int A=a[i-1]-B;
			// cout<<"at "<<i-1<<" sta: "<<x<<","<<B<<endl;
			// restriction 1: v<=B
			// restriction 2: a[i]-v>=A => v<=a[i]-A
			// cout<<"here "<<B<<" and "<<a[i]-A<<endl;
			if(min(B,a[i]-A)>=0)chkmax(mp[i][x],min(B,a[i]-A));
			if(max(B,a[i]-A)<=a[i]){
				chkmax(mp[i][x+1],max(B,a[i]-A));
				chkmax(mp[i][x+2],a[i]);
			}else
				chkmax(mp[i][x+1],a[i]);

			// for(int v=0;v<=a[i];v++)
			// 	chkmax(mp[i][x+(v>B)+(v>a[i]-A)],v);
			// cout<<"to ans: "<<x<<"+"<<(B<a[i])<<"+"<<hz[i]<<"+"<<1<<endl;
			chkmin(ans,x+(B<a[i])+hz[i]+1); 
		}
		while(mp[i].size()>=5)mp[i].erase(mp[i].rbegin()->fi);
		cnt+=(a[i]<a[i-1]);
	}
	for(auto [x,y]:mp[n])chkmin(ans,x+1);
	printf("%d\n",ans);
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