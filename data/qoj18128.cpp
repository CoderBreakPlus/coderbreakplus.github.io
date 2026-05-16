// created time: 2026-05-16 10:02:53
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

int Q,c,col[500005];

struct Tree{
	int sz[500005],k[500005],lc[500005],rc[500005];
	void pushup(int p){
		sz[p]=1+sz[lc[p]]+sz[rc[p]];
	}
	int newnode(int x){
		sz[x]=1, k[x]=rnd();
		return x;
	}
	void split(int a,int k,int &x,int &y){
		if(!a) {x=y=0; return;}
		if(1+sz[lc[a]]<=k){
			x=a;
			// cout<<"put x as "<<a<<endl;
			split(rc[x],k-1-sz[lc[a]],rc[x],y);
			pushup(x);
		}else{
			y=a;
			// cout<<"put x as "<<a<<endl;
			split(lc[y],k,x,lc[y]);
			pushup(y);
		}
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(k[x]<k[y]){
			rc[x]=merge(rc[x],y);
			pushup(x);
			return x;
		}else{
			lc[y]=merge(x,lc[y]);
			pushup(y);
			return y;
		}
	}
}tx,ty;
void procedure(){
	Q=read(),c=read();
	int rx = tx.newnode(1), ry = ty.newnode(1);

	// cout<<"rx = "<<rx<<" ry = "<<ry<<endl;
	col[1] = c;

	for(int i=2;i<=Q+1;i++){
		int op=read(),x=read(),y=read();
		if(op==1){
			col[i]=y;
			int p,q;
			tx.split(rx,x,p,q);
			// cout<<"split as "<<p<<" "<<q<<endl;
			rx = tx.merge(tx.merge(p,tx.newnode(i)),q);
			// cout<<"rx = "<<rx<<endl;
		}else if(op==2){
			col[i]=y;
			int p,q;
			ty.split(ry,x,p,q);
			ry = ty.merge(ty.merge(p,ty.newnode(i)),q);
		}else{
			int ax,ay;
			{
				int p,q,r;
				tx.split(rx,x-1,p,q);
				tx.split(q,1,q,r);
				ax=q;
				rx = tx.merge(tx.merge(p,q),r);
			}
			{
				int p,q,r;
				ty.split(ry,y-1,p,q);
				ty.split(q,1,q,r);
				ay=q;
				ry = ty.merge(ty.merge(p,q),r);
			}
			printf("%d\n", col[max(ax,ay)]);
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