// created time: 2026-06-19 08:03:26
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

int a,b,m,n;
struct Node{
	int x,f,h,t;
}s[6005];
bool operator< (const Node &A,const Node &B){
	return A.x<B.x;
}

int pos[6005],k;
ll dp[6005],val[6005][6005];

vector<tuple<int,int,int,int>>qry[6005];

void procedure(){
	a=read(),b=read(),m=read();
	if(a>100||b>100||m>100){
		return;
	}
	for(int i=1;i<=a;i++){
		int x=read(),f=read(),h=read();
		s[i]=(Node){x,f,h,1};
	}
	for(int i=1;i<=b;i++){
		int x=read(),f=read(),h=read();
		s[a+i]=(Node){x,f,h,-1};
	}
	for(int i=1;i<=m;i++){
		int x=read(),h=read();
		s[a+b+i]=(Node){x,0,h,0};
	}
	s[0]=(Node){(int)-1e6,0,0,0};
	s[a+b+m+1]=(Node){(int)2e6,0,0,0};
	n=a+b+m+1;
	sort(s,s+n+1);

	for(int i=0;i<=n;i++)
		if(!s[i].t) pos[++k]=i;

	memset(dp,0xc0,sizeof(dp));
	dp[1]=0;
	for(int i=2;i<=k;i++){
		for(int j=1;j<i;j++){
			int L=pos[j]+1,R=pos[i]-1,pt=pos[j];
			while(L<=R){
				int w=(L+R)>>1;
				if(-s[w].x+s[pos[j]].x+s[pos[j]].h>=-s[pos[i]].x+s[w].x+s[pos[i]].h){
					pt=w;
					L=w+1;
				}else R=w-1;
			}
			int sb1 = upper_bound(s+1,s+n+1,(Node){s[pos[j]].x+s[pos[j]].h,0,0,0})-s;
			int lpt = min(pt, sb1-1);
			for(int w=pos[j]+1;w<=lpt;w++){
				int ht = -s[w].x+s[pos[j]].x+s[pos[j]].h;
				val[j][i]+=(ll)s[w].t*s[w].f*min(ht,s[w].h);
			}
			if(pos[j]+1<=lpt){
				qry[pos[j]].pb(s[pos[j]].x+s[pos[j]].h,-1,j,i);
				qry[lpt].pb(s[pos[j]].x+s[pos[j]].h,1,j,i);
			}

			int sb2 = upper_bound(s+1,s+n+1,(Node){s[pos[i]].x-s[pos[i]].h,0,0,0})-s;
			int rpt = max(pt+1, sb2);

			if(rpt<pos[i]){
				qry[rpt-1].pb(s[pos[j]].x+s[pos[j]].h,-1,j,i);
				qry[pos[i]-1].pb(s[pos[j]].x+s[pos[j]].h,1,j,i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(auto [val,cf,p,q]: qry[i]){

			for(int j=1;j<=i;j++)
				val[p][q]+=cf*
		}
	}
	for(int i=2;i<=k;i++){
		for(int j=1;j<i;j++){
			auto ABS = [&](int x){ return max(x,-x); };
			if(s[pos[i]].x-s[pos[j]].x<ABS(s[pos[j]].h-s[pos[i]].h))continue;
			chkmax(dp[i], dp[j]+val[j][i]);
		}
	}
	printf("%lld\n",dp[k]);
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