// created time: 2026-10-13 15:11:13
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

int n,m=1,w;
int id(char ch){ return ch=='L'?0:(ch=='R'?1:2); }

int seq[200005][20],pt[20][3],hsh[200005];
int buc[10000005],val[20];

void procedure(){
	n=read();
	m=1,w=0;
	while(m<n)m*=3,w++;

	for(int i=0;i<n;i++){
		int val=i,sum=0;
		for(int j=0;j<w;j++){
			seq[i][j]=(val+(w%3==2&&j==0?0:i))%3,val/=3;
			sum+=seq[i][j];
		}
		seq[i][w]=(3-sum%3)%3;
		hsh[i]=0;
		for(int j=w;j>=0;j--)hsh[i]=hsh[i]*3+seq[i][j];
		buc[hsh[i]]=i+1;
	}
	printf("%d\n",w+1);
	for(int i=0;i<=w;i++){
		vector<int>c[3];
		for(int x=0;x<n;x++)
			c[seq[x][i]].pb(x+1);
		// cout<<c[0].size()<<" "<<c[1].size()<<" "<<c[2].size()<<endl;
		if(c[0].size()==c[1].size()){
			// cout<<"type1"<<endl;
			printf("%d ",(int)2*c[0].size());
			for(int x:c[0]) printf("%d ",x);
			for(int x:c[1]) printf("%d ",x);
			pt[i][0]=0,pt[i][1]=1,pt[i][2]=2;
		}else if(c[0].size()==c[2].size()){
			// cout<<"type2"<<endl;
			printf("%d ",(int)2*c[0].size());
			for(int x:c[0]) printf("%d ",x);
			for(int x:c[2]) printf("%d ",x);
			pt[i][0]=0,pt[i][1]=2,pt[i][2]=1;
		}else{
			// cout<<"type3"<<endl;
			printf("%d ",(int)2*c[1].size());
			for(int x:c[1]) printf("%d ",x);
			for(int x:c[2]) printf("%d ",x);
			pt[i][0]=1,pt[i][1]=2,pt[i][2]=0;
		}
		puts("");
	}
	fflush(stdout);
	char s[25];
	if(scanf("%s",s)==EOF) exit(0);

	int pos=-1,sum=0,cur=0;
	for(int i=0;i<=w;i++){
		if(s[i]=='?')pos=i;
		else sum+=(val[i]=pt[i][id(s[i])]);
	}
	assert(~pos);
	val[pos]=(3-sum%3)%3;

	for(int i=w;i>=0;i--)
		cur=cur*3+val[i];
	printf("%d\n",buc[cur]);
	fflush(stdout);
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