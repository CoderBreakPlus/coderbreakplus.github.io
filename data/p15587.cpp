// created time: 2026-09-14 08:49:16
#include<bits/stdc++.h>
#include <vector>
#include <array>
std::vector<int> sorting(int);
std::vector<int> ask_question(std::vector<std::array<int, 2>>);

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
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
#define arr array<int,2>
#define ask ask_question

vector<int> sorting(int n){
	vector<arr>tree = {{n-2,n-1},{0,n-2}};
	for(int i=1;i<n-2;i++) tree.pb({0,i});

	vector<int>res=ask(tree);
	if(res[0]){
		tree = {{n-2,n-1},{1,n-2}};
		for(int i=0;i<n-2;i++)if(i!=1)
			tree.pb({1,i});
		res=ask(tree);
	}

	int a=n-2, b=n-1;
	if(res[n-2]) swap(a,b);

	int p=lg2(2*(n-2)-1);
	vector<int> seq(1<<p, -1);
	for(int i=0;i<n-2;i++) seq[i]=i;

	auto calc = [&](vector<pair<int,int>> pairs, bool resolve=0){
		vector<bool>vis(n,0), res(pairs.size(),0); 
		for(int i=0;i<pairs.size();i++){
			auto [x,y] = pairs[i];
			if(!~x) {res[i]=0; continue;}
			if(!~y) {res[i]=1; continue;}
			vis[x]=1,vis[y]=1;
		}
		if(resolve){
			a=b=-1;
			for(int i=0;i<n-2;i++)
				if(!vis[seq[i]]){ a=seq[i]; break; }
			for(int i=n-3;i>=0;i--)
				if(!vis[seq[i]]){ b=seq[i]; break; }
		}
		vector<arr>tree = {{a,b}};
		for(int i=0;i<pairs.size();i++){
			auto [x,y] = pairs[i];
			if(~x && ~y)
				tree.pb({a,x}), tree.pb({x,y}), vis[x]=vis[y]=1;
		}
		vis[a]=vis[b]=1;
		for(int i=0;i<n;i++)if(!vis[i]&&i!=a&&i!=b) tree.pb({a,i});
		
		vector<int>tmp=ask(tree);
		for(int i=0;i<pairs.size();i++)
			if(~pairs[i].fi&&~pairs[i].se)
			res[i]=tmp[pairs[i].se];
		return res;
	};


	for(int i=0;i<p;i++){
		for(int j=i;j>=0;j--){
			vector<pair<int,int>>pairs; int m=0;
			for(int x=0;x<(1<<j);x++)
				for(int y=0;y<(1<<p);y+=(1<<j+1))
					pairs.emplace_back(seq[x+y],seq[x+y+(1<<j)]);

			vector<bool>ret=calc(pairs);
			for(int x=0;x<(1<<j);x++)
				for(int y=0;y<(1<<p);y+=(1<<j+1))
					if(ret[m++]==((y>>(i+1))&1)) swap(seq[x+y],seq[x+y+(1<<j)]);
		}
	}

	while(seq.size()>n-2)seq.pop_back(); seq.pb(-1);
	int A=a,B=b;
	
	int l1=0,r1=n-2,l2=0,r2=n-2;
	if(n>=6){
		while(l1<r1 || l2<r2){
			int m1=(l1+r1)>>1, m2=(l2+r2)>>1,m=0;
			vector<pair<int,int>>pairs;
			if(l1<r1) pairs.pb({A,seq[m1]});
			if(l2<r2) pairs.pb({B,seq[(pairs.size()&&m1==m2)?(++m2):m2]});

			vector<bool>res=calc(pairs,1);
			if(l1<r1){
				if(res[m++]) r1=m1;
				else l1=m1+1;
			}
			if(l2<r2){
				if(res[m++]) r2=m2;
				else l2=m2+1;
			}
		}
	}else{
		while(l1<r1){
			int m1=(l1+r1)>>1;
			if(calc({{A,seq[m1]}},1)[0]) r1=m1;
			else l1=m1+1;
		}
		while(l2<r2){
			int m2=(l2+r2)>>1;
			if(calc({{B,seq[m2]}},1)[0]) r2=m2;
			else l2=m2+1;
		}
	}

	vector<vector<int>>ext(n-1);
	ext[l1].pb(A),ext[l2].pb(B);

	vector<int>love;
	for(int i=0;i<n-2;i++){
		for(int x: ext[i]) love.pb(x);
		love.pb(seq[i]);
	}
	for(int x: ext[n-2]) love.pb(x);
	return love;
}