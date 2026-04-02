// created time: 2026-04-02 17:47:14
// A. (-1,1)-Sumplete
// https://qoj.ac/contest/1459/problem/7857
// 场不切的过的人很多的题

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

int n,a[4005],b[4005];
char s[4005][4005],t[4005][4005];

void procedure(){	
	n=read();
	for(int i=0;i<n;i++) scanf("%s",s[i]);
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<n;i++)b[i]=read();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(s[i][j]=='-') a[i]++,b[j]++;
		}

	int sum=0;
	for(int i=0;i<n;i++){sum+=a[i];if(a[i]<0||a[i]>n){puts("No");return;}}
	for(int i=0;i<n;i++){sum-=b[i];if(b[i]<0||b[i]>n){puts("No");return;}}

	if(sum!=0){
		puts("No");
		return;
	}

	// for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<endl;
	// for(int i=0;i<n;i++)cout<<b[i]<<" ";cout<<endl;

	vector<int>vi,vj;
	for(int i=0;i<n;i++) vi.pb(i),vj.pb(i);

	sort(vi.begin(),vi.end(),[](int x,int y){return a[x]>a[y]; });

	for(int I=0;I<n;I++){
		int i=vi[I];
		sort(vj.begin(),vj.end(),[](int x,int y){return b[x]>b[y]; });
		for(int J=0;J<n;J++){
			int j=vj[J];
			if(a[i]&&b[j]) a[i]--,b[j]--,t[i][j]=('1'^(s[i][j]=='-'));
			else t[i][j]=('0'^(s[i][j]=='-'));
		}
	}
	for(int i=0;i<n;i++) if(a[i]||b[i]){puts("No");return;}
	puts("Yes");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)putchar(t[i][j]);
		puts("");
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