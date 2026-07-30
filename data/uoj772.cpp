// created time: 2026-07-30 19:02:12
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

const int N=2e6+5;
int n,m;
char s[N];

int fl[N],tr[N][26],id[N],cnt[N],idx;

int que[N],jp[N];
void getfail(){
	int hd=1,tl=0;
	for(int i=0;i<26;i++)
		if(tr[0][i])que[++tl]=tr[0][i];
	while(hd<=tl){
		int x=que[hd++];
		for(int i=0;i<26;i++)
			if(!tr[x][i]) tr[x][i]=tr[fl[x]][i];
			else fl[tr[x][i]]=tr[fl[x]][i],que[++tl]=tr[x][i];
		jp[x]=id[fl[x]]?fl[x]:jp[fl[x]];
	}
}
bool vis[N];
int stk[N],tp,seq[N],tl;

namespace pw{
	const int N = (1<<18);
	uint p0[N+5],p1[N+5];
	void init(){
		p0[0]=1;
		for(int i=1;i<=N;i++)p0[i]=p0[i-1]*3;
		p1[0]=1;
		for(int i=1;i<=N;i++)p1[i]=p1[i-1]*p0[N];
	}
	uint query(ull x){
		return p1[x>>18]*p0[x&(N-1)];
	}
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		int p=0,len=strlen(s);
		for(int x=0;x<len;x++){
			if(!tr[p][s[x]-'a']) tr[p][s[x]-'a']=++idx;
			p=tr[p][s[x]-'a'];
		}
		id[p]=i; 
	}
	getfail();
	while(m--){
		scanf("%s",s); int len=strlen(s);
		int p=0;
		tp=tl=0;
		for(int x=0;x<len;x++){
			p=tr[p][s[x]-'a'],cnt[p]++;
			tp=0; int cur=p;
			while(!vis[cur]){
				vis[cur]=1, stk[++tp]=cur;
				cur=jp[cur];
			}
			while(tp) seq[++tl]=stk[tp--];
		}
		uint ans=n;
		for(int i=tl;i>=1;i--){
			cnt[jp[seq[i]]]+=cnt[seq[i]];
			ans+=pw::query((ull)id[seq[i]]*cnt[seq[i]])-1;
			vis[seq[i]]=cnt[seq[i]]=0;
		}
		printf("%u\n",ans);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	pw::init();
	read();
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}