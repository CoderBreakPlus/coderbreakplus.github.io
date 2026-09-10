// created time: 2026-09-10 08:49:49
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

int n1,n2,m,u[10005],v[10005];
bool sta[10005];
vector<pair<int,int>>E[10005];

bool ok(int i){
	return i>0?sta[i]:!sta[-i];
}
int prv[10005],vis[10005],mch[10005];
int que[10005],hd,tl;
void procedure(){
	n1=read(),n2=read(),m=read();
	for(int i=1;i<=n1+n2;i++)E[i].clear(),mch[i]=0;
	
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read()+n1;
		E[u[i]].pb(v[i],i),E[v[i]].pb(u[i],-i);
		sta[i]=0;
		// 0: walk right->left
		// 1: walk left->right
	}

	for(int i=1;i<=n2;i++){
		// cout<<"search "<<i<<endl;
		memset(vis,0,sizeof(vis));
		que[hd=tl=1]=i+n1; vis[i+n1]=1;
		while(hd<=tl){
			int x=que[hd++];
			for(auto [y,i]:E[x])if(!vis[y]&&ok(i)){
				// cout<<"solve "<<y<<endl;
				vis[y]=1,prv[y]=i;
				que[++tl]=y;
			}
		}
		for(int j=1;j<=n1;j++)if(vis[j]&&!mch[j]){
			mch[j]=mch[i+n1]=1;
			// cout<<"match "<<i+n1<<" and "<<j<<endl;
			int x=j;
			while(x!=i+n1){
				int id=max(prv[x],-prv[x]); sta[id]^=1;
				// cout<<"reverse "<<id<<": "<<u[id]<<"->"<<v[id]<<endl;
				// cout<<"walk "<<x<<" by "<<id<<" from "<<x<<" to "<<(u[id]^v[id]^x)<<endl;
				x=u[id]^v[id]^x;
			}
			break;
		}
	}

	int ans=0;
	for(int i=1;i<=n2;i++){
		int cnt=0;
		for(int j=i;j<=n2;j++){
			cnt+=mch[j+n1];
			// cout<<i<<"->"<<j<<" ans = "<<cnt<<endl;
			ans=(ans+(ull)cnt*i*j*((i^j)+1))%mod;
		}

		if(mch[i+n1]){
			memset(vis,0,sizeof(vis));
			que[hd=tl=1]=i+n1; vis[i+n1]=1;
			while(hd<=tl){
				int x=que[hd++];
				// cout<<"at "<<x<<endl;
				for(auto [y,i]:E[x])if(!vis[y]&&!ok(i)){
					// cout<<"maybe "<<y<<" i="<<i<<endl;
					// cout<<"sta = "<<sta[max(i,-i)]<<endl;
					// if(ok(i))continue;
					// cout<<"visit "<<y<<endl;
					vis[y]=1,prv[y]=i;
					que[++tl]=y;
				}
			}
			for(int j=i+1;j<=n2;j++)if(vis[j+n1]&&!mch[j+n1]){
				mch[i+n1]=0, mch[j+n1]=1;
				// cout<<i+n1<<" replaced by "<<j+n1<<endl;
				int x=j+n1;
				while(x!=i+n1){
					int id=max(prv[x],-prv[x]); sta[id]^=1;
					x=u[id]^v[id]^x;
				}
				break;
			}
		}
	}
	printf("%d\n",ans);
	// fflush(stdout);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}