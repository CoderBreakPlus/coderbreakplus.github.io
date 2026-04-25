// created time: 2026-04-25 08:58:12
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
int n,m,d;
char s[1005][1005];
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};

bool in(int x,int y){ return 1<=x&&x<=n&&1<=y&&y<=m; }
bool obstacle(int x,int y){ return in(x,y)&&s[x][y]=='#'; }
bool passby(int x,int y){ return in(x,y)&&s[x][y]=='.'; }

bool check(int x,int y){
	if(x==1||x==n||y==1||y==m)return 0;
	if(!obstacle(x,y))return 0;
	int cnt=0;
	for(int i:{0,1,2,3}){
		int tx=x+dx[i],ty=y+dy[i];
		cnt+=obstacle(tx,ty);
	}
	if(cnt<=1) return 1;
	if(cnt>2) return 0;
	for(int i:{0,1,2,3}){
		int j=(i+1)&3;
		if(obstacle(x+dx[i],y+dy[i]) && obstacle(x+dx[j],y+dy[j])
			&& obstacle(x+dx[i]+dx[j],y+dy[i]+dy[j])) return 1;
	}
	return 0;
}
pair<int,int> seq[1000005];
int sx,sy,ex,ey,sb;

int dis[1005][1005];

void procedure(int fjy){
	sb=0;
	n=read(),m=read(),d=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(s[i][j]=='S')sx=i,sy=j,s[i][j]='.';
		if(s[i][j]=='F')ex=i,ey=j,s[i][j]='.';
	}
	printf("Case #%d: ",fjy);
	queue<pair<int,int>>q;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		if(check(i,j))q.push({i,j}),s[i][j]='.';

	while(!q.empty()){
		auto [x,y]=q.front();q.pop();
		seq[++sb]={x,y};
		for(int i:{0,1,2,3}){
			int tx=x+dx[i],ty=y+dy[i];
			if(check(tx,ty))q.push({tx,ty}),s[tx][ty]='.';
		}
	}

	// for(int i=1;i<=n;i++)cout<<(s[i]+1)<<endl;
	reverse(seq+1,seq+sb+1);
	// for(int i=1;i<=sb;i++)cout<<seq[i].fi<<" "<<seq[i].se<<endl;
	// cout<<"finally!"<<endl;

	int L=0, R=sb, ans=-1;

	int iloveu=0;
	while(L<=R){
		int mid=(L+R)>>1;
		for(int i=1;i<=mid;i++) s[seq[i].fi][seq[i].se]='#';

		// cout<<"mid="<<mid<<endl;
		// for(int i=1;i<=n;i++)cout<<(s[i]+1)<<endl;	
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
			dis[i][j]=-1;
		queue<pair<int,int>>q;q.push({sx,sy});dis[sx][sy]=0;
		while(!q.empty()){
			auto [x,y]=q.front();q.pop();
			for(int i:{0,1,2,3}){
				int tx=x+dx[i],ty=y+dy[i];
				if(passby(tx,ty) && !~dis[tx][ty]){
					dis[tx][ty]=dis[x][y]+1;
					// cout<<"upd "<<tx<<","<<ty<<" dis = "<<dis[tx][ty]<<endl;
					// iloveu++;if(iloveu>=100)exit(0);
					q.push({tx,ty});
				} 
			}
		}
		int cur = dis[ex][ey];
		if(cur == d){
			ans = mid;
			break;
		}else if(cur<d) L=mid+1;
		else R=mid-1;
		for(int i=1;i<=mid;i++) s[seq[i].fi][seq[i].se]='.';
	}
	if(~ans){
		puts("POSSIBLE");
		s[sx][sy]='S';
		s[ex][ey]='F';
		for(int i=1;i<=n;i++)
			printf("%s\n",s[i]+1);
	}else{
		puts("IMPOSSIBLE");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++)procedure(i);
	return 0;
}