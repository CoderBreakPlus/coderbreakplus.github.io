// created time: 2026-04-04 11:13:42
// B. Cat Cut
// https://qoj.ac/contest/3575/problem/17714
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const ull mod = (ull)1e18 + 3;
ull base = rng(1e8,1e9);

const int B = 13;
int n,m;
char s[4000005];

int nxt[4000005][B];
ull hsh[4000005][B],pw[(1<<B)+5];

bool cmp(int a,int b){
	for(int i=B-1;i>=0;i--){
		if(hsh[a][i] == hsh[b][i]){
			a=nxt[a][i],b=nxt[b][i];
		}
	}
	return s[a]<s[b];
}
void cons(int a,int x){
	hsh[a][0] = s[a];
	nxt[a][0] = x;
	for(int i=1;i<B;i++){
		hsh[a][i] = ((__int128)pw[1<<i-1]*hsh[a][i-1] + hsh[nxt[a][i-1]][i-1]) % mod;
		nxt[a][i] = nxt[nxt[a][i-1]][i-1];
	}
}
void procedure(){
	n=read(),m=read();
	pw[0]=1;
	for(int i=1;i<=(1<<B);i++)pw[i]=(__int128)pw[i-1]*base%mod;

	s[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1+(i-1)*m);
	}

	int ok = -1;
	for(int i=n*m;i>=1;i--){
		int nxt = i+1;
		if(i>m && ~ok && cmp(ok, nxt)) nxt = ok;
		cons(i, nxt);
		if(i%m==1 && (!(~ok) || cmp(i, ok))) ok = i;
	}
	int ans = (n-1)*m+1;
	for(int i=(n-1)*m;i>=1;i--)
		if(cmp(i, ans)) ans = i;

	for(int i=1;i<=m;i++){
		putchar(s[ans]);
		ans = nxt[ans][0];
	}
	puts("");
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