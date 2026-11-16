// created time: 2026-11-16 07:44:16
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

int n,m,q,l[50005],r[50005],k[50005];
char s[50005];

int sa[50005],rk[50005],x[50005],y[50005],buc[50005];
int ht[50005];

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

int st[16][50005];
inline int lcp(int a,int b){
	if(a==b)return n-a+1;
	int l=rk[a],r=rk[b];
	if(l>r)swap(l,r);
	int k=lg2(r-l++);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
namespace Border{
	int B,id[50005];
	vector<tuple<int,int,int>> v[50005];

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

			if(d){
				if(x<l+1)x+=(l+1-x+d-1)/d*d;
				if(y>r-B+1)y-=(y-(r-B+1)+d-1)/d*d;
			}
			if(x>y)continue;

			if(x==y){
				if(lcp(l,x)>=r-x+1)
					append(ans,r-x+1,0,1);
				continue;
			}

			int len=d+lcp(l,l+d);
			int ed=x+d+lcp(x,x+d)-1;
			if(r<=ed){
				int need=r-len+1;
				if(x<need)x+=(need-x+d-1)/d*d;
				if(x<=y)
					append(ans,r-y+1,d,(y-x)/d+1);
			}else{
				int j=ed-len+1;
				if(x<=j&&j<=y&&(j-x)%d==0&&lcp(l,j)>=r-j+1)
					append(ans,r-j+1,0,1);
			}
		}
		return ans;
	}
}

char t[50005];
int c,f[50005];

vector<pair<int,int>>qr[50005];
int ans[50005];

struct BIT{
	int c[50005];
	void upd(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}b;

const int B = 224;
vector<pair<int,int>>q2[B][50005];

void procedure(){
	n=read(),q=read();
	for(int i=0;i<=n;i++)qr[i].clear();
	memset(b.c,0,sizeof(b.c));

	for(int i=1;i<=min(B-1,n);i++)
		for(int j=1;j<=n;j++)q2[i][j].clear();

	scanf("%s",s+1);
	getsa();
	Border::init();
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),k=read();
		int pos=rk[k],len=r-k+1,L=pos;
		while(ht[L]>=len)L--;

		ans[i]=1;
		qr[l-1].pb(L-1,-i);
		qr[k-1].pb(L-1,i);
		qr[k].pb(pos-1,-i);
		qr[r].pb(pos-1,i);

		vector<tuple<int,int,int>>tmp=Border::query(k,r);
		for(auto [a,d,c]: tmp){
			if(!d)d=1;
			if(d>=B){
				for(int j=0;j<c;j++)
					ans[i]+=(rk[r+1-a-d*j]>pos);
			}else{
				int L=r+1-a-d*c,R=r+1-a;
				if(L>0)q2[d][L].pb(pos,-i);
				q2[d][R].pb(pos,i);
			}
		}
	}
	for(int i=1;i<=min(B-1,n);i++){
		for(int x=1;x<=i;x++){
			int cnt=0;
			for(int y=x;y<=n;y+=i){
				b.upd(rk[y],1),cnt++;
				for(auto [a,id]:q2[i][y]){
					if(id<0)ans[-id]-=(cnt-b.qry(a));
					else ans[id]+=(cnt-b.qry(a));
				}
			}
			for(int y=x;y<=n;y+=i)
				b.upd(rk[y],-1);
		}
	}
	for(int i=1;i<=n;i++){
		b.upd(rk[i],1);
		for(auto [x,y]:qr[i]){
			if(y<0)ans[-y]-=b.qry(x);
			else ans[y]+=b.qry(x);
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]);
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