// created time: 2026-09-01 06:58:41
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

int n,m;
struct Mat{
	int a[3][3];
	Mat(){ memset(a,0xc0,sizeof(a)); }
	int* operator[](int x){ return a[x]; }
	const int* operator[](int x)const{ return a[x]; }

	Mat T(){
		Mat tmp;
		for(int i:{0,1,2})for(int j:{0,1,2})
			tmp[j][i]=a[i][j];
		return tmp;
	}
	void print(){
		for(int i:{0,1,2}){
			for(int j:{0,1,2}) cout<<(a[i][j]<0?-1:a[i][j])<<" ";
			cout<<endl;
		}
	}
}e[35][35],one;
bool has[35][35];

Mat operator* (const Mat &A, const Mat &B){
	Mat C;
	for(int i:{0,1,2})for(int j:{0,1,2})
		for(int k=0;k<=2-j;k++)for(int l:{0,1,2})
			chkmax(C[i][l],A[i][j]+B[k][l]);
	return C;
}
Mat operator+ (const Mat &A, const Mat& B){
	Mat C;
	for(int i:{0,1,2})for(int j:{0,1,2})
		for(int k=0;k<=2-i;k++)for(int l=0;l<=2-j;l++)
			chkmax(C[i+k][j+l],A[i][j]+B[k][l]);
	return C;
}
int ind[35];
void add_edge(int x,int y,Mat z){
	if(has[x][y]){
		e[x][y]=e[x][y]+z;
	}else{
		ind[x]++,ind[y]++;
		e[x][y]=z;
		has[x][y]=has[y][x]=1;
	}
	e[y][x]=e[x][y].T();
	// cout<<"here "<<x<<"->"<<y<<endl;
	// e[x][y].print();
}
void del_edge(int x,int y){
	ind[x]--,ind[y]--;
	e[x][y]=e[y][x]=Mat();
	has[x][y]=has[y][x]=0;
}
void procedure(){
	n=read(),m=read();
	memset(has,0,sizeof(has));
	memset(ind,0,sizeof(ind));

	while(m--){
		int x=read(),y=read();
		add_edge(x,y,one);
	}
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(ind[i]<=2) q.push(i);

	while(!q.empty()){
		int x=q.front();q.pop();
		// cout<<"x="<<x<<endl;
		if(!ind[x])continue;
		if(ind[x]==1){
			int y=-1,z=-1;
			for(int i=1;i<=n;i++)if(has[x][i])y=i;
			assert(~y);

			for(int i=1;i<=n;i++)if(has[y][i]&&i!=x)z=i;
			if(!~z) continue;

			// cout<<"finding1 "<<x<<"->"<<y<<"->"<<z<<endl;

			// cout<<"A:"<<endl;
			// e[y][z].print();
			// cout<<"B:"<<endl;
			// e[y][x].print();
			
			Mat C;
			for(int i:{0,1,2})for(int j:{0,1,2})
				for(int k=0;k<=i;k++)for(int l:{0,1,2})
					chkmax(C[i][j],e[y][z][k][j]+e[y][x][i-k][l]);

			e[y][z]=C;
			
			// cout<<"result:"<<endl;
			// e[y][z].print();
			
			e[z][y]=C.T();


			del_edge(x,y);
			if(ind[y]<=2) q.push(y);//, cout<<"insert "<<y<<endl;
		}else{
			int y=-1,z=-1;
			for(int i=1;i<=n;i++)if(has[x][i]){
				if(~y) z=i; else y=i;
			}
			assert(~y && ~z);
			// cout<<"finding2 "<<y<<"->"<<x<<"->"<<z<<endl;
			Mat C=e[y][x]*e[x][z];

			del_edge(y,x),del_edge(x,z);
			add_edge(y,z,C);

			if(ind[y]<=2) q.push(y);//, cout<<"insert "<<y<<endl;
			if(ind[z]<=2) q.push(z);//, cout<<"insert "<<z<<endl;
		}
	}
	int ans=0;

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)if(has[i][j]){

			// cout<<"res edge "<<i<<","<<j<<endl;
			for(int p:{0,1,2})for(int q:{0,1,2}){
				chkmax(ans, e[i][j][p][q]);
				// cout<<e[i][j][p][q]<<" ";
			}
			// cout<<endl;
		}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	one.a[0][0]=0,one.a[1][1]=1;
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}