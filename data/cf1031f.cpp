// created time: 2026-05-05 07:55:25
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
const int B = 12;
const int prim[B] = {2,3,5,7,11,13,17,19,23,29,31,37};
vector<int>seq(B,0);
vector<int>s[4005]; int id;
map<vector<int>,int>mp;
vector<int>vs[1000005];

int dis[4005][4005];
void dfs(int x,int lst,ll val,int val2){
	s[++id]=seq;
	mp[seq]=id;
	vs[val2].pb(id);
	// for(int i:seq)printf("%d ",i);puts("");
	for(seq[x]=1;seq[x]<=lst;seq[x]++){
		val*=prim[x];
		if(val<=1e9)dfs(x+1,seq[x],val,val2*(1+seq[x]));
		else{
			seq[x]=0;break;
		}
	}
	seq[x]=0;
}
int fuck[4005],tmp[4005][4005];
void procedure(){
	memset(dis,0x3f,sizeof(dis));
	dfs(0,20,1,1);
	int xid=id;
	for(int i=1;i<=1e6;i++)
		if(vs[i].size()){
			++id;fuck[id]=i;
		}
	// cout<<"id="<<id<<endl;
	for(int i=1;i<=xid;i++){
		for(int j=1;j<=xid;j++){
			dis[i][j]=0;
			for(int k=0;k<B;k++)dis[i][j]+=max(s[i][k]-s[j][k],s[j][k]-s[i][k]);
		}
	}
	for(int x=1;x<=id;x++){
		for(int i=xid+1;i<=id;i++){
			tmp[x][i]=1e9;
			for(int z: vs[fuck[i]])
				tmp[x][i]=min(tmp[x][i],dis[x][z]);
		}
	}
	int q=read();
	while(q--){
		int x=read(),y=read(),ans=1e9;

		vector<int>seqx,seqy;
		for(int d=2;d*d<=x;d++)if(x%d==0){
			int c=0;while(x%d==0)x/=d,c++;seqx.pb(c);
		}if(x>1)seqx.pb(1);
		sort(seqx.begin(),seqx.end(),greater<int>()),seqx.resize(B,0);

		for(int d=2;d*d<=y;d++)if(y%d==0){
			int c=0;while(y%d==0)y/=d,c++;seqy.pb(c);
		}if(y>1)seqy.pb(1);
		sort(seqy.begin(),seqy.end(),greater<int>()),seqy.resize(B,0);

		// for(auto x:seqx)cout<<x<<" ";cout<<endl;
		// for(auto y:seqy)cout<<y<<" ";cout<<endl;
		// assert(mp.count(seqx));
		// assert(mp.count(seqy));

		x=mp[seqx],y=mp[seqy];
		for(int i=xid+1;i<=id;i++){
			ans=min(ans, tmp[x][i]+tmp[y][i]);
		}
		printf("%d\n",ans);
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