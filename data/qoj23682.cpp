// created time: 2026-11-12 16:16:39
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
char s[200005],t[200005],sz;
int q,l[200005],r[200005];

const int INF=1e9;
int brute(char* s,int len){
	auto dfs=[&](auto&& dfs,string t)->int{
		int ans=-1,n=t.size();
		for(int i=0;i+1<n;i++){
			if((t[i]==':'&&t[i+1]=='(')||(t[i]==')'&&t[i+1]==':')){
				string u=t.substr(0,i)+t.substr(i+2);
				ans=max(ans,dfs(dfs,u));
			}
		}
		if(ans!=-1)return ans;
		ans=0;
		for(int i=0;i+1<n;i++)
			if((t[i]==':'&&t[i+1]==')')||(t[i]=='('&&t[i+1]==':'))
				ans++;
		return ans;
	};
	return dfs(dfs,string(s,len));
}
void procedure(){
	scanf("%s",s+1); q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();

		int x=l[i];
		// '' ':' '(' ')'
		// 0   1   2   3
		int sz=0;
		for(int j=l[i];j<=r[i];j++){
			t[++sz]=s[j];
			if(sz>=2&&t[sz]=='('&&t[sz-1]==':')sz-=2;
			if(sz>=2&&t[sz]==':'&&t[sz-1]==')')sz-=2;
		}
		int w=0,ans=0;
		for(int j=2;j<=sz;j++){
			ans+=(t[j]==')'&&t[j-1]==':')||(t[j]==':'&&t[j-1]=='(');
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