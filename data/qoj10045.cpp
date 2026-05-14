// created time: 2026-05-14 16:42:16
#include<bits/stdc++.h>
#ifdef N1K_LOCAL
	bool memory_start;
#else
	#pragma GCC optimize(3)
	#pragma GCC optimize("Ofast,no-stack-protector")
	#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
	#pragma GCC optimize("Ofast")
	#pragma GCC optimize("inline")
	#pragma GCC optimize("-fgcse")
	#pragma GCC optimize("-fgcse-lm")
	#pragma GCC optimize("-fipa-sra")
	#pragma GCC optimize("-ftree-pre")
	#pragma GCC optimize("-ftree-vrp")
	#pragma GCC optimize("-fpeephole2")
	#pragma GCC optimize("-ffast-math")
	#pragma GCC optimize("-fsched-spec")
	#pragma GCC optimize("unroll-loops")
	#pragma GCC optimize("-falign-jumps")
	#pragma GCC optimize("-falign-loops")
	#pragma GCC optimize("-falign-labels")
	#pragma GCC optimize("-fdevirtualize")
	#pragma GCC optimize("-fcaller-saves")
	#pragma GCC optimize("-fcrossjumping")
	#pragma GCC optimize("-fthread-jumps")
	#pragma GCC optimize("-funroll-loops")
	#pragma GCC optimize("-fwhole-program")
	#pragma GCC optimize("-freorder-blocks")
	#pragma GCC optimize("-fschedule-insns")
	#pragma GCC optimize("inline-functions")
	#pragma GCC optimize("-ftree-tail-merge")
	#pragma GCC optimize("-fschedule-insns2")
	#pragma GCC optimize("-fstrict-aliasing")
	#pragma GCC optimize("-fstrict-overflow")
	#pragma GCC optimize("-falign-functions")
	#pragma GCC optimize("-fcse-skip-blocks")
	#pragma GCC optimize("-fcse-follow-jumps")
	#pragma GCC optimize("-fsched-interblock")
	#pragma GCC optimize("-fpartial-inlining")
	#pragma GCC optimize("no-stack-protector")
	#pragma GCC optimize("-freorder-functions")
	#pragma GCC optimize("-findirect-inlining")
	#pragma GCC optimize("-fhoist-adjacent-loads")
	#pragma GCC optimize("-frerun-cse-after-loop")
	#pragma GCC optimize("inline-small-functions")
	#pragma GCC optimize("-finline-small-functions")
	#pragma GCC optimize("-ftree-switch-conversion")
	#pragma GCC optimize("-foptimize-sibling-calls")
	#pragma GCC optimize("-fexpensive-optimizations")
	#pragma GCC optimize("-funsafe-loop-optimizations")
	#pragma GCC optimize("inline-functions-called-once")
	#pragma GCC optimize("-fdelete-null-pointer-checks")
	#pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2",3) 
#endif
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
namespace IO{
	char buf[1 << 20], *p1 = buf, *p2 = buf;
	#define getchar() (p1 == p2 && (p2 = (p1 = buf) + \
		fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
	inline ll read(){
		ll x = 0,h = 1;
		char ch = getchar();
		while(!(ch=='-'||('0'<=ch&&ch<='9'))) ch = getchar();
		if(ch=='-') h = -1;
		else x = ch-'0';
		ch = getchar();
		while('0'<=ch&&ch<='9'){
			x = x*10+ch-'0';
			ch = getchar();
		}
		return x*h;
	}
	inline ll digread(){
		char ch = getchar();
		while(!('0'<=ch&&ch<='9')) ch = getchar();
		return ch-'0';
	}
	inline char readCH(){
		char ch = getchar();
		while(!(ch=='x')) ch = getchar();
		return ch;
	}
	inline void print(ll x){
		if(x>9) print(x/10);
		putchar(x%10+'0');
	}
	inline void write(ll x){
		if(x<0) putchar('-'),x = -x;
		print(x);
	}
}
using namespace IO;
namespace MathLab{
	inline ll ksm(ll _x,ll _k,ll _mod){
		ll _res = 1;
		while(_k){
			if(_k&1) _res = _res*_x%_mod;
			_x = _x*_x%_mod;
			_k>>=1;
		}
		return _res;
	}
	inline ll phi(ll _x){
		ll _res = _x;
		for(ll _i = 2; _i*_i <= _x; _i++){
			if(_x%_i==0){
				while(_x%_i==0) _x/=_i;
				_res = _res*(_i-1)/_i;
			}
		}
		if(_x>1) _res = _res*(_x-1)/_x;
		return _res;
	}
	inline ll gcd(ll _x,ll _y){
		return _y?gcd(_y,_x%_y):_x;
	}
	inline ll lcm(ll _x,ll _y){
		return _x*_y/gcd(_x,_y);
	}
	inline bool IsPrime(ll _x){
		if(_x<=1) return 0;
		for(ll _i = 2; _i*_i <= _x; _i++) if(_x%_i==0) return 1;
		return 0;
	}
	inline void AddMod(ll &_x,ll _y,ll _mod){
		_x = (_x+_y>=_mod?_x+_y-_mod:_x+_y);
	}
	inline void MulMod(ll &_x,ll _y,ll _mod){
		_x = _x*_y%_mod;
	}
	inline ll GetMid(ll _x){
		return (_x&1LL)?((_x>>1LL)+1LL):(_x>>1LL);
	}
	inline ll GetFac(ll _x,ll _mod){
		return _x?GetFac(_x-1,_mod)*_x%_mod:1LL;
	}
	inline ll Inv(ll _x,ll _mod){
		return ksm(_x,_mod-2,_mod);
	}
	
}
#define File(name)                     \
    freopen(#name ".in", "r", stdin);  \
    freopen(#name ".out", "w", stdout);
#define ERR assert(0)
//#define RunTime ((double)clock()/CLOCKS_PER_SEC)
/*
*/
namespace G4M1{
	const ll N = 400010;
	ll n,m;
	vector<ll> vec[N];
	ll reg[N],lnk[N];
	bool vis[N];
	map<ll,ll> cnt[N];
	mt19937 rng(time(0));
	void dfs(ll u){
		while(!cnt[u].empty()){
			auto [v,c] = *cnt[u].begin();
			if(!c) cnt[u].erase(cnt[u].begin());
			else{
				cnt[u][v]--,cnt[v][u]--;
				vec[u].push_back(v);
				dfs(v);
			}
		}
	}
	
	void main(){
		n = read(),m = read();
		for(ll i = 1; i <= m*2; i++) for(ll j = 1; j <= n; j++) cnt[j][read()]++;
		for(ll u = 1; u <= n; u++) dfs(u);
		for(ll k = m; k >= 1; k--){
			iota(reg+1,reg+n+1,1);
			fill(lnk+1,lnk+n+1,0);
			shuffle(reg+1,reg+n+1,rng);
			for(ll i = 1; i <= n; i++){
				ll u = reg[i];
				vector<ll> q;
				while(u){
					ll v = vec[u][rng()%k];
					while(lnk[v]==u) v = vec[u][rng()%k];
					while(vis[v]){
						vis[q.back()] = 0;
						q.pop_back();
					}
					u = lnk[v];
					vis[v] = 1;
					q.push_back(v);
				}
				u = reg[i];
				for(ll w : q){
					vis[w] = 0;
					swap(lnk[w],u);
				}
			}
			for(ll i = 1; i <= n; i++){
				printf("%lld ",lnk[i]);
				vec[lnk[i]].erase(find(vec[lnk[i]].begin(),vec[lnk[i]].end(),i));
			}
			puts("");
		}
	}
}
#ifdef N1K_LOCAL
	bool memory_end;
#endif
int main(){
	#ifdef N1K_LOCAL 
		fprintf(stderr,"Using N1K_LOCAL\n");
	#endif
	ll T = 1;
	while(T--) G4M1::main();
	#ifdef N1K_LOCAL
		fprintf(stderr,"\nEnd---\n");
		double run_time=1.0*clock()/CLOCKS_PER_SEC;
		double run_space=((&memory_end)-(&memory_start))/1048576.0;
		fprintf(stderr,"Time: %.3lfs Space:%.3lfMB\n",run_time,run_space);
	#endif
	return 0;
}
/*

*/