// created time: 2026-04-27 14:28:54
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,d,a[200005],ia[200005],b[200005],ib[200005],p[200005];

int calc(int i){
	if(i>=n) return 0;
	if(p[i]<p[i+1])return p[i+1]-p[i]-1;
	else return p[i+1]+n-p[i]-1;
}
void procedure(){
	n=read(),d=read()-1;
	for(int i=1;i<=n;i++)a[i]=read(),ia[a[i]]=i;
	for(int i=1;i<=n;i++)b[i]=read(),ib[b[i]]=i,p[i]=ia[b[i]];

	// for(int i=1;i<=n;i++) cout<<p[i]<<" ";cout<<endl;

	ll ans=0;
// for(ll i=0;i<n;i++)cout<<calc(i)<<" ";cout<<endl;
	for(int i=0;i<n;i++) ans+=calc(i);
	printf("%lld\n",ans);
	while(d--){
		// cout<<"shabi1"<<endl;
		int c=read(),x=read(),y=read();
		if(c==1){
			int l=a[x],r=a[y];
			int s=ib[l],t=ib[r];
			if(s>t)swap(s,t);
			ans-=calc(s-1)+calc(s)+calc(t);
			if(s+1!=t)ans-=calc(t-1);

			swap(a[x],a[y]);
			swap(ia[l],ia[r]);
			swap(p[s],p[t]);

			ans+=calc(s-1)+calc(s)+calc(t);
			if(s+1!=t)ans+=calc(t-1);
		}else{
			int l=b[x],r=b[y];
			
			if(x>y)swap(x,y);
			ans-=calc(x-1)+calc(x)+calc(y);
			if(x+1!=y)ans-=calc(y-1);

			swap(b[x],b[y]);
			swap(ib[l],ib[r]);
			swap(p[x],p[y]);

			ans+=calc(x-1)+calc(x)+calc(y);
			if(x+1!=y)ans+=calc(y-1);
		}
		// cout<<"shabi2"<<endl;
		// for(ll i=0;i<n;i++)cout<<calc(i)<<" ";cout<<endl;
		printf("%lld\n",ans);
	}	
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