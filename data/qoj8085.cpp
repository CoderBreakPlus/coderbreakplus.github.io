// created time: 2026-09-09 13:51:58
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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int n,k,w[40005][9][9],b[40005],pre[40005];
char s[11];

int f[40005][9][9];
void upd(int &A, ull B){ A=(A+B)%mod; }

int check_cnt=0;

int c[9][9],cw;
inline int getrank(int a[][9],int sta=(1<<k)-1){
	cw=0;
	for(int i=0;i<k;i++)if((sta>>i)&1)
		memcpy(c[cw++],a[i],sizeof(c[0]));
	int now=0;
	for(int i=0;i<k&&now<cw;i++){
		for(int j=now;j<cw;j++)if(c[j][i]){swap(c[now],c[j]); break;}
		if(!c[now][i])continue;
		for(int j=now+1;j<cw;j++){
			for(int x=i+1;x<k;x++)
				c[j][x]=((ull)c[j][x]*c[now][i]+(ull)(mod-c[j][i])*c[now][x])%mod;
			c[j][i]=0;
		}
		++now;
	}
	return now;
}
inline bool check_full(int a[][9],int sta){
	++check_cnt;
	return getrank(a,sta)==__builtin_popcount(sta);
}
int mx[40005],sl[1<<9],sr[1<<9];
ll ans;
void solve(int l,int r){
	if(l>=r)return;
	int m=(l+r)>>1;

	memset(f[m],0,sizeof(f[m]));
	for(int i=0;i<k;i++) f[m][i][i]=1;

	for(int i=m+1;i<=r;i++){
		memset(f[i],0,sizeof(f[i]));
		for(int a=0;a<k;a++)for(int b=0;b<k;b++)for(int c=0;c<k;c++)
			upd(f[i][a][c],(ull)f[i-1][a][b]*w[i-1][b][c]);
	}
	for(int i=m-1;i>=l;i--){
		memset(f[i],0,sizeof(f[i]));
		for(int a=0;a<k;a++)for(int b=0;b<k;b++)for(int c=0;c<k;c++)
			upd(f[i][a][c],(ull)f[i+1][a][b]*w[i][c][b]);
	}

	for(int i=l;i<=r;i++) pre[i]=getrank(f[i]);

	for(int t=k;t>=1;t--){
		for(int i=l-1;i<=m;i++) mx[i]=0;
		for(int s=0;s<(1<<k);s++)if(__builtin_popcount(s)==t){
			sl[s]=m,sr[s]=m;

			for(int ss=s|(s+1);ss<(1<<k);ss=(ss+1)|s)
				chkmin(sl[s],sl[ss]),chkmax(sr[s],sr[ss]);

			{
				int L=sr[s]+1,R=r;
				while(L<=R){
					int M=(L+R)>>1;
					if(pre[M]>=t && check_full(f[M],s)) sr[s]=M,L=M+1;
					else R=M-1;
				}
			}
			{
				int L=l,R=sl[s]-1;
				while(L<=R){
					int M=(L+R)>>1;
					if(pre[M]>=t && check_full(f[M],s)) sl[s]=M,R=M-1;
					else L=M+1;
				}
			}
			chkmax(mx[sl[s]],sr[s]);
		}
		ans--;
		for(int i=l;i<=m;i++){
			chkmax(mx[i],mx[i-1]);
			ans+=max(0,mx[i]-m+1);
		}
	}
	solve(l,m-1),solve(m+1,r);
}
void procedure(){
	n=read(),k=read();
	for(int i=1;i<n;i++){
		for(int p=0;p<k;p++){
			scanf("%s",s);
			for(int q=0;q<k;q++){
				w[i][p][q]=(s[q]-'0')*rnd()%mod;
			}
		}
	}
	solve(1,n);
	printf("%lld\n",ans);
	cerr<<check_cnt<<endl;
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