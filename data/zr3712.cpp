#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define pb emplace_back
const int mod=1e9+7,N=1e6;

int fac[1000005],inv[1000005];
inline int qpow(int a,int b){
	int ans=1,base=a;
	while(b){
		if(b&1)ans=(ull)ans*base%mod;
		base=(ull)base*base%mod;
		b>>=1;
	}
	return ans;
}
void icantwait(){
	fac[0]=1;
	for(int i=1;i<=N;i++)fac[i]=(ull)fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=0;i--)inv[i]=(ull)inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return (ull)fac[x]*inv[x-y]%mod*inv[y]%mod;
}
inline ll read(){
	ll x;scanf("%lld",&x);return x;
}
template<typename T>void chkmax(T &A,const T &B){ A=max(A,B); }
template<typename T>void addmod(T &A){ if(A>=mod)A-=mod; }

int n,vis[500005],son[500005],sz[500005];
int cs[500005][3],ct[500005][3];
int ds[500005][3],dt[500005][3];

int ts[3],tt[3];

vector<int> E[500005];
char s[500005],t[500005];

void dfs(int x,int fa){
	sz[x]=1;
	for(int y:E[x])if(y!=fa){
		vis[y]=vis[x]^1;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
int tot;
int v1,v2,iv2;
int orig_H(int c1,int c2){
	int ans=0;
	for(int i=0;i<=c1;i++)
		ans=(ans+(ull)binom(c2,i)*binom(v2-c2,v1-i))%mod;
	return ans;
}
struct Node{
	int c1,c2,ans;
	void init(){
		c1=c2=0;
		ans=orig_H(c1,c2);
	}
	void add_c1(){
		c1++;
		ans=(ans+(ull)binom(c2,c1)*binom(v2-c2,v1-c1))%mod;
	}
	void del_c1(){
		ans=(ans+(ull)(mod-binom(c2,c1))*binom(v2-c2,v1-c1))%mod;
		c1--;
	}
	void add_c2(){
		ans=(ans+(ull)(mod-binom(c2,c1))*binom(v2-c2-1,v1-c1-1))%mod;
		c2++;
	}
	void del_c2(){
		c2--;
		ans=(ans+(ull)binom(c2,c1)*binom(v2-c2-1,v1-c1-1))%mod;
	}
	int qry(int x,int y){
		while(c1<x)add_c1();
		while(c1>x)del_c1();
		while(c2<y)add_c2();
		while(c2>y)del_c2();
		return ans;
	}
}DS;
void solve(int x,int fa){
	cs[x][s[x]-'0']++;
	ct[x][t[x]-'0']++;
	for(int y:E[x])if(y!=fa&&y!=son[x]){
		solve(y,x);
		for(int o:{0,1,2})
			cs[x][o]+=cs[y][o],ct[x][o]+=ct[y][o];
	}
	if(son[x]){
		int y=son[x];
		solve(y,x);
		for(int o:{0,1,2})
			cs[x][o]+=cs[y][o],ct[x][o]+=ct[y][o];
	}
	for(int o:{0,1,2})
		ds[x][o]=ts[o]-cs[x][o],
		dt[x][o]=tt[o]-ct[x][o];
	if(fa){
		int c2=cs[x][2]+ct[x][2],c1=ct[x][2]-cs[x][1]+ct[x][1];
		int cf1=((ull)v1*c2+(ull)(mod-v2)*(c1+mod))%mod*(binom(v2,v1)+2ull*(mod-DS.qry(c1,c2)))%mod;
		int cf2=2ull*(c2+mod-c1)*(v1+mod-c1)%mod*binom(c2,c1)%mod*binom(v2-c2,v1-c1)%mod;
		tot=(tot+(ull)(cf1+cf2)*iv2)%mod;
	}
}
void solve2(int x,int fa){
	cs[x][s[x]-'0']++;
	ct[x][t[x]-'0']++;
	for(int y:E[x])if(y!=fa){
		solve2(y,x);
		for(int o:{0,1,2})
			cs[x][o]+=cs[y][o],ct[x][o]+=ct[y][o];
	}
	int d=cs[x][0]-ct[x][0];
	addmod(tot+=max(d,-d));
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	scanf("%s",s+1);
	scanf("%s",t+1);
	dfs(1,0);
	for(int i=1;i<=n;i++){
		if(s[i]!='?')s[i]^=vis[i];else s[i]='2';
		if(t[i]!='?')t[i]^=vis[i];else t[i]='2';
		ts[s[i]-'0']++;
		tt[t[i]-'0']++;
	}
	v2=ts[2]+tt[2];
	iv2=qpow(v2,mod-2);
	v1=tt[2]-ts[1]+tt[1];
	DS.init();
	if(v2){
		solve(1,0);
	}else{
		if(ts[0]!=tt[0]||ts[1]!=tt[1]){
			puts("0");
			return;
		}
		solve2(1,0);
	}
	printf("%d\n",tot);
}
int main(){
	assert(freopen("putao.in","r",stdin));
	assert(freopen("putao.out","w",stdout));
	icantwait(); // I can't wait!!!!
	procedure();
}