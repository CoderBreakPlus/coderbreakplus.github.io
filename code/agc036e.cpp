// created time: 2026-11-08 13:56:59
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
char s[1000005];
int n,cnt[256];
char o[3];

void scan1(){
	int m=n; n=0;
	for(int i=1;i<=m;i++)
		if(s[i]!=s[n])s[++n]=s[i];
	s[0]='F',s[n+1]='L';
}
void scan2(int &k){
	int m=n; n=0;
	for(int i=1;i<=m;i++){
		if(s[i]==o[0]&&s[n]!=s[i+1]&&k) k--,cnt[o[0]]--;
		else s[++n]=s[i];
	}
	s[0]='F',s[n+1]='L';
}
void scan3(int k){
	int m=n; n=0;
	for(int i=1;i<=m;i++){
		s[++n]=s[i];
		if(n>=2 && k && ((s[n-1]==o[0]&&s[n]==o[2])||(s[n-1]==o[2]&&s[n]==o[0])))
			n-=2,k--,cnt[o[0]]--,cnt[o[2]]--;
	}
	assert(!k);
	s[0]='F',s[n+1]='L';
}
void scan4(int k){
	int m=n; n=0;
	// cout<<"o2: "<<o[2]<<endl;
	for(int i=1;i<=m;i++){
		s[++n]=s[i];
		if(n>=2 && k && ((s[n-1]==o[0]&&s[n]==o[1])||(s[n-1]==o[1]&&s[n]==o[0]))){
			// cout<<"calc: "<<
			if(s[n-2]!=o[2] || s[i+1]!=o[2])
				n-=2,k--,cnt[o[0]]--,cnt[o[1]]--;
		}
	}
	s[0]='F',s[n+1]='L';
}
void print(){
	for(int i=1;i<=n;i++){
		putchar(s[i]);
		assert(s[i]!=s[i-1]);
	}
	puts("");
}
void procedure(){
	scanf("%s",s+1);n=strlen(s+1);
	scan1();
	for(int i=1;i<=n;i++)
		cnt[s[i]]++;
	o[0]='A',o[1]='B',o[2]='C';
	sort(o,o+3,[](char x,char y){ return cnt[x]>cnt[y]; });

	int dc=cnt[o[0]]-cnt[o[1]];
	scan2(dc);
	// print();
	// cout<<"dc="<<dc<<endl;
	if(dc) scan3(dc);

	assert(cnt[o[0]]==cnt[o[1]]);
	scan4(cnt[o[0]]-cnt[o[2]]);
	print();
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