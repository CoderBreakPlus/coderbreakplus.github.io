// created time: 2026-08-17 13:37:18
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e4+7,m=7;
#define pb emplace_back

inline void addmod(int &x){ (x>=mod)&&(x-=mod); }
inline int qpow(int x,int y){
	int ans=1,base=x;
	while(y){
		if(y&1)ans=ans*base%mod;
		base=base*base%mod;
		y>>=1;
	}
	return ans;
}
const int inv = qpow(1<<m, mod-2);
int n,idx,v[30005];
vector<int>E[30005];

struct Info{
	int f[1<<m];
	Info(){ memset(f,0,sizeof(f)); }
	Info(int x){
		for(int i=0;i<(1<<m);i++)
			f[i] = __builtin_parity(i&x) ? mod-1 : 1;
	}
	int getv(int x){
		int ret = 0;
		for(int i=0;i<(1<<m);i++)
			addmod(ret += (__builtin_parity(i&x) ? mod-f[i] : f[i]));
		return ret * inv % mod;
	}
};
inline Info& operator*= (Info &A, const Info &B){
	for(int i=0;i<(1<<m);i++)(A.f[i]*=B.f[i])%=mod; return A;	
}
inline Info operator* (Info A, const Info &B){ return A*=B; }
inline Info& operator+= (Info &A, const Info &B){
	for(int i=0;i<(1<<m);i++)addmod(A.f[i]+=B.f[i]);return A;
}
inline Info operator+ (Info A, const Info &B){ return A+=B; }

struct Node{
	Info f[2][2]; int sz;
	Node(){ f[0][0]=f[0][1]=f[1][0]=f[1][1]=Info(), sz=0; }
	Info *operator [](int x){ return f[x]; } 
	const Info *operator [](int x)const { return f[x]; }
}t[60005];
int lc[60005],rc[60005],fa[60005],op[60005];

inline Node operator* (const Node &A, const Node &B){
	Node C; C.sz=A.sz+B.sz;
	C.f[0][0]=A.f[0][0]+B.f[0][0];
	C.f[1][0]=A.f[1][0],C.f[0][1]=B.f[0][1];
	for(int i:{0,1})for(int j:{0,1})
		C.f[i][j]+=A.f[i][1]*B.f[1][j];
    return C;
}
inline Node operator+ (const Node &A, const Node &B){
	Node C=A; C.sz+=B.sz;
	Info tmp=B.f[1][0]+B.f[1][1];
	C.f[1][0]*=tmp;
	C.f[1][1]*=tmp;
	C.f[0][0]+=B.f[0][0]+B.f[0][1];
	return C;
}
int sz[60005],son[60005],ff[60005];
void dfs(int x,int fa){
	ff[x]=fa,sz[x]=1;
	t[x].sz=1;
	t[x][1][0]=Info(0),t[x][0][1]=t[x][1][1]=Info(v[x]);
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void pushup(int x){
	if(op[x]==0) t[x]=t[lc[x]]*t[rc[x]];
	else t[x]=t[lc[x]]+t[rc[x]];
}
int newnode(int x,int y,int o){
	++idx;
	lc[idx]=x, rc[idx]=y, op[idx]=o;
	fa[x]=fa[y]=idx,pushup(idx);
    return idx;
}
vector<int>seq;
int build(int l,int r,int o){
	if(l==r){
        return seq[l];
    }
	int sum=0, cur=0, cut=r-1;
	for(int i=l;i<=r;i++)sum+=t[seq[i]].sz;
	for(int i=l;i<r;i++){
		cur+=t[seq[i]].sz;
		if(2*cur>=sum) {cut=i; break;}
	}
	int ret= newnode(build(l,cut,o),build(cut+1,r,o),o);
    return ret;
}
int build(int x){
	vector<int>now; now.pb(x);
	for(;son[x];x=son[x]){
		vector<int>cur;
		for(auto y:E[x]) if(y!=ff[x]&&y!=son[x]) cur.pb(build(y));
		if(cur.empty()) now.pb(son[x]);
		else{
			seq=cur;
			now.pb(newnode(son[x],build(0,(int)seq.size()-1,1),1));
		}
	}
	seq=now;
	return build(0,(int)seq.size()-1,0);
}
int main(){
    int shit;
	scanf("%d%d",&n,&shit); idx=n;
	
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	
	for(int i=1;i<n;i++){
		int u,v; scanf("%d%d",&u,&v);
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int rt=build(1);

	int q;scanf("%d",&q);
	while(q--){
		char s[10];
		scanf("%s",s);
		if(s[0]=='C'){
			int x,y; scanf("%d%d",&x,&y);v[x]=y;
			t[x][1][0]=Info(0),t[x][0][1]=t[x][1][1]=Info(v[x]);
			while(fa[x])pushup(x=fa[x]);
		}else{
			int k; scanf("%d",&k);
			printf("%d\n",(t[rt][0][0]+t[rt][0][1]).getv(k));
		}
	}
    return 0;
} 