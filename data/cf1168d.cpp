// created time: 2026-08-25 11:26:52
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353, Z = 26;
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

int n,q,D,d;
int fa[150005],mx[150005][Z],val[150005][Z],sig[150005],c[150005],dep[150005],tag;
vector<int>E[150005],G[200005];
int jp[150005],low[150005];

char s[5];

void dfs(int x,int d){
	chkmax(D,dep[x]=d);
	for(int y:E[x]) dfs(y,d+1);
}
void dfs2(int x){
	for(int y:E[x]){
		int now[Z];
		memset(now,0,sizeof(now));
		vector<int>way={y};
		if(c[y]>=0)now[c[y]]++;		
		while(E[y].size()==1){
			y=E[y][0];
			if(c[y]>=0)now[c[y]]++;
			way.pb(y);
		}
		for(int sb:way) low[sb]=y;
		memcpy(val[y],now,sizeof(val[y]));

		dfs2(y),G[x].pb(y),jp[y]=x;
		for(int i=0;i<Z;i++)
			chkmax(mx[x][i],mx[y][i]+val[y][i]);
	}
	sig[x]=0;
	for(int i=0;i<Z;i++)sig[x]+=mx[x][i];

	// cout<<"node "<<x<<" here ";
	// for(int i=0;i<Z;i++) cout<<mx[x][i]<<" ";
	// cout<<endl;

	tag+=(sig[x]>D-dep[x]);
}
void pushup(int x,vector<int> col){
	tag-=(sig[x]>D-dep[x]);
	for(int i:col){
		sig[x]-=mx[x][i];
		mx[x][i]=0;
		for(int y:G[x])
			chkmax(mx[x][i],mx[y][i]+val[y][i]);
		sig[x]+=mx[x][i];
	}
	tag+=(sig[x]>D-dep[x]);
}
void procedure(){
	n=read(),q=read();
	for(int i=2;i<=n;i++){
		fa[i]=read(),E[fa[i]].pb(i);
		scanf("%s",s);
		c[i]=s[0]-'a';
	}
	dfs(1,0);
	bool flg=1;
	for(int i=1;i<=n;i++)
		if(E[i].empty())flg&=(dep[i]==D);
	if(!flg){
		while(q--)puts("Fou");
		return;
	}
	dfs2(1);

	while(q--){
		int i=read(); scanf("%s",s);
		int x=low[i];
		
		vector<int>ch;
		if(c[i]>=0)ch.pb(c[i]),val[x][c[i]]--;
		
		c[i]=s[0]-'a';
		if(c[i]>=0)ch.pb(c[i]),val[x][c[i]]++;

		while(x){
			pushup(jp[x],ch);
			x=jp[x];
		}

		if(tag){
			puts("Fou");
		}else{
			int ans=0;
			for(int i=0;i<Z;i++){
				ans+=(D-sig[1]+mx[1][i])*(i+1);
				// cout<<"Add "<<D-sig[1]+mx[1][i]<<" * "<<i+1<<endl;
			}
			printf("Shi %d\n",ans);
		}
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