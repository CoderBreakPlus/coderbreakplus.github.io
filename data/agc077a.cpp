// created time: 2026-06-23 13:47:05
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

int n;
char a[500005],b[500005],cp[500005],cq[500005];

void procedure(){
	vector<pair<int,int>>v1,v2;

	n=read();
	scanf("%s%s",a+1,b+1);

	int cnt=0, L=0, R=0, sb=0;
	for(int i=1;i<=n;i++){
		cp[i]=a[i],cq[i]=b[i];
		sb+=(a[i]=='A')-(a[i]=='B');
		cnt+=(a[i]=='A')-(b[i]=='A');
		if(a[i]!=b[i] && !L){
			L=i;
			if(a[i]=='B'){ puts("No"); return; }
		}
		if(a[i]!=b[i]) R=i;
	}
	if(cnt || a[R]=='A'){ puts("No"); return; }

	if(!L){
		puts("Yes\n0");
		return;
	}

	reverse(a+L+1,a+R);

	int N=R-L-1;

	auto push1 = [&](int x,int y){
		x-=L,y-=L;
		v1.pb(N-y+1+L,N-x+1+L);
	};
	auto push2 = [&](int x,int y){
		v2.pb(x,y);
	};

	// B...A -> A... B on rev(X) and Y

	if(sb<=0){ // look at A
		vector<int>sa,sb;
		for(int i=L+1;i<R;i++){
			if(a[i]=='A')sa.pb(i);
			if(b[i]=='A')sb.pb(i);
		}

		for(int i=0;i<sa.size();i++){
			if(sa[i]==sb[i]) continue;
			if(sa[i]<sb[i]) push2(sa[i],sb[i]);
			else push1(sb[i],sa[i]);
		}
	}else{
		vector<int>sa,sb;
		for(int i=R-1;i>L;i--){
			if(a[i]=='B')sa.pb(i);
			if(b[i]=='B')sb.pb(i);
		}
		for(int i=0;i<sa.size();i++){
			if(sa[i]==sb[i]) continue;
			if(sa[i]>sb[i]) push2(sb[i],sa[i]);
			else push1(sa[i],sb[i]);
		}
	}
	printf("Yes\n%d\n",(int)v1.size()+1+(int)v2.size());

	auto opt = [&](int x,int y){
		// #ifdef LOCAL
		// 	assert(cp[x]=='A'&&cp[y]=='B');
		// 	reverse(cp+x,cp+y+1);
		// #endif
		printf("%d %d\n",x,y);
	};
	for(auto [x,y]: v1) opt(x,y);
	opt(L,R);
	reverse(v2.begin(),v2.end());
	for(auto [x,y]: v2) opt(x,y);

	// #ifdef LOCAL
		// for(int i=1;i<=n;i++)
		// 	assert(cp[i]==cq[i]);
	// #endif
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure();
		// cout<<"done "<<i<<endl;
	}
	return 0;
}