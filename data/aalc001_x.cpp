// created time: 2026-10-28 07:39:35
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

int n,q,a[200005],g[200005],d[200005];

struct Info{
	int v,mn,mx;
	Info(){}
	Info(int a,int b,int c){v=a,mn=b,mx=c;}
};
Info operator+ (const Info &A,const Info &B){
	if(A.v==B.v) return Info(A.v,min(A.mn,B.mn),max(A.mx,B.mx));
	else return A.v<B.v?A:B;
}
#define mid ((l+r)>>1)
struct sgt{
	int tag[800005];
	Info t[800005];
	void upd(int p,int v){ t[p].v+=v,tag[p]+=v; }
	void pushup(int p){ t[p]=t[p<<1]+t[p<<1|1]; }
	void pushdown(int p){
		upd(p<<1,tag[p]),upd(p<<1|1,tag[p]);
		tag[p]=0;
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){upd(p,v);return;}
		pushdown(p);
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void build(int l,int r,int p){
		if(l==r){ t[p]=Info(d[l],l,l); return; }
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
}s0,s1;

struct zkw{
	int m,t[800005],op;
	int get(int x,int y){
		if(!x||!y)return x^y;
		if(!op)return a[x]<a[y]?x:y;
		else return a[x]>a[y]?x:y;
	}
	void pushup(int p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void init(){
		m=1;
		while(m<=n+1)m<<=1;
		for(int i=1;i<=n;i++)t[m+i]=i;
		for(int i=m-1;i>=1;i--)pushup(i);
	}
	void upd(int x,int w){
		for(t[x+=m]=w;x>1;) pushup(x>>=1);
	}
	int qry(int l,int r){
		int ret=0;
		for(l+=m-1,r+=m+1;l+1<r;l>>=1,r>>=1){
			if(~l&1) ret=get(ret,t[l^1]);
			if( r&1) ret=get(ret,t[r^1]);
		}
		return ret;
	}
}t0,t1;

int w[200005]; ll ans;
vector<pair<int,int>>vec;

void perm_upd(int x,int v){
	t0.upd(x,0),t1.upd(x,0);
	w[x]+=v,ans+=v*a[x],s0.update(1,n,1,x,v,1),s1.update(1,n,1,x,-v,1);
	if(w[x]>-g[x]) t0.upd(x,x);
	if(w[x]<g[x]) t1.upd(x,x);
}
void temp_upd(int x,int v){ perm_upd(x,v),vec.pb(x,-v); }
void clear(){
	while(!vec.empty()){
		auto [x,v]=vec.back();
		perm_upd(x,v);
		vec.pop_back();
	}
}
void solve(int x,bool f=0){
	int ori=w[x];
	ll best=ans; int val=ori; 
	for(int v=ori+1;v<=g[x];v++){
		temp_upd(x,1);
		int L=1,R=f?x:n;		
		
		if(s1.t[1].v==-1) chkmax(L,s1.t[1].mx);
		if(s0.t[1].v==0) chkmin(R,s0.t[1].mn-1);
		int pos=t0.qry(L,R);if(!pos) break;
		temp_upd(pos,-1);
		if(ans>best)best=ans,val=v;
	}
	clear();
	for(int v=ori-1;v>=-g[x];v--){
		temp_upd(x,-1);
		int L=1,R=f?x:n;		
		if(s0.t[1].v==-1) chkmax(L,s0.t[1].mx);
		if(s1.t[1].v==0) chkmin(R,s1.t[1].mn-1);
		int pos=t1.qry(L,R);if(!pos) break;
		temp_upd(pos,1);
		if(ans>best)best=ans,val=v;
	}
	clear();

	if(ori==val)return;
	if(ori<val){
		for(int v=ori+1;v<=val;v++){
			perm_upd(x,1);
			int L=1,R=f?x:n;		
			if(s1.t[1].v==-1) chkmax(L,s1.t[1].mx);
			if(s0.t[1].v==0) chkmin(R,s0.t[1].mn-1);
			int pos=t0.qry(L,R);assert(pos);
			perm_upd(pos,-1);
		}
	}else{
		for(int v=ori-1;v>=val;v--){
			perm_upd(x,-1);
			int L=1,R=f?x:n;		
			if(s0.t[1].v==-1) chkmax(L,s0.t[1].mx);
			if(s1.t[1].v==0) chkmin(R,s1.t[1].mn-1);
			int pos=t1.qry(L,R);assert(pos);
			perm_upd(pos,1);
		}
	}
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)g[i]=read();
	d[1]=1e9;
	for(int i=2;i<=n;i++)d[i]=read();
	s1.build(1,n,1);
	s0.build(1,n,1);

	t1.op=1; t0.init(),t1.init();

	for(int i=1;i<=n;i++)solve(i,1);
	while(q--){
		int i=read(),x=read();
		ans-=a[i]*w[i]; a[i]=x; ans+=a[i]*w[i];
		solve(i);
		printf("%lld\n",ans);
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
/*
可以。将第 \(i\) 种后缀操作定义为对 \([i+1,N]\) 加上 \(r_i-s_i\)，其中 \(p_i,q_i,r_i,s_i\ge0\)。设最终所有元素都等于自由变量 \(t\)，则原问题为

\[
\begin{aligned}
\min\quad&
\sum_{j=1}^N g_j(p_j+q_j)
+\sum_{i=1}^{N-1}d_i(r_i+s_i)\\
\text{s.t.}\quad&
B_j+p_j-q_j+\sum_{i<j}(r_i-s_i)-t=0
\qquad(1\le j\le N).
\end{aligned}
\]

给第 \(j\) 个等式分配一个**不限制正负**的对偶变量 \(y_j\)。拉格朗日函数是

\[
\begin{aligned}
L={}&\sum_{j=1}^N B_jy_j-t\sum_{j=1}^Ny_j\\
&+\sum_{j=1}^N\bigl[(g_j+y_j)p_j+(g_j-y_j)q_j\bigr]\\
&+\sum_{i=1}^{N-1}
\left[
\left(d_i+\sum_{j=i+1}^Ny_j\right)r_i+
\left(d_i-\sum_{j=i+1}^Ny_j\right)s_i
\right].
\end{aligned}
\]

要使它对原变量的下确界不是 \(-\infty\)，必须满足：

- \(t\) 自由，因此 \(\sum_jy_j=0\)；
- \(p_j,q_j\ge0\)，因此 \(-g_j\le y_j\le g_j\)；
- \(r_i,s_i\ge0\)，因此 \(-d_i\le\sum_{j=i+1}^Ny_j\le d_i\)。

所以**对偶问题**为

\[
\boxed{
\begin{aligned}
\max\quad&\sum_{j=1}^NB_jy_j\\
\text{s.t.}\quad&
\sum_{j=1}^Ny_j=0,\\
&|y_j|\le g_j &&(1\le j\le N),\\
&\left|\sum_{j=i+1}^Ny_j\right|\le d_i
&&(1\le i<N).
\end{aligned}}
\]

进一步令前缀和
\[
z_i=\sum_{j=1}^iy_j,\qquad z_0=z_N=0.
\]
由于总和为零，后缀和限制就是 \(|z_i|\le d_i\)。目标函数分部求和得到

\[
\sum_{j=1}^NB_jy_j
=\sum_{i=1}^{N-1}(B_i-B_{i+1})z_i.
\]

于是可以写成更简洁的形式：

\[
\boxed{
\begin{aligned}
f(B)=\max\quad&
\sum_{i=1}^{N-1}(B_i-B_{i+1})z_i\\
\text{s.t.}\quad&
z_0=z_N=0,\\
&|z_i|\le d_i &&(1\le i<N),\\
&|z_i-z_{i-1}|\le g_i &&(1\le i\le N).
\end{aligned}}
\]

也就是：**选择一条高度受 \(d_i\) 限制、相邻高度差受 \(g_i\) 限制的折线，最大化相邻差分 \(B_i-B_{i+1}\) 对高度的加权和。**

整数限制不会造成对偶间隙：原问题的等式相邻作差、消去 \(t\) 后，系数矩阵是全幺模的，因此整数 \(B\) 下线性规划松弛存在整数最优解。以上默认 \(d_i\ge0\)；若有负数，对偶会不可行，原问题也可能无下界。
*/