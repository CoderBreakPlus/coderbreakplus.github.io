// created time: 2026-09-22 07:45:39
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

char s[8005],t[8005];
int n,m,x,y,f[8005][8005],sum[8005],st[8005][8005];
vector<int>vec[8005],val[8005];

int que[8005],now[8005],qz[8005],tl;

void procedure(){
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	if((n^m)&1){puts("-1");return;}

	s[n+1]=t[m+1]='C';
	x=read(),y=read();
	if(x>y){
		for(int i=1;i<=n;i++)s[i]=(s[i]=='A'?'B':'A');
		for(int i=1;i<=m;i++)t[i]=(t[i]=='A'?'B':'A');
		swap(x,y);
	}

	int mn=0,mx=0;
	for(int i=1;i<=m;i++){
		sum[i]=sum[i-1]+(t[i]=='A'?-1:1);
		chkmin(mn,sum[i]),chkmax(mx,sum[i]);
	}
	mx-=mn;
	for(int i=0;i<=m;i++){
		sum[i]-=mn;
		st[i][i]=sum[i];
		vec[sum[i]].pb(i);
	}
	for(int l=0;l<m;l++)
		for(int r=l+1;r<=m;r++)st[l][r]=max(st[l][r-1],st[r][r]);
	for(int x=0;x<=mx;x++){
		for(int i=0;i+1<vec[x].size();i++)
			val[x].pb(st[vec[x][i]][vec[x][i+1]]);
	}

	qz[0]=1e9;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<=n;i++){
		for(int x=0;x<=mx;x++){
			tl=0;
			for(int j=1;j<vec[x].size();j++){
				int sb=vec[x][j-1];
				now[j-1]=f[i][sb]-sum[sb];

				while(tl && val[x][que[tl]]<val[x][j-1])
					chkmin(now[j-1],now[que[tl--]]);
				
				que[++tl]=j-1, qz[tl]=min(qz[tl-1],now[j-1]+val[x][j-1]);
				if(s[i+1]==t[vec[x][j]+1]) chkmin(f[i+1][vec[x][j]+1],qz[tl]);
			}
		}
		for(int j=0;j<=m;j++)
			if(s[i+1]==t[j+1])chkmin(f[i+1][j+1],f[i][j]);
	}
	if(f[n+1][m+1]>m)puts("-1");
	else
	printf("%lld\n",(ll)(y-x)*f[n+1][m+1]+(ll)x*((m-n)/2));
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