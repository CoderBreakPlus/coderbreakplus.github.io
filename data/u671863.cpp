// created time: 2026-04-07 08:02:51
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

int n,m,dep[1000005],dfn[1000005],out[1000005]; ll dis[1000005];
int jp[20][1000005],tim;
int *fa=jp[0];
vector<int>E[1000005];

void dfs(int x){
	dfn[x]=++tim;
	for(auto y:E[x])dfs(y);
	out[x]=tim;
}
ll dist(int x,int y,int p){
	assert(p);
	return dis[x]+dis[y]-2*dis[p];
}
struct Node{
	int x,y,z;
	Node(){ x=y=z=0; }
	Node(int a){ x=y=z=a; }
	Node(int a,int b,int c=0){ x=a,y=b,z=c; }
}tr[1000005];
bool operator< (const Node &A, const Node &B){
	return dist(A.x,A.y,A.z)<dist(B.x,B.y,B.z);
}
Node merge (const Node &A, const Node &B,int z){
	return max({A,B,Node(A.x,B.x,z),Node(A.x,B.y,z),Node(A.y,B.x,z),Node(A.y,B.y,z)});
}

ll qz[1000005],hz[1000005];
ll p[1000005],q[1000005];
ll bg[2000005],val[2000005],sum[2000005]; bool op[2000005];

int tt,t;
inline ll tmp_calc(ll r){
	r--;
	if((r&3)==0) return r;
	if((r&3)==1) return 1;
	if((r&3)==2) return r+1;
	return 0;
}
inline ll calc(ll l,ll r){
	return tmp_calc(r)^tmp_calc(l);
}
inline ll solve(int x,ll l,ll r){
	if(l>=r)return 0;
	if(op[x]==0) return val[x]*((r-l)&1);
	else return calc(l-bg[x]+val[x],r-bg[x]+val[x]);
}

void procedure(){
	n=read(),m=read();	
	int pos=1;
	for(int i=2;i<=n;i++){
		int x=read(),w=read();
		E[x].pb(i);
		jp[0][i]=x; dep[i]=dep[x]+1,dis[i]=dis[x]+w;
		if(dis[i]>dis[pos]) pos=i;
	}
	dfs(1);

	ll kl=read(),bl=read(),kr=read(),br=read();
	for(int i=n;i>=1;i--){
		tr[i]=Node(i);
		for(auto j:E[i]) tr[i]=merge(tr[i],tr[j],i);
	}
	for(int i=1;i<=n;i++) qz[dfn[i]]=hz[dfn[i]]=dis[i];
	for(int i=1;i<=n;i++) qz[i]=max(qz[i],qz[i-1]);
	for(int i=n;i>=1;i--) hz[i]=max(hz[i],hz[i+1]);

	int lu=pos,lv=pos,lw=pos,w=pos;
	for(int x=pos,px=0;x>1;px=x,x=fa[x]){
		// cout<<"x="<<x<<endl;
		int u=tr[x].x,v=tr[x].y,lca=tr[x].z;
		if(dis[u]<dis[v])swap(u,v);

		if(u!=lu || v!=lv){
			w=lw;
			if(!(dfn[px]<=dfn[w] && dfn[w]<=out[px]))w=u;
			while(w!=lca && dist(u,fa[w],fa[w])<=dist(fa[w],v,lca))
				w=fa[w];
		}else{
			w=lw;
		}
		lu=u,lv=v,lw=w;

		ll inner=max(dist(u,w,w),dist(w,v,lca));
		if(w!=lca){ w=fa[w], inner=min(inner, max(dist(u,w,w),dist(w,v,lca))); }
		ll outer=max(qz[dfn[x]-1],hz[out[x]+1]);
		p[++tt]=outer,q[tt]=inner;
	}
	reverse(p+1,p+tt+1),reverse(q+1,q+tt+1);

	ll cur=0; p[tt+1]=dis[pos];
	for(int i=1;i<=tt;i++){
		bg[++t]=cur, val[t]=p[i], op[t]=0;
		bg[++t]=p[i]-q[i], val[t]=p[i], op[t]=1;
		cur=p[i+1]-q[i];
	}
	bg[++t]=cur, val[t]=dis[pos], op[t]=0;

	for(int i=1;i<t;i++) {
		sum[i]=solve(i,bg[i],bg[i+1]);
	}

	for(int i=1;i<t;i++)sum[i]^=sum[i-1];

	__int128 ans=0;
	for(int i=1;i<=m;i++){
		ll l=kl*i+bl,r=kr*i+br+1;
		int p1=upper_bound(bg+1,bg+t+1,l)-(bg+1);
		int p2=lower_bound(bg+1,bg+t+1,r)-(bg+1);
		ll now;
		if(p1==p2){
			now=solve(p1,l,r);
		}else
			now=sum[p2-1]^sum[p1]^solve(p1,l,bg[p1+1])^solve(p2,bg[p2],r);
		ans+=now;
	}
	if(!ans){
		puts("0");
		return;
	}
	vector<char>vec;
	while(ans){ vec.pb(ans%10+'0'),ans/=10; }
	reverse(vec.begin(),vec.end());
	for(auto ch:vec) putchar(ch);puts("");
}
void clear(){
	for(int i=0;i<=n+1;i++){
		dep[i]=dis[i]=dfn[i]=out[i]=qz[i]=hz[i]=0;
		tr[i]=Node();
		E[i].clear();
	}
	tim=t=tt=0;
}
int main(){
	#ifdef LOCAL
		assert(freopen("tree8.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure(),clear();
	return 0;
}