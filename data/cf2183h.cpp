// created time: 2026-08-26 19:48:12
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
#define LL __int128

const LL INF = 1e36;

int n,k,a[200005],cnt;
LL qz[200005];

void print(LL x){
	if(x==0){puts("0");return;}
	vector<int>ch;
	if(x<0)putchar('-'),x=-x;
	while(x) ch.pb(x%10),x/=10;
	reverse(ch.begin(),ch.end());
	for(int x:ch) putchar(x+'0');
	puts("");
}
pair<LL,int> dp[200005];
int jc[200005];

int que[200005],sl[200005],tl;

pair<LL,int> check(LL c){
	auto calc = [&](int i,int j) -> pair<LL,int>{
		if(i>j) return {INF, 0}; 
		return {dp[i].fi + (qz[j]-qz[i])*(j-i) + c, dp[i].se + 1};
	};
	tl=0;
	for(int i=n-cnt;i<=n;i++){
		// cout<<"i = "<<i<<" qz="<<(ll)qz[i]<<endl;
		dp[i] = {qz[i] * i + c, 1};
		int lft=1,rht=tl,ans=-1;
		while(lft<=rht){
			int mid=(lft+rht)>>1;
			if(sl[mid] <= i) {
				ans=mid;
				lft=mid+1;
			}else
				rht=mid-1;
		}
		// cout<<"dp "<<i<<" = "<<(ll)dp[i].fi<<" "<<dp[i].se<<endl;
		if(~ans){
			// cout<<"from "<<que[ans]<<" to "<<i<<endl;
			chkmin(dp[i], calc(que[ans],i));
		}
		while(tl && calc(que[tl],sl[tl]) > calc(i,sl[tl])) tl--;

		// cout<<"dp "<<i<<" = "<<(ll)dp[i].fi<<" "<<dp[i].se<<endl;
		// cout<<"cut3"<<endl;
		if(tl){
			lft=sl[tl], rht=n, ans=n+1;
			while(lft<=rht){
				int mid=(lft+rht)>>1;
				if(calc(que[tl],mid) > calc(i,mid)) ans=mid,rht=mid-1;
				else lft=mid+1;
			}
			que[++tl]=i, sl[tl]=ans;
		}else
			que[++tl]=i, sl[tl]=n-cnt+1;
		// cout<<"cut4"<<endl;
		// cout<<"---------"<<endl;
	}
	return dp[n];
}
void procedure(){
	n=read(),k=read();cnt=0;
	for(int i=1;i<=n;i++)cnt+=((a[i]=read())>=0);
	sort(a+1,a+n+1);
	
	for(int i=1;i<=n;i++)qz[i]=qz[i-1]+a[i];
	// cout<<"testcase"<<endl;

	LL sum=0;
	if(k>cnt){
		for(int i=1;i<=n-k+1;i++)sum+=a[i];
		sum*=(n-k+1);
		for(int i=n-k+2;i<=n;i++)sum+=a[i];
		print(sum);
	}else{
		// check(-5);
		LL l=-1e20,r=1e20; 
		while(l+1<r){
			// cout<<(ll)l<<"->"<<(ll)r<<endl;
			LL mid=(l+r)>>1;
			if(check(mid).se>k) l=mid;
			else r=mid;
		}
		// cout<<"l="<<(ll)l<<" r="<<(ll)r<<endl;
		LL a1=check(l).fi,a2=check(r).fi;
		// int b1=check(l).se,b2=check(r).se;

		// cout<<b1<<","<<b2<<endl;

		// cout<<"a1="<<(ll)a1<<" a2="<<(ll)a2<<endl;
		print(max(a1-k*l, a2-k*r));
	}
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