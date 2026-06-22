// created time: 2026-06-22 18:39:46
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

int n,k,stk[5005],tp,vis[5005],ans[5005]; char s[5005];
void procedure(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)vis[i]=ans[i]=0;
	tp=0;

	int mn=0,val=0,cur=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='('){
			cur++;
			stk[++tp]=i;
		}else{
			cur--;
			if(tp) vis[stk[tp--]]=vis[i]=1;
		}
		if(cur<=val)val=cur,mn=i;
	}

	// cout<<"mn="<<mn<<endl;
	vector<int>res;
	for(int i=1;i<=n;i++)if(vis[i]){
		if(s[i]==')'&&i>mn) res.pb(i);
		if(s[i]=='('&&i<=mn) res.pb(i);
	}
	// for(auto x: res) cout<<x<<" ";cout<<endl;

	while(k-- && !res.empty()){
		ans[res.back()]=1;
		res.pop_back();
	}
	for(int i=1;i<=n;i++)printf("%d",ans[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}