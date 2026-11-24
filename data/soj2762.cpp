#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-')f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
template<typename T>void chkmin(T &a,const T &b){ a=min(a,b); }
template<typename T>void chkmax(T &a,const T &b){ a=max(a,b); }

int n,m,e[20],u[400],v[400];

int dp[1<<20];

bool g[1<<20][20],cir[1<<20];

int sum[1<<20];
int st[100005],tp;

vector<int>low[1<<20];

void procedure(){
	n=read(),m=read();
	for(int i=0;i<n;i++)e[i]=0;
	memset(g,0,sizeof(g));
	memset(cir,0,sizeof(cir));
	memset(sum,0,sizeof(sum));

	tp=0;
	for(int i=0;i<m;i++){
		u[i]=read()-1,v[i]=read()-1;
		e[u[i]]|=(1<<v[i]),e[v[i]]|=(1<<u[i]);
	}
	for(int i=0;i<n;i++)g[1<<i][i]=1;
	for(int i=1;i<(1<<n);i++){
		int p=__builtin_ctz(i);
		for(int j=0;j<n;j++)if(g[i][j]){
			int now=e[j]&(~i)&((1<<n)-(1<<p));
			if((e[j]>>p)&1){
				cir[i]=1;
				if(__builtin_popcount(i)>=3)sum[i]=1;
			}
			while(now){
				int k=__builtin_ctz(now);now^=(1<<k);
				g[i^(1<<k)][k]=1;
			}
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)if((j>>i)&1)
			sum[j]+=sum[j^(1<<i)];

	for(int i=0;i<(1<<n);i++){
		if(cir[i]&&sum[i]<=1){
			st[++tp]=i;
		}else cir[i]=0;
	}
	memset(dp,0xc0,sizeof(dp));

	int s=0;
	for(int i=1;i<(1<<n);i++){
		int cnt=__builtin_popcount(i);
		if(cnt==1) continue;
		int lim=cnt-1+(cnt-1)/2;
		
		if(cir[i]){
			dp[i]=cnt;
			if(cnt==2)dp[i]--;
		}
		for(int x=1;x<=tp&&dp[i]<lim;x++)if((st[x]&i)==st[x]){
			int now=st[x];
			while(now){
				int w=(now&-now);
				chkmax(dp[i],dp[st[x]]+dp[i^st[x]^w]);
				now^=w;
			}
		}
	}
	if(dp[(1<<n)-1]<0)puts("-1");
	else printf("%d\n",m-dp[(1<<n)-1]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll c=read(),T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}