// created time: 2026-10-09
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int N=300000;
inline int read(){
	int x=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
inline int lg2(int x){return 31^__builtin_clz(x);}
int n,p[N+5],ip[N+5],itmp[N+5];
vector<pair<int,int>>q[N+5];
int stk[N+5],tp;
int tmp[N+5],pos[N+5],qz[N+5],m,idx;
int _prv[N+5],_nxt[N+5];
ll ans[N+5];int len[N+5],ans2[N+5],siz[N+5];

// 修改 1：同一套 O(1) 静态 RMQ 分别用于旧点最大值、新点最早时间。
struct RMQ{
	const int *a;
	ull mask[N+5];
	int pre[N+5],suf[N+5];
	int st[15][(N+63)/64+5],nb;
	void init(const int *v,int n){
		a=v;
		nb=(n+63)>>6;
		for(int b=0;b<nb;b++){
			int l=b*64+1,r=min(n,l+63),mx=0;
			ull s=0;
			for(int i=l;i<=r;i++){
				int j=i-l;
				while(s){
					int t=63-__builtin_clzll(s);
					if(a[l+t]>a[i])break;
					s^=1ull<<t;
				}
				s|=1ull<<j;
				mask[i]=s;
				pre[i]=mx=max(mx,a[i]);
			}
			mx=0;
			for(int i=r;i>=l;i--)suf[i]=mx=max(mx,a[i]);
			st[0][b]=pre[r];
		}
		for(int k=1;(1<<k)<=nb;k++)
			for(int b=0;b+(1<<k)<=nb;b++)
				st[k][b]=max(st[k-1][b],st[k-1][b+(1<<(k-1))]);
	}
	inline int qry(int l,int r)const{
		if(l>r)return 0;
		int x=(l-1)>>6,y=(r-1)>>6;
		if(x==y){
			ull s=mask[r]&(ULLONG_MAX<<((l-1)&63));
			return a[(x<<6)+1+__builtin_ctzll(s)];
		}
		int res=max(suf[l],pre[r]);
		if(y>x+1){
			int L=x+1,R=y-1,k=lg2(R-L+1);
			res=max(res,max(st[k][L],st[k][R-(1<<k)+1]));
		}
		return res;
	}
}T,TD;

// 修改 2：HNOI2016 序列的单调栈 DP：左右第一更大点链的计数/坐标和。
int cntL[N+5],cntR[N+5];
ll sumL[N+5],sumR[N+5];

// 修改 3：每个旧点候选只初始化一次，按死亡时间分桶。
int tval[N+5],deadhead[N+5],deadlink[N+5],weight[N+5];

// 修改 4：按长度分块的二维数点，修改 O(1)，查询 O(sqrt(n))。
struct SqrtCounter{
	int sh,D;
	int cnt[N+5],bcnt[1024];
	ll bsum[1024];
	void init(int M){
		sh=(lg2(max(1,M))+1)>>1;
		D=1<<sh;
		fill(cnt,cnt+M+1,0);
		fill(bcnt,bcnt+(M>>sh)+2,0);
		fill(bsum,bsum+(M>>sh)+2,0);
	}
	inline void upd(int x,int d){
		cnt[x]+=d;
		int b=x>>sh;
		bcnt[b]+=d;
		bsum[b]+=(ll)x*d;
	}
	inline pair<ll,ll> qry(int x)const{
		if(x<=0)return {0,0};
		ll c=0,s=0;
		int b=x>>sh;
		for(int i=0;i<b;i++)c+=bcnt[i],s+=bsum[i];
		for(int i=(b<<sh);i<=x;i++)c+=cnt[i],s+=(ll)i*cnt[i];
		return {c,s};
	}
}SC;

// 修改 5：只有时间分块，不再需要事件数和询问数限制。
int beg[N+5],ed[N+5],bsz;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=read(),ip[p[i]]=i;
	idx=0;
	for(int i=1;i<=n;i++){
		int k=read();
		q[i].clear();
		while(k--)siz[++idx]=i,q[i].pb(len[idx]=read(),idx),ans[idx]=ans2[idx]=0;
	}
	int B=max(1,(int)(1.5*n/sqrt((double)(n+idx))));
	bsz=0;
	for(int x=1;x<=n;x++)if(!q[x].empty()){
		if(!bsz||x-beg[bsz]+1>B)beg[++bsz]=x;
		ed[bsz]=x;
	}
	for(int ww=1;ww<=bsz;ww++){
		int L=beg[ww],R=ed[ww];
		m=0;
		for(int j=1;j<=n;j++){
			qz[j]=qz[j-1];
			if(p[j]<L)tmp[++m]=p[j],pos[m]=j,qz[j]++;
			// 将当前块内的时间映射为正值，0 表示不在当前块内。
			tval[j]=(L<=p[j]&&p[j]<=R)?R+1-p[j]:0;
		}
		T.init(tmp,m);
		TD.init(tval,n);
		for(int i=1;i<=m;i++)_prv[i]=0,_nxt[i]=m+1,itmp[tmp[i]]=i;
		tp=0;
		for(int i=1;i<=m;i++){
			while(tp&&tmp[stk[tp]]<tmp[i])_nxt[stk[tp--]]=i;
			if(tp)_prv[i]=stk[tp];
			stk[++tp]=i;
		}
		cntL[0]=0;sumL[0]=0;
		for(int i=1;i<=m;i++){
			int j=_prv[i];
			cntL[i]=cntL[j]+1;
			sumL[i]=sumL[j]+i;
		}
		cntR[m+1]=0;sumR[m+1]=0;
		for(int i=m;i>=1;i--){
			int j=_nxt[i];
			cntR[i]=cntR[j]+1;
			sumR[i]=sumR[j]+i;
		}
		SC.init(m);
		fill(deadhead+L,deadhead+R+1,0);
		for(int i=1;i<=m;i++)if(_prv[i]&&_nxt[i]<=m){
			int a=_prv[i],b=_nxt[i];
			int w=b-a;
			weight[i]=w;
			SC.upd(w,1);
			int v=TD.qry(pos[a]+1,pos[b]-1);
			if(v){
				int death=R+1-v;
				deadlink[i]=deadhead[death];
				deadhead[death]=i;
			}
		}
		int s[B+5],tl=0;
		for(int x=L;x<=R;x++){
			// 从当前时刻起，包含新加入点的候选已失效。
			for(int j=deadhead[x];j;j=deadlink[j])SC.upd(weight[j],-1);
			s[++tl]=ip[x];
			int v=s[tl],*it=lower_bound(s+1,s+tl,v);
			memmove(it+1,it,(s+tl-it)*sizeof(int));
			*it=v;
			if(q[x].empty())continue;
			int prv[B+5],nxt[B+5];tp=0;
			for(int j=1;j<=tl;j++)prv[j]=0,nxt[j]=tl+1;
			for(int j=1;j<=tl;j++){
				while(tp&&p[s[stk[tp]]]<p[s[j]])nxt[stk[tp--]]=j;
				if(tp)prv[j]=stk[tp];
				stk[++tp]=j;
			}
			for(auto [k,id]:q[x]){
				// 原 q2/q3 的整组二维数点，合并成当前原始询问的一次查询。
				auto [v0,v1]=SC.qry(min(k-1,m));
				ans[id]+=v1;
				ans2[id]+=v0;
				for(int j=1;j<=tl;j++){
					if(!prv[j]||nxt[j]>tl)continue;
					int sz=qz[s[nxt[j]]]-qz[s[prv[j]]]+nxt[j]-prv[j];
					if(sz<=k)ans[id]+=sz,ans2[id]++;
				}
				auto solve=[&](int l,int r,bool vl,bool vr){
					if(l>r)return;
					int mx=itmp[T.qry(l,r)];
					if(!vl&&!vr&&r-l+2<=k)ans[id]+=r-l+2,ans2[id]++;
					// 原 q0：右侧更大点链的前缀，RMQ 定位最后一个点。
					if(!vl){
						int rr=min(l+k-1,mx);
						if(rr>l){
							int t=rr==mx?mx:itmp[T.qry(l,rr)];
							ll c=cntR[l]-cntR[t];
							ll v=sumR[l]-sumR[t]+t-l;
							ans[id]+=v-(ll)(l-1)*c;
							ans2[id]+=c;
						}
					}
					// 原 q1：左侧更大点链的前缀，RMQ 定位最左端点。
					if(!vr){
						int left=max(r-k+1,mx);
						if(left<r){
							int t=left==mx?mx:itmp[T.qry(left,r)];
							ll c=cntL[r]-cntL[t];
							ll v=sumL[r]-sumL[t]+t-r;
							ans[id]+=(ll)(r+1)*c-v;
							ans2[id]+=c;
						}
					}
				};
				solve(1,qz[s[1]],1,0);
				for(int j=1;j<tl;j++)solve(qz[s[j]]+1,qz[s[j+1]],0,0);
				solve(qz[s[tl]]+1,m,0,1);
			}
		}
	}
	for(int i=1;i<=idx;i++)printf("%lld\n",ans[i]+(ll)(siz[i]-ans2[i])*len[i]);
}
int main(){
#ifdef LOCAL
	assert(freopen("test.in","r",stdin));
	assert(freopen("test.out","w",stdout));
#endif
	int T=read();
	while(T--)procedure();
	return 0;
}
