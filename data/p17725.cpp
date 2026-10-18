// created time: 2026-10-18 14:35:52
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
inline int gc(){
	static char buf[1<<20],*p=buf,*q=buf;
	if(p==q){
		q=(p=buf)+fread(buf,1,sizeof(buf),stdin);
		if(p==q) return EOF;
	}
	return *p++;
}
inline ll read(){
	ll x=0;int ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc();
	return x;
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
const int INF=(1<<30),N=30000005;
int idx;
int n,a[1000005],f[1000005],bit[1000005],dp[1000005];

int son[N][2],vis[N],tag[N],fa[N],need;
vector<int>buc[30][2];
int dq[30][2];

void clear(){
	for(int i=1;i<=idx;i++) son[i][0]=son[i][1]=fa[i]=vis[i]=tag[i]=0;
	for(int i=0;i<30;i++)for(int o:{0,1}) dq[i][o]=0,buc[i][o].clear();
	idx=1; vis[0]=tag[0]=vis[1]=tag[1]=-1;
}

void color(int p,int v){ tag[p]=vis[p]=v; }
int create(int d,int v,int o){
	if(!son[v][o]){
		son[v][o]=++idx, fa[idx]=v;
		tag[idx]=vis[idx]=-1;
		buc[d][o].pb(idx);
	}
	int ret=son[v][o];
	return ret;
}
void pushup(int p){
	vis[p]=max({tag[p],vis[son[p][0]],vis[son[p][1]]});
}
void ins(int i){
	if(!dp[i]){ color(1,i); return; }
	if(dp[i]>=INF) return;
	// dp[i]-1<(a[i+1] xor x)
	int v=1;
	for(int d=29;d>=0;d--){
		int o=(a[i+1]>>d)&1,lim=((dp[i]-1)>>d)&1;
		if(!lim){
			color(create(d,v,o^1),i);
			v=create(d,v,o); 
		}else
			v=create(d,v,o^1);
	}
	for(v=fa[v];v;v=fa[v]) pushup(v);
}

void erase(int p){
	while(p){
		int old=vis[p];
		pushup(p);
		if(vis[p]==old) return;
		p=fa[p];
	}
}
int query(int w){
	int v=1,ans=0;
	if(vis[v]<=need) return INF;

	int lst=-1,DQ=need;
	for(int i=29;i>=0;i--){
		int o=((w>>i)&1);
		if(~tag[v]) chkmax(lst,tag[v]);
		if(max(lst,vis[son[v][o]])>max(dq[i][o],DQ)){
			v=son[v][o];
			chkmax(DQ,dq[i][o]);
		}else{
			ans^=(1<<i),v=son[v][o^1];
			chkmax(DQ,dq[i][o^1]);
		}
	}
	return ans;
}

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),bit[i]=(a[i]==a[i-1]?-1:lg2(a[i]^a[i-1]));

	f[1]=1;
	int v0=0,v1=0;
	for(int i=2;i<=n;i++){
		f[i]=f[i-1];
		if(~bit[i]){
			if((~v0>>bit[i])&1) v0|=(1<<bit[i]), v1|=(a[i-1]&(1<<bit[i]));
			else if(((v1^a[i-1])>>bit[i])&1){
				f[i]++;
				v0=v1=0;
			}
		}
	}
	for(int m=1,r;m<=n;m=r+1){
		r=m; while(r<n&&f[r+1]==f[r]) ++r;
		int l=m-1; while(l>0&&f[l-1]==f[l]) --l;

		clear();
		memset(dq,-1,sizeof(dq));

		need=-1;
		for(int i=l+1;i<=r;i++){
			if(~bit[i]){
				int d=bit[i],v=(~a[i-1]>>d)&1;
				chkmax(dq[d][v],i-2);
				chkmax(need,dq[d][v^1]);
				for(int p: buc[d][v])
					son[fa[p]][v]=0;
				for(int p: buc[d][v])
					erase(fa[p]);
				vector<int>().swap(buc[d][v]);
			}
			if(i<=m){
				ins(i-1);
			}
			if(i>=m){
				dp[i]=query(a[i]);
			}
		}
	}
	for(int i=n-1;i>=0;i--){
		if(f[i]==f[n]-1 && dp[i]<=a[i+1]){
			printf("%d\n",f[n]-1);
			return;
		}
		if(a[i]>a[i+1])break;
	}
	printf("%d\n",f[n]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll c=read(),T=read();
	// math_init();
	while(T--) procedure(),clear();
	return 0;
}