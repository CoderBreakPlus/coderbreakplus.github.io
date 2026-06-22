// created time: 2026-06-22 18:39:48
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

int n,m,a[200005],c;
map<int,int>mp;

set<int>pos[200005];

void procedure(){
	mp.clear();
	n=read();
	for(int i=1;i<=c;i++)pos[i].clear();
	c=0;

	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!mp.count(a[i]))mp[a[i]]=++c;
		pos[a[i]=mp[a[i]]].emplace(i);
	}

	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;

	vector<int>sb;
	for(int i=1;i<=c;i++){
		bool f=0;
		vector<int>ok;
		for(auto x: pos[i])ok.pb(x);
		for(int j=1;j<ok.size();j++){
			if(ok[j]-1!=ok[j-1]){
				f=1;
				break;
			}
		}
		if(f)sb.pb(i);
	}
	if(sb.size()==0){
		puts("YES");
		return;
	}
	int X=0;

	vector<int>mY;
	if(sb.size()==1){
		int x=sb[0];
		vector<int>ok;
		for(auto w: pos[x])ok.pb(w);

		X=x;

		set<int>S;
		for(int i=ok[0]-1;i<=ok.back()+1;i++){
			if(i<1||i>n)continue;
			if(a[i]==x)continue;
			S.emplace(a[i]);
			if(S.size()>=10)break;
		}

		for(int i=ok.back()+1;i>=ok[0]-1;i--){
			if(i<1||i>n)continue;
			if(a[i]==x)continue;
			S.emplace(a[i]);
			if(S.size()>=20)break;
		}
		for(auto x: S) mY.pb(x);
	}
	if(sb.size()>=3){
		puts("NO");
		return;
	}
	int x,y;
	if(sb.size()==2)
		x=sb[0],mY={sb[1]};
	else
		x=X;

	for(auto y:mY){
		set<int>t1 = pos[x], t2 = pos[y];
		// cout<<x<<","<<y<<endl;
		{
			int ed=*prev(pos[x].end());
			int pr=*pos[y].begin();

			pos[x].erase(ed),pos[y].emplace(ed);
			pos[y].erase(pr),pos[x].emplace(pr);


			// for(auto w:pos[x])cout<<w<<" "; cout<<endl;
			// for(auto w:pos[y])cout<<w<<" "; cout<<endl;
			// cout<<endl;

			if(*prev(pos[x].end()) - *pos[x].begin() + 1 == pos[x].size()
			&& *prev(pos[y].end()) - *pos[y].begin() + 1 == pos[y].size()){
				puts("YES");
				return;
			}
		}
		pos[x]=t1, pos[y]=t2;
		swap(x,y);
		{
			int ed=*prev(pos[x].end());
			int pr=*pos[y].begin();

			pos[x].erase(ed),pos[y].emplace(ed);
			pos[y].erase(pr),pos[x].emplace(pr);

			// for(auto w:pos[x])cout<<w<<" "; cout<<endl;
			// for(auto w:pos[y])cout<<w<<" "; cout<<endl;
			// cout<<endl;

			if(*prev(pos[x].end()) - *pos[x].begin() + 1 == pos[x].size()
			&& *prev(pos[y].end()) - *pos[y].begin() + 1 == pos[y].size()){
				puts("YES");
				return;
			}
		}
		swap(x,y);
		pos[x]=t1, pos[y]=t2;
	}
	puts("NO");
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