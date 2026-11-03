// created time: 2026-10-30 07:04:40
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

int n,a[100005];
bool pay(int a,int b,int v){
	return (a>=v)||(v>=2&&a>=v-2&&b>=1)||(v==4&&b>=2);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();

	int sum=0,cnt=0,cnt5=0,db=0;
	priority_queue<pair<int,int>>q;
	for(int i=1;i<=n;i++){
		a[i]=(a[i]==10?1:(a[i]==20?-1:-4));
		if(pay(sum,db,-a[i])){
			if(a[i]==-1) sum--,db++;
			else if(a[i]==-4){
				int a=0,b=0;
				if(db) db--,b++; else sum-=2,a+=2;
				if(db) db--,b++; else sum-=2,a+=2;
				q.push({a,b});
				cnt5++;
			}else sum++;
			cnt++;
		}else if(a[i]==-1){
			if(cnt5&&q.top().fi){
				cnt5--,db++;
				auto [x,y]=q.top();q.pop();
				sum+=x-1,db+=y;
			}
		}
		// else if(a[i]==-4&&cnt5){
		// 	auto [x,y]=q.top();q.pop();
		// 	sum+=x,db+=y;

		// 	int a=0,b=0;
		// 	if(db) db--,b++; else sum-=2,a+=2;
		// 	if(db) db--,b++; else sum-=2,a+=2;
		// 	q.push({a,b});
		// }
		// cout<<"qz "<<i<<" sum="<<sum<<" db="<<db<<" cnt="<<cnt<<" cnt5="<<cnt5<<endl;
	}
	printf("%d\n",cnt);
}
int main(){
	// #ifdef LOCAL
		assert(freopen("change.in","r",stdin));
		assert(freopen("change.out","w",stdout));
	// #endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}