// created time: 2026-05-27 16:03:11
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
char s[200005];
int n,m,q,fa[200005];
vector<int>E[200005];
namespace SAM{
	int len[200005],fa[200005],son[200005][26],lst;
	inline void ins(int p,int v){
		len[p]=len[lst]+1;
		while(lst&&!son[lst][v]){
			son[lst][v]=p;
			lst=fa[lst];
		}
		if(!son[lst][v]) son[lst][v]=p;
		else{
			int q=son[lst][v];
			if(len[q]==len[lst]+1) fa[p]=q;
			else{
				int u=++m;
				len[u]=len[lst]+1,fa[u]=fa[q];
				memcpy(son[u],son[q],sizeof(son[u]));
				fa[p]=fa[q]=u;
				while(son[lst][v]==q) son[lst][v]=u,lst=fa[lst];
			}
		}
		lst=p;
	}
}
int lc[10000005],rc[10000005],cnt[10000005],id;
int merge(int x,int y){
	if(!x||!y)return x^y;
	int z=++id;
	lc[z]=merge(lc[x],lc[y]);
	rc[z]=merge(rc[x],rc[y]);
	cnt[z]=cnt[lc[z]]+cnt[rc[z]];
	return z;
}
void upd(int &x,int l,int r,int pos){
	x=++id,cnt[x]=1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid) upd(lc[x],l,mid,pos);
	else upd(rc[x],mid+1,r,pos);
}
int rt[200005];
void dfs(int x){
	for(int y:E[x]){
		dfs(y);
		rt[x]=merge(rt[x],rt[y]);
	}
}
int query(int l,int r,int ql,int qr,int x){
	if(!x||r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr)return cnt[x];
	int mid=(l+r)>>1;
	return query(l,mid,ql,qr,lc[x])+query(mid+1,r,ql,qr,rc[x]);
}
void procedure(){
	scanf("%s",s+1); n=m=strlen(s+1);
	for(int i=1;i<=n;i++)SAM::ins(i,s[i]-'a');
	for(int i=1;i<=m;i++)fa[i]=SAM::fa[i],E[fa[i]].pb(i);//cout<<fa[i]<<"->"<<i<<endl;

	for(int i=1;i<=n;i++)
		upd(rt[i],1,n,i);
	dfs(0);

	// cout<<query(1,n,1,n,rt[1])<<endl;
	q=read();

	while(q--){
		int l=read(),r=read();
		scanf("%s",s);
		int len=strlen(s),cur=0;
		int ok=-1,nw=0;
		for(int i=0;i<len;i++){
			for(int z=25;z>s[i]-'a';z--)
				if(SAM::son[cur][z] && query(1,n,l+i,r,rt[SAM::son[cur][z]])){
					ok=i,nw=z;
				}
			if(SAM::son[cur][s[i]-'a'] && query(1,n,l+i,r,rt[SAM::son[cur][s[i]-'a']])) cur=SAM::son[cur][s[i]-'a'];
			else{
				cur=-1;
				break;
			}
		}
		bool flg=0;
		if(~cur){
			for(int z=0;z<=25;z++)
				if(SAM::son[cur][z] && query(1,n,l+len,r,rt[SAM::son[cur][z]])){
					flg=1;
					printf("%s",s); putchar('a'+z); puts("");
					break;
				}
		}
		if(flg)continue;
		
		if(~ok){
			for(int i=0;i<ok;i++)
				putchar(s[i]);
			putchar('a'+nw);
			puts("");
		}else puts("-1");
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