// created time: 2026-09-22 08:59:34
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

int n,m,M,T,F;
char s[1005][1005];

int code(int x,int y){ return (x-1)*m+y; }
int fa[4000005];

int find(int x){ if(x!=fa[x]) fa[x]=find(fa[x]); return fa[x]; }
void merge(int x,int y){
	x=find(x),y=find(y);if(x==y)return;
	fa[x]=y;
}

void make1(int i){
	if(~i){
		// cout<<"make1 "<<i<<endl;
		merge(i+M,T);
		merge(i,F);
		// assert(find(T)!=find(F));
	}
}
void make0(int i){
	if(~i){
		// cout<<"make0 "<<i<<endl;
		merge(i+M,F);
		merge(i,T);
		// assert(find(T)!=find(F));
	}
}

void choose(int i,int j){
	if(i==-1) {make1(j);return;}
	if(j==-1) {make1(i);return;}
	// cout<<"choose "<<i<<","<<j<<endl;
	merge(i,j+M),merge(i+M,j);
	// assert(find(T)!=find(F));
}
void same(int i,int j){
	if(i==-1) {make0(j);return;}
	if(j==-1) {make0(i);return;}
	// cout<<"same "<<i<<","<<j<<endl;
	merge(i,j),merge(i+M,j+M);
	// assert(find(T)!=find(F));
}

int up(int i,int j){ return i>1?(code(i-1,j)<<1|1):-1; }
int down(int i,int j){ return i<n?(code(i,j)<<1|1):-1; }

int left(int i,int j){ return j>1?(code(i,j-1)<<1):-1; }
int right(int i,int j){ return j<m?(code(i,j)<<1):-1; }

void procedure(){
	n=read(),m=read();
	M=2*n*m,T=2*M+1,F=2*M+2;
	for(int i=1;i<=2*M+2;i++)fa[i]=i;

	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);

	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<m;j++){
	// 		cout<<right(i,j)<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// for(int i=1;i<n;i++){
	// 	for(int j=1;j<=m;j++){
	// 		cout<<down(i,j)<<" ";
	// 	}
	// 	cout<<endl;
	// }
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int L=left(i,j);
			int R=right(i,j);
			int U=up(i,j);
			int D=down(i,j);
			// cout<<"at "<<i<<","<<j<<endl;
			if(s[i][j]=='0'){
				make0(U),make0(D);
				make0(L),make0(R);
			}
			if(s[i][j]=='1'){
				same(U,D);
				same(L,R);
				choose(U,L);
			}
			if(s[i][j]=='2'){
				choose(U,D);
				choose(L,R);
			}
			if(s[i][j]=='3'){
				choose(U,R);
				make0(L),make0(D);
			}
			if(s[i][j]=='4'){
				choose(U,D);
				make0(L),make0(R);
			}
			if(s[i][j]=='5'){
				choose(U,L);
				make0(D),make0(R);
			}
			if(s[i][j]=='6'){
				choose(R,D);
				make0(U),make0(L);
			}
			if(s[i][j]=='7'){
				choose(R,L);
				make0(U),make0(D);
			}
			if(s[i][j]=='8'){
				choose(D,L);
				make0(R),make0(U);
			}
			if(s[i][j]=='9'){
				make1(L),make1(R),make1(U),make1(D);
			}
			if(s[i][j]=='A'){
				make1(L),make1(R);
				choose(U,D);
			}
			if(s[i][j]=='B'){
				make1(U),make1(D);
				choose(L,R);
			}
		}
	assert(find(T)!=find(F));
	for(int i=1;i<=M;i++){
		if(find(i)!=find(T)&&find(i)!=find(F))
			merge(i,T),merge(i+M,F);
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]!='0') putchar('o');
			else putchar('.');
			if(j<m) putchar(find(right(i,j)+M)==find(T)?'-':'.');
		}
		puts("");
		if(i==n)break;
		for(int j=1;j<=m;j++){
			putchar(find(down(i,j)+M)==find(T)?'|':'.');
			if(j<m) putchar('.');
		}
		puts("");
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