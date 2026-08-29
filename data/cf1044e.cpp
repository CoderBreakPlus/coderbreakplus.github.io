// created time: 2026-08-29 07:54:45
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

int n,m,a[25][25],id;
vector<int>sb;
// 0 1 2
// 3 4 5
// 6 7 8
const int B = 13;
vector<int>f[2*B]={
	{3,0,2
	,4,1,5
	,6,7,8},

	{0,4,1
	,3,5,2
	,6,7,8},
	
	{0,1,2
	,6,3,5
	,7,4,8},
	
	{0,1,2
	,3,7,4
	,6,8,5}, // 2*2 spin
	
	{3,0,2
	,6,1,5
	,7,4,8},
	
	{0,4,1
	,3,7,2
	,6,8,5},
	
	{3,0,1
	,4,5,2
	,6,7,8},
	
	{0,1,2
	,6,3,4
	,7,8,5}, // 2*3 psin
	
	{3,0,1
	,6,5,2
	,7,4,8},

	{3,0,1
	,4,7,2
	,6,8,5},

	{3,0,2
	,6,1,4
	,7,8,5},

	{0,4,1
	,6,3,2
	,7,8,5}, // 3*3-1 spin

	{3,0,1
	,6,4,2
	,7,8,5} // 3*3 spin
};
vector<int>siz = {4,4,4,4,6,6,6,6,8,8,8,8,9};


int fa[362880],w[362880],dis[362880],fac[10],vis[362880];
int perm[362880][9];

int decode(int perm[8]){
	int ret=0, mask=0;
	for(int i=0;i<8;i++){
		int c = perm[i] - __builtin_popcount(mask & ((1 << perm[i]) - 1));
		ret += c * fac[8-i];
		mask |= 1 << perm[i];
	}
	return ret;
}
pair<int,int> pos[405];
int code(int x,int y){ return x*3+y; }

vector<vector<int>>lovef;

void solve(int i0,int j0,int i1,int j1,int i2,int j2){
	int cur[9]={0,1,2,3,4,5,6,7,8};
	swap(cur[code(i1-i0,j1-j0)], cur[code(i2-i0,j2-j0)]);

	vector<int>op;
	int x=decode(cur);
	while(x){
		op.pb(w[x]),x=fa[x];
	}
	reverse(op.begin(),op.end());

	vector<int>tab={
		a[i0][j0],a[i0][j0+1],a[i0][j0+2],
		a[i0+1][j0],a[i0+1][j0+1],a[i0+1][j0+2],
		a[i0+2][j0],a[i0+2][j0+1],a[i0+2][j0+2]
	};
	for(int x:op){
		for(int i=0;i<9;i++)
			if(f[x][i]!=i){
				int now=i;
				vector<int>out;
				do{
					out.pb(tab[now]);
					now=f[x][now];
				}while(now!=i);
				reverse(out.begin(),out.end());
				lovef.pb(out);
				break;
			}
		vector<int>tab2(9);
		for(int i=0;i<9;i++)tab2[i]=tab[f[x][i]];
		swap(tab,tab2);
	}
	int ww=0;
	for(int p=0;p<3;p++)
		for(int q=0;q<3;q++)
			pos[a[i0+p][j0+q]=tab[ww++]]={i0+p,j0+q};
}
void procedure(){
	fac[0]=1;
	for(int i=1;i<=9;i++)fac[i]=fac[i-1]*i;

	for(int i=0;i<B;i++){
		f[i+B].resize(9);
		for(int j=0;j<9;j++)
			f[i+B][f[i][j]]=j;
	}
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			pos[a[i][j]]={i,j};
		}

	for(int i=0;i<9;i++)sb.pb(i);
	do{
		for(int i=0;i<9;i++)
			perm[id][i]=sb[i];
		id++;
	}while(next_permutation(sb.begin(),sb.end()));

	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
	q.push({0,0});
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;

	int now[9];
	while(!q.empty()){
		int x=q.top().se;q.pop();
		if(vis[x])continue;vis[x]=1;

		for(int i=0;i<2*B;i++){
			for(int j=0;j<9;j++)now[j]=perm[x][f[i][j]];

			int y=decode(now);
		
			if(dis[y]>dis[x]+siz[i%B]){
				dis[y]=dis[x]+siz[i%B];
				fa[y]=x, w[y]=i;
				q.push({dis[y],y});
			}
		}
	}

	int ww=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		auto [x,y]=pos[++ww];
		while(x!=i||y!=j){
			int xx,yy;
			if(i<x) xx=max(x-2,i);
			else xx=min(x+2,i);

			if(j<y) yy=max(y-2,j);
			else yy=min(y+2,j);

			if(xx==i&&yy<j)xx++;

			solve(min(n-2,min(xx,x)),min(m-2,min(yy,y)),xx,yy,x,y);
			x=xx,y=yy;
		}
	}
	printf("%d\n", (int)lovef.size());
	for(auto out:lovef){
		printf("%d ",(int)out.size());
		for(int x:out) printf("%d ",x);
		puts("");
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