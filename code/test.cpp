// created time: 2026-07-06 08:33:34
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
mt19937_64 rnd(1233);
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

const int n = 10;
bool vis[n+5];
int test(vector<int> tmp, bool safety=1){
	int fuck=0;
	for(int i=0;i<n;i++)cout<<tmp[i]<<" ";cout<<endl;
	for(int i=0;i<n;i++){
		fuck+=(tmp[i]==i+1);
		if(vis[i]&&safety){
			assert(tmp[i]==i+1);
		}
	}
	// cout<<fuck<<endl;
	return fuck;
}
void procedure(){
	memset(vis,0,sizeof(vis));
	vector<int>res;
	for(int i=1;i<=n;i++)res.pb(i);
	shuffle(res.begin(),res.end(),rnd);
	
	int x=test(res);

	int cnt=0;
	while(x!=n){
		cnt++;
		if(cnt>5e5) exit(0);
		vector<int>tmp;
		int pt=-1;
		for(int i=0;i<n;i++)
			if(!vis[i])tmp.pb(i);
			else pt=i;

		cout<<"tmp="<<tmp.size()<<endl;
		int i=rnd()%tmp.size(),j=rnd()%tmp.size();
		while(i==j){
			j=rnd()%tmp.size();
		}
		i=tmp[i],j=tmp[j];

		swap(res[i],res[j]);
		int y=test(res);
		if(y>x){
			if(y==x+2){
				cout<<"lock1 "<<i<<" "<<j<<endl;
				vis[i]=vis[j]=1;
				assert(res[i]==i+1);
				assert(res[j]==j+1);
			}
			else if(y==x+1){
				if(~pt){
					cout<<"trying "<<i<<" "<<j<<endl;
					vector<int>res2=res;
					swap(res2[i],res2[pt]);
					int z=test(res2,0);
					if(z+1<y) vis[i]=1,cout<<"lock3 "<<i<<endl;
					else vis[j]=1,cout<<"lock3 "<<j<<endl;
				}
				// else{
				// 	pt=rnd()%n;
				// 	while(pt==i||pt==j)pt=rnd()%n;

				// 	vector<int>res2=res;
				// 	swap(res2[i],res2[pt]);
					
				// 	int z=test(res2);
				// 	if(z<y) vis[i]=1;
				// }
			}
			x=y;
		}else{
			swap(res[i],res[j]);
			if(y==x-2){
				cout<<"lock2 "<<i<<" "<<j<<endl;
				vis[i]=vis[j]=1;
				assert(res[i]==i+1);
				assert(res[j]==j+1);
				// for(int i=0;i<n;i++)cout<<res[i]<<" ";cout<<endl;
			}
		}
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