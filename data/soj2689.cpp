// created time: 2026-11-16 10:13:30
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
namespace atcoder{
	long long floor_sum(long long n, long long m, long long a, long long b) {
	    long long ans = 0;
	    if (a >= m) {
	        ans += (n - 1) * n * (a / m) / 2;
	        a %= m;
	    }
	    if (b >= m) {
	        ans += n * (b / m);
	        b %= m;
	    }

	    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
	    if (y_max == 0) return ans;
	    ans += (n - (x_max + a - 1) / a) * y_max;
	    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
	    return ans;
	}
}
int n,m,q;
char s[100005];
int sa[100005],rk[100005],x[100005],y[100005],buc[100005];
int ht[100005];

void getsa(){
	m=127;
	memset(buc,0,sizeof(buc));
	for(int i=1;i<=n;i++)buc[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
	for(int i=n;i>=1;i--)sa[buc[x[i]]--]=i;

	for(int p=1;p<n;p<<=1){
		int w=0;
		for(int i=n-p+1;i<=n;i++) y[++w]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>p) y[++w]=sa[i]-p;
		memset(buc,0,sizeof(buc));
		for(int i=1;i<=n;i++)buc[x[i]]++;
		for(int i=1;i<=m;i++)buc[i]+=buc[i-1];

		for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];
		swap(x,y);
		x[sa[1]]=m=1;
		for(int i=2;i<=n;i++){
			if(max(sa[i],sa[i-1])+p<=n&&y[sa[i]]==y[sa[i-1]]&&y[sa[i]+p]==y[sa[i-1]+p])
				x[sa[i]]=m;
			else
				x[sa[i]]=++m;
		}
	}
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1){
			ht[1]=k=0;
			continue;
		}
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k])k++;
		ht[rk[i]]=k;
	}
}

int st[17][100005];
inline int lcp(int a,int b){
	if(a==b)return n-a+1;
	int l=rk[a],r=rk[b];
	if(l>r)swap(l,r);
	int k=lg2(r-l++);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
namespace Border{
	int B,id[100005];
	vector<tuple<int,int,int>> v[100005];

	void init(){
		B=max(2,(int)sqrt(n));
		for(int i=1;i<=n;i++)st[0][i]=ht[i];
		for(int k=1;k<=lg2(n);k++)
			for(int i=1;i+(1<<k)-1<=n;i++)
				st[k][i]=min(st[k-1][i],st[k-1][i+(1<<(k-1))]);

		int c=0;
		for(int i=1;i<=n;i++){
			v[i].clear();
			if(i==1||ht[i]<B)c++;
			if(sa[i]+B-1<=n)id[sa[i]]=c;
		}
		for(int i=1;i+B-1<=n;i++){
			auto &a=v[id[i]];
			if(a.empty()||i-get<1>(a.back())>B/2)
				a.pb(i,i,0);
			else{
				auto &[l,r,d]=a.back();
				d=i-r;
				r=i;
			}
		}
	}
	inline void append(vector<tuple<int,int,int>> &ans,int a,int d,int c){
		if(c<=0)return;
		if(c==1)d=0;
		if(!ans.empty()){
			auto &[pa,pd,pc]=ans.back();
			int gap=a-pa-pd*(pc-1);
			if(pc==1&&(c==1||gap==d)){
				pd=gap;
				pc+=c;
				return;
			}
			if(pc>1&&gap==pd&&(c==1||d==pd)){
				pc+=c;
				return;
			}
		}
		ans.pb(a,d,c);
	}
	vector<tuple<int,int,int>> query(int l,int r){
		vector<tuple<int,int,int>> ans;
		for(int k=1;k<B&&k<r-l+1;k++)
			if(lcp(l,r-k+1)>=k)
				append(ans,k,0,1);

		if(r-l+1<=B)return ans;

		auto &a=v[id[l]];
		for(int i=(int)a.size()-1;i>=0;i--){
			auto [x,y,d]=a[i];
			if(y<=l)break;
			if(x>r-B+1)continue;

			if(!d){
				if(lcp(l,x)>=r-x+1)
					append(ans,r-x+1,0,1);
				continue;
			}

			int L=max(x,l+1),R=min(y,r-B+1);
			int len=d+lcp(l,l+d);
			int ed=x+d+lcp(x,x+d)-1;

			if(r<=ed){
				L=max(L,r-len+1);
			}else{
				int j=ed-len+1;
				L=max(L,j);
				R=min(R,j);
			}

			L=x+(L-x+d-1)/d*d;
			if(L>R)continue;
			R=x+(R-x)/d*d;

			if(lcp(l,L)>=r-L+1)
				append(ans,r-R+1,d,(R-L)/d+1);
		}
		return ans;
	}
}
void procedure(){
	n=read(),q=read();
	scanf("%s",s+1);
	getsa();
	Border::init();
	int lst=0;
	while(q--){
		int l=read()^lst,r=read()^lst;
		vector<tuple<int,int,int>>res=Border::query(l,r);
		lst=0;
		for(auto [a,b,c]:res){
			if(c==1){ lst^=a; continue; }
			for(int i=0;i<=16;i++)
				lst^=(atcoder::floor_sum(c,1<<i,b,a)&1)<<i;
		}
		printf("%d\n",lst);
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