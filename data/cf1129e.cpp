// created time: 2026-08-27 13:35:30
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

int n,sz[505],ord[505];
vector<pair<int,int>>ans;

int ques(vector<int> A,vector<int> B,int v){
	if(B.empty())return 0;
	cout<<A.size()<<endl;
	for(int x:A)cout<<x<<" "; cout<<endl;
	cout<<B.size()<<endl;
	for(int x:B)cout<<x<<" "; cout<<endl;
	cout<<v<<endl;
	int sb;
	if(!(cin>>sb)) exit(0);
	return sb;
}
void procedure(){
	cin>>n; sz[1]=n;

	vector<int>all;
	for(int i=2;i<=n;i++)all.pb(i);
	for(int i=2;i<=n;i++)sz[i]=ques({1},all,i);
	for(int i=1;i<=n;i++)ord[i]=i;
	sort(ord+1,ord+n+1,[&](int x,int y){return sz[x]<sz[y];});

	vector<int>love;
	for(int i=1;i<=n;i++){
		int x=ord[i];
		// cout<<"x="<<x<<endl;
		int lst=ques({1},love,x);

		vector<int>fff;
		while(lst){
			int l=1,r=(int)love.size()-1,ok=0;
			while(l<=r){
				int mid=(l+r)>>1;

				// cout<<"here mid = "<<mid<<endl;
				if(ques({1},vector<int>(love.begin(),love.begin()+mid),x)<lst)
					ok=mid,l=mid+1;
				else r=mid-1;
			}
			// cout<<"link "<<x<<" "<<love[ok]<<endl;
			ans.pb(x,love[ok]);
			while(love.size()>ok+1)fff.pb(love.back()),love.pop_back();
			love.pop_back();
			lst--;
		}
		while(love.size())fff.pb(love.back()),love.pop_back();
		fff.pb(x);
		swap(love,fff);
	}
	cout<<"ANSWER"<<endl;
	for(auto [x,y]: ans)cout<<x<<" "<<y<<endl;
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