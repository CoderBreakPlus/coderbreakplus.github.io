// created time: 2026-11-23 19:20:22
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

int n;
char s[1005][1005];
vector<int>lk;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}	
	if(s[1][2]=='1')lk={1,2};
	else lk={2,1};
	for(int i=3;i<=n;i++){
		if(s[i][lk[0]]=='1'){
			lk.insert(lk.begin(),i);
			continue;
		}
		bool ok=0;
		for(int j=0;j+1<lk.size();j++){
			if(s[lk[j]][i]=='1'&&s[i][lk[j+1]]=='1'){
				lk.insert(lk.begin()+j+1,i);
				ok=1;break;
			}
		}
		if(!ok)lk.emplace_back(i);
	}
	int pt=1;
	while(s[lk[0]][lk[pt]]=='1')pt++;
	vector<int>cir(lk.begin(),lk.begin()+pt+1);
	for(int i=pt+1;i<n;){
		vector<int>now;
		int ok=0;
		while(!ok){
			int x=lk[i++];
			now.emplace_back(x);
			for(int j=0;j+1<cir.size();j++){
				if(s[cir[j]][now[0]]=='1'&&s[x][cir[j+1]]=='1'){
					cir.insert(cir.begin()+j+1,now.begin(),now.end());
					ok=1;break;
				}
			}
			if(!ok&&s[cir.back()][now[0]]=='1'&&s[x][cir[0]]=='1'){
				cir.insert(cir.end(),now.begin(),now.end());
				ok=1;
			}
		}
	}
	for(int x:cir) printf("%d ",x);
	puts("");
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