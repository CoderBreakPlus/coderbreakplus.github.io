#include <bits/stdc++.h>
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define fi first
#define se second
using namespace std;
const int MAXN=3e5+2,MOD=1e9+7;
int n;
pair<int,int>val[MAXN];
int cnt;
struct Node{
	short type;//-1unit,0rake,1compress
	int up,dn,mid;
	int siz,lc,rc,fa;
	ll f[2][2],g[2][2];
	Node(const int&t=-1,const int&d=0,const int&e=0,const int&a=1,const int&b=0,const int&c=0){
		type=t,siz=a,lc=b,rc=c,up=d,dn=e,fa=0;
		memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
		return;
	}
}node[MAXN<<1];
bool isin[MAXN]; 
inline void upd(int now){
	Node&qwq(node[now]),&l(node[qwq.lc]),&r(node[qwq.rc]);
	memset(qwq.f,0,sizeof(qwq.f));
	if(node[now].type) F(i,0,1) F(j,0,1) F(k,0,isin[l.dn]) qwq.f[i][j]=(qwq.f[i][j]+l.f[i][k]*r.f[k][j])%MOD;
	else F(i,0,1) F(j,0,1) F(k,0,isin[r.dn]) qwq.f[i][j]=(qwq.f[i][j]+l.f[i][j]*r.f[i][k])%MOD;
	return;
}
inline void psd(int now){
	Node&qwq(node[now]),&l(node[qwq.lc]),&r(node[qwq.rc]);
	if(node[now].type){
		/*
		转置前 
		F(i,0,1) F(j,0,1) F(k,0,isin[l.dn]){
			qwq.g[i][j]=(qwq.g[i][j]+l.f[i][k]*r.g[k][j])%MOD;
			qwq.g[i][j]=(qwq.g[i][j]+l.g[i][k]*r.f[k][j])%MOD;
		}
		*/ 
		F(i,0,1) F(j,0,1) F(k,0,isin[l.dn]){
			r.g[k][j]=(r.g[k][j]+l.f[i][k]*qwq.g[i][j])%MOD;
			l.g[i][k]=(l.g[i][k]+r.f[k][j]*qwq.g[i][j])%MOD;
		}//倒不倒序不影响 
	}else{
		/*
		转置前 
		F(i,0,1) F(j,0,1) F(k,0,isin[r.dn]){
			qwq.g[i][j]=(qwq.g[i][j]+l.f[i][j]*r.g[i][k])%MOD;
			qwq.g[i][j]=(qwq.g[i][j]+l.g[i][j]*r.f[i][k])%MOD;
		}
		*/ 
		F(i,0,1) F(j,0,1) F(k,0,isin[r.dn]){
			r.g[i][k]=(r.g[i][k]+l.f[i][j]*qwq.g[i][j])%MOD;
			l.g[i][j]=(l.g[i][j]+r.f[i][k]*qwq.g[i][j])%MOD;
		}
	}
	memset(qwq.g,0,sizeof(qwq.g));
	return;
}
inline int merge(int x,int y,int type){
	node[x].fa=node[y].fa=++cnt;
	node[cnt]=Node(type,node[x].up,node[type?y:x].dn,node[x].siz+node[y].siz,x,y);
	return upd(cnt),cnt;
}
#define Poi vector<int>::iterator
int build(Poi l,Poi r,int type){
	if(l==r) return 0;
	if(l+1==r) return *l;
	int sum=0,all=0;
	for(auto it=l;it!=r;++it) all+=node[*it].siz;
	Poi mid=l+1;
	for(auto it=l;it!=r;++it){
		sum+=node[*it].siz;
		if(sum*2<=all) mid=it+1;
		else break;
	}
	return merge(build(l,mid,type),build(mid,r,type),type);
}
int siz[MAXN],fa[MAXN],son[MAXN],rt[MAXN];//根为 cnt 
vector<int>g[MAXN];
void dfs1(int now){
	siz[now]=1;
	node[now]=Node(-1,fa[now],now);
	node[now].f[0][0]=node[now].f[1][0]=node[now].f[0][1]=1;
	isin[now]=1;
	for(int i:g[now]){
		dfs1(i);
		siz[now]+=siz[i];
		if(siz[son[now]]<siz[i]) son[now]=i;
	}
	return;
}
void dfs2(int now,bool heavy){
	if(son[now]) dfs2(son[now],1);
	for(int i:g[now]) if(i!=son[now]) dfs2(i,0);
	if(!heavy){
		vector<int>chain;
		chain.push_back(now);
		for(int i(son[now]);i;i=son[i]){
			vector<int>sub({i});
			for(int j:g[fa[i]]) if(j!=i) sub.push_back(rt[j]);
			chain.push_back(build(sub.begin(),sub.end(),0));
		}
		rt[now]=build(chain.begin(),chain.end(),1);
	}
	return;
}
int ans[MAXN];
signed main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	F(i,2,n) cin>>fa[i],g[fa[i]].push_back(i);
	F(i,1,n) cin>>val[i].fi,val[i].se=i;
	sort(val+1,val+n+1);
	dfs1(1),cnt=n,dfs2(1,0);
	R(i,n,1){//倒序执行 
		/*
		转置前 (ans[i]-ans[i-1])+=node[cnt].g[0][0/1] 
		转置后倒序变成 node[cnt].g[0][0/1]+=val[i]-val[i+1] 
		*/
		node[cnt].g[0][0]=(node[cnt].g[0][0]+val[i].fi-val[i+1].fi+MOD)%MOD;
		if(isin[node[cnt].dn]) node[cnt].g[0][1]=(node[cnt].g[0][1]+val[i].fi-val[i+1].fi+MOD)%MOD;
		int now=val[i].se,tp=0;
		static int path[MAXN];
		while(node[now].fa) path[++tp]=node[now].fa,now=path[tp];
		R(j,tp,1) psd(path[j]);//从上到下倒序执行 
		now=val[i].se;
		ans[now]=node[now].g[0][1];
		//node[now].g[0][1]=0;
		//node[now].g[0][1]=val[now]的转置 
		isin[now]=0,node[now].f[0][1]=0; 
		while(node[now].fa) upd(node[now].fa),now=node[now].fa;//按原顺序更新常量（矩阵里的量） 
	}
	F(i,1,n) cout<<ans[i]<<" "; 
	return 0;
}
