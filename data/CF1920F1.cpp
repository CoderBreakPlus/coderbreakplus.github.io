// created time: 2026-04-08 15:33:20
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
const int dx[8]={0,0,1,-1,1,1,-1,-1};
const int dy[8]={1,-1,0,0,1,-1,1,-1};

int n,m,Q;
char t[100005];
string s[100005];
vector<int>dp[100005],tmp[100005];

bool check(int mid,int ox,int oy){
	for(int i=0;i<=n+1;i++)fill(tmp[i].begin(),tmp[i].end(),0);
	queue<pair<int,int>>q;
	tmp[ox][oy]=2,q.push({ox,oy});
	while(!q.empty()){
		auto [x,y]=q.front();q.pop();
		for(int d=0;d<4;d++){
			int tx=x+dx[d],ty=y+dy[d];
			if(1<=tx&&tx<=n&&1<=ty&&ty<=m&&!tmp[tx][ty]&&s[tx][ty]!='#'&&dp[tx][ty]>=mid){
				tmp[tx][ty]=2;
				q.push({tx,ty});
			}
		}
	}

	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		if(s[i][j]=='#'){
			tmp[i][j]=1;
			q.push({i,j});
		}

	int px=-1,py=-1;
	while(!q.empty()){
		auto [x,y]=q.front();q.pop();
		for(int d=0;d<8;d++){
			int tx=x+dx[d],ty=y+dy[d];
			if(0<=tx&&tx<=n+1&&0<=ty&&ty<=m+1&&tmp[tx][ty]==0&&s[tx][ty]!='#')
				tmp[tx][ty]=1, q.push({tx,ty});
		}
	}
	return !tmp[0][0];
}
void procedure(){
	n=read(),m=read(),Q=read();
	queue<pair<int,int>>q;
	for(int i=0;i<=n+1;i++){
		s[i].resize(m+2),dp[i].resize(m+2);
		tmp[i]=dp[i];
		if(1<=i&&i<=n){
			scanf("%s",t+1);
			for(int j=1;j<=m;j++){
				s[i][j]=t[j];
				if(s[i][j]=='v') dp[i][j]=1,q.push({i,j});
			}
		}
	}
	while(!q.empty()){
		auto [x,y]=q.front();q.pop();
		for(int d=0;d<4;d++){
			int tx=x+dx[d],ty=y+dy[d];
			if(1<=tx&&tx<=n&&1<=ty&&ty<=m&&!dp[tx][ty]){
				dp[tx][ty]=dp[x][y]+1;
				q.push({tx,ty});
			}
		}
	}
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=m;j++)putchar('0'+dp[i][j]);
	// 	puts("");
	// }
	// cout<<endl;
	while(Q--){
		int x=read(),y=read();
		int L=1,R=dp[x][y],ans=-1;
		// cout<<L<<"->"<<R<<endl;
		while(L<=R){
			int mid=(L+R)>>1;
			if(check(mid,x,y))ans=mid,L=mid+1;
			else R=mid-1;
		}
		assert(~ans);
		printf("%d\n",ans-1);
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