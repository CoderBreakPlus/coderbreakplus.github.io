// created time: 2026-05-12 15:38:49
// https://qoj.ac/contest/1906/problem/10080
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

char s[300005]; int val[300005];
int n;
void procedure(){
	scanf("%s",s+1);n=strlen(s+1);
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(isdigit(s[i]))cnt-=s[i]-'0',val[i]=-s[i]+'0';
		else cnt++,val[i]=(s[i]=='(');
	}
	for(int i=n-1;i>=1;i--)val[i]+=val[i+1];
	val[n+1]=0;
	if(cnt&1){
		puts("No");
		return;
	}
	deque<int>a,b;
	for(int i=1;i<=n;i++){
		if(s[i]=='(')a.push_back(i);
		else if(s[i]==')')b.push_back(i);
		else{
			int w=s[i]-'0';
			int g1=min((int)b.size(),w),g2=w-g1;
			while(g1>=0&&g2>=0&&(int)a.size()-g2+val[i+1]>cnt/2)g2++,g1--;
			if(g1<0||g2<0){
				puts("No");
				return;
			}
			if(g1>b.size()||g2>a.size()){
				puts("No");
				return;
			}
			// assert(g1<=b.size()),assert(g2<=a.size());
			while(g1--) b.pop_front();
			while(g2--) a.pop_back();
		}
	}
	// for(auto x:a)cout<<x<<" ";cout<<endl;
	// for(auto x:b)cout<<x<<" ";cout<<endl;
	// assert(a.size()==cnt/2);
	// assert(b.size()==cnt/2);

	if(a.size()!=cnt/2||b.size()!=cnt/2){
		puts("No");
		return;
	}
	
	int t=0;
	while(!a.empty()&&!b.empty()){
		if(a.front()<b.front())a.pop_front(),t++;
		else b.pop_front(),t--;
		if(t<0){ puts("No");return; }
	} 
	puts("Yes");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure(),
	fflush(stdout);
	return 0;
}