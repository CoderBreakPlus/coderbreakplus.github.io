// created time: 2026-10-10 14:17:26
#include"cycle.h"
#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"grader.cpp"
#endif
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

void init(int op,int t){

}

int n,d[1005][2005];
tuple<int,int,int> prv[1005][2005];
char s[3005];
int nxt[3005][26];

bool vis[26];

pair<int,string> construct(string S){
	n=S.size(); int cnt=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++)vis[S[i]-'a']=1;
	for(int d=1;d<=n;d++)if(n%d==0){
		bool flg=1;
		for(int j=d;j<n;j++)flg&=(S[j]==S[j-d]);
		if(flg){
			cnt=n/d;
			n=d; break;
		}
	}
	for(int i=0;i<n;i++) s[i]=s[n+i]=s[2*n+i]=S[i];
	memset(nxt[3*n-1],-1,sizeof(nxt[3*n-1]));
	for(int i=3*n-1;i>0;i--){
		memcpy(nxt[i-1],nxt[i],sizeof(nxt[i]));
		nxt[i-1][s[i]-'a']=i;
	}

	queue<pair<int,int>>q;
	for(int i=0;i<n;i++)
		for(int j=0;j<2*n;j++)d[i][j]=-1;
	for(int i=0;i<n;i++) d[i][i+1]=0,q.emplace(i,i+1);
	while(!q.empty()){
		auto [a,b]=q.front(); q.pop();
		if(a+n==b) {
			string S;
			while(a+1!=b){
				auto [c,aa,bb]=prv[a][b];
				S+=('a'+c);
				a=aa,b=bb;
			}
			reverse(S.begin(),S.end());
			return {cnt,S};
		}
		for(int x=0;x<26;x++)if(vis[x]){
			int aa=nxt[a][x],bb=nxt[b][x];
			if(aa>=n)aa-=n,bb-=n;
			if(~d[aa][bb])continue;

			d[aa][bb]=d[a][b]+1;
			prv[aa][bb]={x,a,b};
			q.emplace(aa,bb);
		}
	}
	// assert(0);
}

bool check(string S, string C){
	n=S.size(); int cnt=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++)vis[S[i]-'a']=1;
	for(int d=1;d<=n;d++)if(n%d==0){
		bool flg=1;
		for(int j=d;j<n;j++)flg&=(S[j]==S[j-d]);
		if(flg){
			cnt=n/d;
			n=d; break;
		}
	}
	for(int i=0;i<n;i++) s[i]=s[i+n]=S[i];

	memset(nxt[2*n-1],-1,sizeof(nxt[2*n-1]));
	for(int i=2*n-1;i>0;i--){
		memcpy(nxt[i-1],nxt[i],sizeof(nxt[i]));
		nxt[i-1][s[i]-'a']=i;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<26;j++)if(vis[j])
			nxt[i][j]-=i;
	int L=0,R=n;

	auto calc=[&](int x){
		for(char c: C){
			c-='a';
			if(!vis[c])continue;
			x+=nxt[x%n][c];
		}
		return x;
	};
	int v0=calc(0);
	while(L+1<R){
		int M=(L+R)>>1,vM=calc(M);
		if(vM!=v0 && vM!=v0+n) return 0;
		if(vM==v0) L=M; else R=M;
	}
	return 1;
}
