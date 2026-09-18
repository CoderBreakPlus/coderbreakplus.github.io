// created time: 2026-09-18 16:15:22
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

int n,kk,x,m,l[2005],r[2005];
int pos[4005],t;
ll cc[4005][4005];

int calc(int i,int j){
	if(!j) return 0;
	return max(0,min(r[i],pos[j]+m)-max(l[i],pos[j]));
}

pair<ll,ll> dp[4005];

pair<ll,ll> solve(ll v){
	for(int i=1;i<=t;i++) dp[i]={-1e18,0};
	pair<ll,ll> ans={0,0};
	for(int i=1;i<=t;i++){
		for(int j=0;j<i;j++) {
			pair<ll,ll> tmp={dp[j].fi+cc[j][i]-v,dp[j].se+1};
			chkmax(dp[i], tmp);
		}
		chkmax(ans,dp[i]);
	}
	return ans;
}
void procedure(){
	n=read(),kk=read(),x=read(),m=read();
	ll ans=(ll)n*(x-m);
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		pos[++t]=min(x-m,l[i]);
		pos[++t]=max(0,r[i]-m);
		ans-=r[i]-l[i];
	}	
	sort(pos+1,pos+t+1);t=unique(pos+1,pos+t+1)-(pos+1);

	// for(int i=0;i<t;i++)
	// 	for(int j=i+1;j<=t;j++)
	// 		for(int x=1;x<=n;x++) cc[i][j]+=max(0,calc(x,j)-calc(x,i));

	for(int x=1;x<=n;x++){
		int L=0,R=t+1;
		while(L<t&&pos[L+1]+m<r[x]&&pos[L+1]<l[x])L++;
		while(R>1&&pos[R-1]>l[x]&&pos[R-1]+m>r[x])R--;

		for(int j=1;j<=t;j++){
			int val=calc(x,j);
			{
				int lft=0,rht=L,pt=-1;
				while(lft<=rht){
					int mid=(lft+rht)>>1;
					if(calc(x,mid)<val)pt=mid,lft=mid+1;
					else rht=mid-1;
				}
				for(int i=0;i<=pt;i++){
					if(!i)
						cc[i][j]+=val-calc(x,i);
					else
						cc[i][j]+=val-max(0,(pos[i]+m)-l[x]);
				}
			}
			{
				int lft=R,rht=t,pt=n+1;
				while(lft<=rht){
					int mid=(lft+rht)>>1;
					if(calc(x,mid)<val)pt=mid,rht=mid-1;
					else lft=mid+1;
				}

				for(int i=pt;i<=t;i++){
					// cc[i][j]+=val-calc(x,i);
					cc[i][j]+=val-max(0,r[x]-pos[i]);
				}
			}
		}
	}

	ll l=0,r=1e12;
	while(l+1<r){
		ll mid=(l+r)>>1;
		if(solve(mid).se>kk) l=mid; 
		else r=mid;
	}
	auto [a,b]=solve(l);
	auto [c,d]=solve(r);
	
	ll mx=min(a+l*kk,c+r*kk);
	printf("%lld\n",ans+mx);
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