// created time: 2026-04-02 07:47:46
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

int n,m,q,a[200005],L[200005],R[200005],x[200005],y[200005];
ll ans[200005],dp1[200005][2],dp2[200005][2];
bool vis[200005];

inline void sbfjy(int l,int r,int s,int t,int c){
	bool fat=(s==0&&t==m-1);
	for(int i=l;i<=r;i++){
		int L=i*m+s,R=i*m+t;
		for(int j=L;j<=R;j++) dp1[j][0]=dp1[j][1]=dp2[j][0]=dp2[j][1]=-1e18;
	}
	dp1[c][0]=dp2[c][1]=0;
	auto [X,Y] = div(c,m);
	for(int i=X;i>=l;i--)for(int j=(i==X?Y-1:t);j>=s;j--){
		int x=i*m+j;assert(x<c);
		if(fat||j<t){
			dp1[x][0]=max(dp1[x+1][1]+a[x+1],dp1[x+1][0]);
			dp1[x][1]=max(dp1[x+1][0]-a[x+1],dp1[x+1][1]);
			dp2[x][0]=max(dp2[x+1][1]+a[x+1],dp2[x+1][0]);
			dp2[x][1]=max(dp2[x+1][0]-a[x+1],dp2[x+1][1]);
		}
		if(i<X&&x+m<=c){
			dp1[x][1]=max(dp1[x][1],dp1[x+m][1]+a[x+m]);
			dp2[x][1]=max(dp2[x][1],dp2[x+m][1]+a[x+m]);
		}
	}
	for(int i=X;i<=r;i++)for(int j=(i==X?Y+1:s);j<=t;j++){
		int x=i*m+j;assert(x>c);
		if(fat||j>s){
			dp1[x][0]=max(dp1[x-1][1]-a[x],dp1[x-1][0]);
			dp1[x][1]=max(dp1[x-1][0]+a[x],dp1[x-1][1]);
			dp2[x][0]=max(dp2[x-1][1]-a[x],dp2[x-1][0]);
			dp2[x][1]=max(dp2[x-1][0]+a[x],dp2[x-1][1]);
		}
		if(i>X&&x-m>=c){
			dp1[x][1]=max(dp1[x][1],dp1[x-m][1]+a[x]);
			dp2[x][1]=max(dp2[x][1],dp2[x-m][1]+a[x]);
		}
	}
}
basic_string<int>qq[520005];
void solve(int l,int r,int s,int t,int p){
	bool fat=(s==0 && t==m-1);
	if(l>r||s>t||qq[p].empty()) return;
	if(r-l<t-s){
		int mid=(s+t)>>1;
		{basic_string<int>ok;
		for(auto o: qq[p]){
			if(y[L[o]]<mid && y[R[o]]<mid) qq[p<<1].push_back(o);//cout<<"goleft"<<endl;
			else if(y[L[o]]>mid && y[R[o]]>mid) qq[p<<1|1].push_back(o);//cout<<"right"<<endl;
			else ok.push_back(o);
		}
		if(!fat)swap(ok,qq[p]);}

		for(int i=l;i<=r;i++){
			int id=i*m+mid;
			sbfjy(l,r,s,t,id);
			for(auto x: qq[p]){
				if(L[x]<=id && R[x]>=id)
				ans[x]=max({ans[x],
				dp1[L[x]][0]+max(dp1[R[x]][0],dp1[R[x]][1]),
				dp2[L[x]][0]+max(dp2[R[x]][0],dp2[R[x]][1])});
			}

			if(fat){
				int id=i*m+t;
				sbfjy(l,r,s,t,id);
				for(auto x: qq[p])
					if(L[x]<=id && R[x]>=id)
					ans[x]=max({ans[x],
					dp1[L[x]][0]+max(dp1[R[x]][0],dp1[R[x]][1]),
					dp2[L[x]][0]+max(dp2[R[x]][0],dp2[R[x]][1])});
			}
		}
		solve(l,r,s,mid-1,p<<1),solve(l,r,mid+1,t,p<<1|1);
	}else{
		int mid=(l+r)>>1;
		{basic_string<int>ok;
		for(auto o: qq[p]){
			if(x[L[o]]<mid && x[R[o]]<mid) qq[p<<1].push_back(o);
			else if(x[L[o]]>mid && x[R[o]]>mid) qq[p<<1|1].push_back(o);
			else ok.push_back(o);
		}
		swap(qq[p],ok);}
		for(int i=s;i<=t;i++){
			int id=mid*m+i;
			sbfjy(l,r,s,t,id);

			for(auto x: qq[p])
				if(L[x]<=id && R[x]>=id)
				ans[x]=max({ans[x],
				dp1[L[x]][0]+max(dp1[R[x]][0],dp1[R[x]][1]),
				dp2[L[x]][0]+max(dp2[R[x]][0],dp2[R[x]][1])});
		}
		solve(l,mid-1,s,t,p<<1),solve(mid+1,r,s,t,p<<1|1);
	}
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();

	for(int o=1;o<=q;o++){
		L[o]=read()-1,R[o]=read();
		qq[1].push_back(o);
	}
	for(int i=0;i<=n;i++) x[i]=i/m,y[i]=i%m;
	solve(0,n/m,0,m-1,1);
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
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