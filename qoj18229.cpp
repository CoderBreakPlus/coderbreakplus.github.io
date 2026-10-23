// created time: 2026-05-22 08:57:27
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

inline void upd(int &x,ull y){ x=(x+y)%mod; }

int n,m,k,t,sub,f[1<<19],g[1<<21],h[1<<21],val[100];
vector<pair<int,int>>E[505];
vector<pair<int,int>>G[505];

int nd[21],c,ord0[21],iord0[21],w0,ord1[21],iord1[21],tail[21],w1,buc0[21],buc1[21];
void procedure(){
	n=read(),m=read(),k=read(),t=read(),sub=read();
	for(int i=0;i<n;i++)val[i]=t;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),p=(mod+1-read())%mod;
		if(u>v)swap(u,v);
		int q=(ull)p*(mod+1-p)%mod;
		addmod(val[u]+=p),addmod(val[v]+=p);
		if(u/k==v/k){
			E[u].pb(v%k,q);
		}else{
			G[u].pb(v%k,q);
		}
	}
	f[0]=1;
	for(int e=0;e<n;e+=k){
		// cout<<"e="<<e<<endl;
		int m=min(n-e,k);
		for(int i=0;i<m;i++){
			memset(g,0,sizeof(g));
			for(int j=0;j<(1<<m);j++){
				addmod(g[j]+=f[j]);
				if((~j>>i)&1){
					upd(g[j^(1<<i)], (ull)f[j]*val[e+i]);
					for(auto [k,q]: E[e+i]){
						if((~j>>k)&1)
						upd(g[j^(1<<i)^(1<<k)], (ull)f[j]*q);
					}
				}
			}
			memcpy(f,g,sizeof(f));
		}
		if(e+k>=n){
			printf("%d\n",f[(1<<m)-1]);
			return;
		}
		memset(g,0,sizeof(g));
		// for(int i=0;i<(1<<m);i++){
		// 	bool debug=(i==1);
		// 	c=0;
		// 	int to=0,flg=1,cf=1;
		// 	for(int j=0;j<m;j++)if((~i>>j)&1){
		// 		if(G[e+j].empty()) { flg=0; break; }
		// 		if(G[e+j].size()==1){
		// 			auto [x,y]=G[e+j][0];
		// 			if(to&(1<<x)) { flg=0; break; }
		// 			to|=(1<<x), cf=(ull)cf*y%mod;
		// 		}else{
		// 			nd[c++]=j;
		// 		}
		// 	}
		// 	if(!flg)continue;
		// 	for(int s=0;s<(1<<c);s++){
		// 		int To=to,Flg=1,Cf=cf;
		// 		for(int k=0;k<c;k++){
		// 			int j=nd[k];
		// 			auto [x,y]=G[e+j][(s>>k)&1];
		// 			if(To&(1<<x)) { Flg=0; break; }
		// 			To|=(1<<x),Cf=(ull)Cf*y%mod;
		// 		}
		// 		if(!Flg)continue;
		// 		upd(g[To],(ull)f[i]*Cf%mod);
		// 	}
		// }
		int t=min(k,n-e-m);
		memset(buc0,0,sizeof(buc0));
		memset(buc1,0,sizeof(buc1));

		w0=w1=0;
		for(int T=0;T<m;T++){
			int low=1e9,node=-1;			
			for(int j=0;j<m;j++)if(!buc0[j]){
				int now=0;
				for(auto [k,v]:G[e+j])now+=!buc1[k];
				if(now<low){
					low=now;
					node=j;
				}
			}assert(~node);
			buc0[node]=1;
			for(auto [k,v]:G[e+node])if(!buc1[k])buc1[k]=1,ord1[w1]=k,iord1[k]=w1,w1++;
			ord0[w0]=node,iord0[node]=w0;
			tail[w0]=w1,w0++;
		}

		memset(g,0,sizeof(g));
		for(int i=0;i<(1<<m);i++){
			int sta=0;
			for(int j=0;j<m;j++)
				sta^=(((i>>j)&1)<<iord0[j]);
			g[sta]=f[i];
		}

		// for(int i=0;i<w1;i++) cout<<ord1[i]<<" "; cout<<endl;
		int sz=m;
		for(int i=0;i<m;i++){
			memcpy(h,g,sizeof(h));
			memset(g,0,sizeof(g));
			int new_sz=m-i-1+tail[i];
			for(int j=0;j<(1<<sz);j++){
				if(j&1) addmod(g[j>>1]+=h[j]);
				else{
					for(auto [k,v]:G[e+ord0[i]]){
						int p=iord1[k]+m-i;
						if((~j>>p)&1){
							int sta=(j^(1<<p))>>1;
							assert(sta<(1<<new_sz));
							// if(sta>=(1<<new_sz)){
							// 	// cout<<"p="<<p<<endl;
							// 	exit(0);
							// }
							upd(g[sta],(ull)h[j]*v);
						}
					}
				}
			}
			sz=new_sz;
			// assert(sz<=20);
		}
		memset(f,0,sizeof(f));
		for(int i=0;i<(1<<w1);i++){
			int sta=0;
			for(int j=0;j<w1;j++)
				sta|=((i>>j)&1)<<ord1[j];
			f[sta]=g[i];
		}
	}
}
int main(){
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}