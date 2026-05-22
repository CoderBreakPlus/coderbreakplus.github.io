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

int n,m,k,t,sub,f[1<<19],g[1<<19],h[1<<19],val[100];
vector<pair<int,int>>E[505];
vector<pair<int,int>>G[505];

int nd[19],c;
void procedure(){
	n=read(),m=read(),k=read(),t=read(),sub=read();
	for(int i=0;i<n;i++)val[i]=t;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),p=(mod+1-read())%mod;
		if(u>v)swap(u,v);
		int q=(ull)p*(mod+1-p)%mod;
		// cout<<"q="<<q<<endl;
		addmod(val[u]+=p),addmod(val[v]+=p);

		if(u/k==v/k){
			E[u].pb(v%k,q);
		}else{
			G[u].pb(v%k,q);
		}
	}
	// for(int i=0;i<n;i++) cout<<val[i]<<" ";cout<<endl;

	f[0]=1;
	for(int e=0;e<n;e+=k){
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
		// cout<<"e="<<e<<" first"<<endl;
		// for(int i=0;i<(1<<m);i++){
		// 	if(f[i]) cout<<i<<" f="<<f[i]<<endl;
		// }
		memset(g,0,sizeof(g));
		for(int i=0;i<(1<<m);i++){
			cout<<"i="<<i<<endl;
			// cout<<i<<" f="<<f[i]<<endl;
			// bool debug=(i==1);
			c=0;
			int to=0,flg=1,cf=1;
			for(int j=0;j<m;j++)if((~i>>j)&1){
				if(G[e+j].empty()) { flg=0; break; }
				if(G[e+j].size()==1){
					auto [x,y]=G[e+j][0];
					if(to&(1<<x)) { flg=0; break; }
					to|=(1<<x), cf=(ull)cf*y%mod;
				}else{
					nd[c++]=j;
					// if(debug)cout<<"find "<<j<<" flexible"<<endl;
				}
			}
			if(!flg)continue;
			for(int s=0;s<(1<<c);s++){
				int To=to,Flg=1,Cf=cf;
				for(int k=0;k<c;k++){
					int j=nd[k];
					// cout<<"j="<<j<<endl;
					auto [x,y]=G[e+j][(s>>k)&1];
					// if(debug)cout<<x<<","<<y<<endl;
					if(To&(1<<x)) { Flg=0; break; }
					// assert(x>=0&&x<k);
					To|=(1<<x),Cf=(ull)Cf*y%mod;
				}
				if(!Flg)continue;
				if(Cf)cout<<"trans "<<i<<"->"<<To<<" cf = "<<Cf<<endl;
				upd(g[To],(ull)f[i]*Cf%mod);
			}
		}
		memcpy(f,g,sizeof(f));
		// cout<<"e="<<e<<" second"<<endl;
		// for(int i=0;i<(1<<m);i++){
		// 	if(f[i]) cout<<i<<" f="<<f[i]<<endl;
		// }
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}