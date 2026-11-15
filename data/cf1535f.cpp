// created time: 2026-11-15 19:20:40
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ull mod = (ull)1e16 + 2137, base = 423;
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

int n,len; ll ans;
char t[200005];
string s[200005],ts;
vector<ull>qz[200005],hz[200005];

vector<int>vec[200005]; int tc;
unordered_map<ull,int>mp;

int sl[200005],sr[200005];
int kl[200005],kr[200005];

int lst[200005];

vector<pair<int,int>>qry[200005];
int c[200005];
void upd(int x,int w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
int ask(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
void solve(int o){
	int m=vec[o].size();
	for(int i=0;i<m;i++)sl[i]=sr[i]=vec[o][i];
	sort(sl,sl+m,[&](int x,int y){return s[x]<s[y];});
	for(int i=0;i<m;i++)reverse(s[vec[o][i]].begin(),s[vec[o][i]].end());

	sort(sr,sr+m,[&](int x,int y){return s[x]<s[y];});
	for(int i=0;i<m;i++)reverse(s[vec[o][i]].begin(),s[vec[o][i]].end());
	for(int i=0;i<m;i++)kl[sl[i]]=kr[sr[i]]=i;

	for(int i=0;i<m;i++){
		int R=i,x=sl[i],p=kr[x];
		lst[len-1]=len;
		for(int j=len-1;j>=0;j--){
			lst[j]=j+1;
			if(s[x][j]<=s[x][j+1])lst[j]=lst[j+1];
		}
		for(int j=len-1;j>=0;j--){
			int vR=R;
			{
				int lf=vR+1,rh=m-1;
				while(lf<=rh){
					int md=(lf+rh)>>1;
					if(!j||qz[sl[md]][j-1]==qz[x][j-1]){
						R=md,lf=md+1;
					}
					else rh=md-1;
				}
			}
			int pos=lst[j];
			int bg=p,ed=p;
			{
				int lf=0,rh=p-1;
				while(lf<=rh){
					int md=(lf+rh)>>1;
					if(hz[sr[md]][pos]==hz[x][pos])
						bg=md,rh=md-1;
					else lf=md+1;
				}
			}
			{
				int lf=p+1,rh=m-1;
				while(lf<=rh){
					int md=(lf+rh)>>1;
					if(hz[sr[md]][pos]==hz[x][pos])
						ed=md,lf=md+1;
					else rh=md-1;
				}
			}
			// int ret=0;
			// for(int i=bg;i<=ed;i++)
			// 	ret+=(vR<kl[sr[i]]&&kl[sr[i]]<=R);
			// ans-=ret;
			// assert(bg<=ed);
			// assert(vR<=R);
			if(bg){
				qry[bg-1].pb(vR,-1);
				qry[bg-1].pb(R,1);
			}
			qry[ed].pb(vR,1);
			qry[ed].pb(R,-1);
		}
	}
	for(int i=0;i<m;i++){
		upd(kl[sr[i]]+1,1);
		for(auto [x,y]:qry[i]){
			ans+=y*ask(x+1);
		}
		qry[i].clear();
	}
	for(int i=0;i<m;i++){
		upd(kl[sr[i]]+1,-1);
	}
}
void procedure(){
	n=read();
	ans=(ll)n*(n-1)/2*1337;
	for(int i=1;i<=n;i++){
		scanf("%s",t);
		int len=strlen(t); ::len=len;
		for(int x=0;x<len;x++)s[i].push_back(t[x]);
		qz[i].resize(len+1);
		hz[i].resize(len+1);

		ull now=0;
		for(int x=0;x<len;x++){
			qz[i][x]=now=(now*base+s[i][x])%mod;
		}
		now=0;
		for(int x=len-1;x>=0;x--){
			hz[i][x]=now=(now*base+s[i][x])%mod;
		}

		ts=s[i];
		sort(ts.begin(),ts.end());
		now=0;
		for(int x=0;x<len;x++)now=(now*base+ts[x])%mod;
		if(!mp.count(now))mp[now]=++tc;
		vec[mp[now]].pb(i);
	}
	for(int i=1;i<=tc;i++){
		int sz=vec[i].size();
		ans-=(ll)sz*(sz-1)/2*1335;
		solve(i);
	}
	printf("%lld\n",ans);
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