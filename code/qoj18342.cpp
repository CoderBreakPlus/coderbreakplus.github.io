// created time: 2026-07-07 14:56:25
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

int n,a[200005];
int pos[200005],len[200005],c[200005],m;
int f0[20][200005],f1[20][200005];
char s[200005];

int query0(int l,int r){
	int p=lg2(r-l+1);
	return max(f0[p][l], f0[p][r-(1<<p)+1]);
}
int query1(int l,int r){
	int p=lg2(r-l+1);
	return max(f1[p][l], f1[p][r-(1<<p)+1]);
}
int col[200005];

int buc0[200005],buc1[200005],seq0[200005],seq1[200005],c0,c1;
vector<int>vec0[200005],vec1[200005];

vector<pair<int,int>>ok[705][705];

bool check(int i,int j,int v0,int v1){
	return query0(i,j)==v0 && query1(i,j)==v1;
}
void procedure(){
	n=read(),q=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]!=s[i-1]){
			pos[++m]=i, c[i]=(s[i]-='0');
			int ok=i;while(ok<n&&s[ok+1]==s[ok])ok++;
			len[m]=ok-i+1;
			for(int x=i;x<=ok;x++)col[x]=m;
		}
	}
	pos[m+1]=n+1;
	for(int i=1;i<=m;i++){
		int l=len[i];
		if(c[i]){
			f1[0][i]=l;
			if(!buc1[l]) seq1[buc1[l]=++c1]=l;
			vec1[buc1[l]].pb(i);
		}else{
			f0[0][i]=l;
			if(!buc0[l]) seq0[buc0[l]=++c0]=l;
			vec0[buc0[l]].pb(i);
		}
	}
	for(int i=1;(1<<i)<=m;i++)
		for(int j=1;j<=m-(1<<i)+1;j++){
			f0[i][j]=max(f0[i-1][j],f0[i-1][j+(1<<i-1)]);
			f1[i][j]=max(f1[i-1][j],f1[i-1][j+(1<<i-1)]);
		}
	for(int i=1;i<=c0;i++)
		for(int j=1;j<=c1;j++){
			vector<int>all(vec0[i].size()+vec1[j].size());
			merge(vec0[i].begin(),vec0[i].end(),
				vec1[i].begin(),vec1[i].end(),all.begin());

			ok[i][j].resize(all);
			int s0=-1, s1=-1;
			for(int x=all.size()-1;x>=0;x--){
				ok[i][j][x]=(x+1<all.size()?ok[i][j][x+1]:m+1);
				if(c[x]){
					if(~s0 && check(all[x],s0,len[s0],len[all[x]]))
						chkmin(ok[i][j][x],s0);
					s1=c[x];
				}else{
					if(~s1 && check(all[x],s1,len[all[x]],len[s1]))
						chkmin(ok[i][j][x],s1);
					s0=c[x];
				}
			}
		}

	while(q--){
		
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