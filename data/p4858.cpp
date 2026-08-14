// created time: 2026-08-13 18:56:08
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
const int N = 2505;
int n,m;
char s[N][N];

int L[N][N],R[N][N],U[N][N],D[N][N],cnt;

int a[N],b[N],c[N],d[N],lst[N];
struct Deque{
	int q[N],hd,tl;
	Deque(){ hd=1,tl=0; }
	int front(){ return q[hd]; }
	int back(){ return q[tl]; }
	bool empty(){ return hd>tl; }
	void pop_back(){ tl--; }
	void push_back(int x){ q[++tl]=x; }
	void pop_front(){ hd++; }
	void clr(){ hd=1,tl=0; }
}A,B;
bool check(int R,int C){
	int ok=0;
	if(n/R*m<=m/C*n){
		for(int i=1;i<=m;i++) lst[i]=0;
		for(int i=R;i<=n;i+=R){
			for(int j=1;j<=m;j++) a[j]=U[i][j],b[j]=D[i][j],c[j]=d[j]=0;

			A.clr(),B.clr();

			for(int j=1;j<=m;j++){
				while(!A.empty()&&a[A.back()]>=a[j]) A.pop_back(); A.push_back(j);
				while(!A.empty()&&A.front()+C<=j) A.pop_front();
				while(!B.empty()&&b[B.back()]>=b[j]) B.pop_back(); B.push_back(j);
				while(!B.empty()&&B.front()+C<=j) B.pop_front();

				if(j>=C && a[A.front()]+b[B.front()]-1>=R){
					c[j-C+1]=a[A.front()],d[j-C+1]=b[B.front()];
				}
			}

			A.clr(),B.clr();

			for(int j=1;j<=m;j++){
				while(!A.empty()&&c[A.back()]<=c[j]) A.pop_back(); A.push_back(j);
				while(!A.empty()&&A.front()+C<=j) A.pop_front();
				while(!B.empty()&&d[B.back()]<=d[j]) B.pop_back(); B.push_back(j);
				while(!B.empty()&&B.front()+C<=j) B.pop_front();
				if(c[A.front()]&&d[B.front()]){
					int L=i-c[A.front()]+1,R=i+d[B.front()]-1;
					ok+=R-max(L-1,lst[j]);
					lst[j]=R;
				}
			}
		}
		return ok==cnt;
	}else{
		for(int i=1;i<=n;i++) lst[i]=0;
		for(int i=C;i<=m;i+=C){
			for(int j=1;j<=n;j++) a[j]=L[j][i],b[j]=::R[j][i],c[j]=d[j]=0;

			A.clr(),B.clr();

			for(int j=1;j<=n;j++){
				while(!A.empty()&&a[A.back()]>=a[j]) A.pop_back(); A.push_back(j);
				while(!A.empty()&&A.front()+R<=j) A.pop_front();
				while(!B.empty()&&b[B.back()]>=b[j]) B.pop_back(); B.push_back(j);
				while(!B.empty()&&B.front()+R<=j) B.pop_front();

				if(j>=R && a[A.front()]+b[B.front()]-1>=C)
					c[j-R+1]=a[A.front()],d[j-R+1]=b[B.front()];
			}

			A.clr(),B.clr();
			
			for(int j=1;j<=n;j++){
				while(!A.empty()&&c[A.back()]<=c[j]) A.pop_back(); A.push_back(j);
				while(!A.empty()&&A.front()+R<=j) A.pop_front();
				while(!B.empty()&&d[B.back()]<=d[j]) B.pop_back(); B.push_back(j);
				while(!B.empty()&&B.front()+R<=j) B.pop_front();

				if(c[A.front()]&&d[B.front()]){
					int L=i-c[A.front()]+1,R=i+d[B.front()]-1;
					ok+=R-max(L-1,lst[j]);
					lst[j]=R;
				}
			}
		}
		return ok==cnt;
	}
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)
			cnt+=(s[i][j]=='X');
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)if(s[i][j]=='X'){
			L[i][j]=L[i][j-1]+1;
			U[i][j]=U[i-1][j]+1;
		}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)if(s[i][j]=='X'){
			R[i][j]=R[i][j+1]+1;
			D[i][j]=D[i+1][j]+1;
		}
	int c=m,ans=0,x=0,y=0;
	for(int r=1;r<=n;r++){
		if(r*c<=ans) continue;
		bool sb=0;
		while(c&&!check(r,c)){
			c--;
			if(r*c<=ans){
				sb=1;
				break;
			}
		}
		if(!sb&&r*c>ans){
			ans=r*c;
			x=r,y=c;
		}
	}
	printf("%d %d\n",x,y);
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