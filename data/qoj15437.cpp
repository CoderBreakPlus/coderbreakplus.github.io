// created time: 2026-09-10 14:16:28
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

int op,n,m,k,u[500005],v[500005],ord[500005],d[500005],id[500005];
vector<int>E[500005];

void procedure(){
	op=read();	
	n=read(),m=read();

	if(op==1){
		for(int i=1;i<=m;i++)
			u[i]=read(),v[i]=read();
		k=read();
		for(int i=1;i<=k;i++) ord[read()]=i;

		int kk=k;
		for(int i=1;i<=n;i++)
			if(!ord[i])ord[i]=++kk;

		for(int i=1;i<=m;i++){
			if(ord[u[i]]<ord[v[i]])swap(u[i],v[i]);
			if(ord[u[i]]==k&&ord[v[i]]==1)swap(u[i],v[i]);
			printf("%d %d\n",u[i],v[i]);
		}
	}else{
		for(int i=1;i<=m;i++){
			u[i]=read(),v[i]=read();
			d[v[i]]++,id[v[i]]^=u[i];E[u[i]].pb(v[i]);
		}
		queue<int>q;
		for(int i=1;i<=n;i++)if(!d[i]) q.push(i);
		while(!q.empty()){
			int x=q.front();q.pop();
			// cout<<"erase node "<<x<<endl;
			for(int y:E[x]){
				d[y]--,id[y]^=x;
				if(!d[y])q.push(y);
			}
		}



		for(int i=1;i<=n;i++)if(d[i]==1) q.push(i);//cout<<"snode "<<i<<endl;

		while(!q.empty()){
			int x=q.front(),px=id[x]; q.pop();
			for(int y:E[px])if(y!=x){
				d[y]--,id[y]^=px;
				if(d[y]==1)q.push(y);
			}
		}


		int st=0;
		for(int i=1;i<=n;i++)if(d[i]==1){ st=i; break; }

		// vector<int>all;
		int x=st;
		do{
			printf("%d ",x);
			x=id[x];
		}while(x!=st);
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