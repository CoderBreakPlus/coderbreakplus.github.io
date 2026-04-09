// created time: 2026-04-09 10:29:43
// https://qoj.ac/contest/1924/problem/10125
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
int n,q;
char s[1005][1005];

int d[1005][1005][4];
vector<int>G[4000005];

int dp[4000005],ind[4000005];

int code(int i,int j,int o){
	return ((i-1)*n+j)*4+o;
}
tuple<int,int,int> decode(int sta){
	int x=(sta/4-1)/n;
	return {x+1,(sta-x*(4*n))/4,sta&3};
}

const int dx[4]={0,-1,0,1};
const int dy[4]={1,0,-1,0};

map<char,int>mp;

int nxt[4000005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	memset(dp,-1,sizeof(dp));
	queue<int>que;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			for(int d=0;d<4;d++){
				for(int w=3;w<=6;w++){
					int tx=i+dx[(d+w)&3], ty=j+dy[(d+w)&3];
					if(s[tx][ty]!='#'){
						if(1<=tx&&tx<=n&&1<=ty&&ty<=n){
							G[code(tx,ty,(d+w)&3)].pb(code(i,j,d));
							nxt[code(i,j,d)]=code(tx,ty,(d+w)&3);
							// cout<<i<<" "<<j<<" "<<d<<" go to "<<tx<<" "<<ty<<" "<<((d+w)&3)<<endl;
						}
						else{
							que.push(code(i,j,d));
							dp[code(i,j,d)]=1;
							// cout<<i<<" "<<j<<" "<<d<<" success"<<endl;
						}
						break;
					}
				}
			}
		}
	while(!que.empty()){
		int x=que.front();que.pop();
		for(auto y:G[x]){
			dp[y]=dp[x]+1;
			que.push(y);
		}
	}
	while(q--){
		int x=read(),y=read(); char s[5];scanf("%s",s);
		int o=mp[s[0]];

		int sta=code(x,y,o);
		while(sta){
			auto [a,b,c] = decode(sta);
			// cout<<a<<" "<<b<<" "<<c<<endl;
			sta=nxt[sta];
		}
		printf("%d\n", dp[code(x,y,o)]);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	mp['R']=0, mp['U']=1, mp['L']=2, mp['D']=3;
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}