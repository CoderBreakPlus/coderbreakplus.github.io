# Practical Templates

## 数据结构

### static top tree

[P4751 【模板】动态 DP（加强版）](https://www.luogu.com.cn/problem/P4751)

```cpp
struct Node{
	int f[2][2],sz;
	Node(){ memset(f,0,sizeof(f)),sz=0; }
	int *operator [](int x){ return f[x]; }
	const int *operator [](int x)const{ return f[x]; }
}t[2000005];
int lc[2000005],rc[2000005],fa[2000005],op[2000005],id;

inline Node operator* (const Node& A,const Node& B){
	Node C; C.sz=A.sz+B.sz;
	for(int x:{0,1})for(int y:{0,1})
		C.f[x][y]=max(A.f[x][0]+B.f[1][y],A.f[x][1]+B.f[0][y]);
	return C;
}
inline Node operator+ (const Node& A,const Node& B){
	Node C; C.sz=A.sz+B.sz;
	for(int x:{0,1})for(int y:{0,1})
		C.f[x][y]=A.f[x][y]+B.f[x][1];
	return C;
}
int sz[2000005],son[2000005],ff[2000005];
void dfs(int x,int fa){
	ff[x]=fa,sz[x]=1;
	t[x].sz=1,t[x][1][1]=max(a[x],0);
	for(auto y: E[x]){
		if(y==fa)continue;
		dfs(y,x),sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void pushup(int x){
	if(op[x]==0) t[x]=t[lc[x]]*t[rc[x]];
	else t[x]=t[lc[x]]+t[rc[x]];
}
int newnode(int x,int y,int o){
	++id;
	lc[id]=x, rc[id]=y, op[id]=o;
	fa[x]=fa[y]=id,pushup(id); return id;
}
vector<int>seq;
int build(int l,int r,int o){
	if(l==r) return seq[l];
	int sum=0, cur=0, cut=r-1;
	for(int i=l;i<=r;i++)sum+=t[seq[i]].sz;
	for(int i=l;i<r;i++){
		cur+=t[seq[i]].sz;
		if(2*cur>=sum) {cut=i; break;}
	}
	return newnode(build(l,cut,o),build(cut+1,r,o),o);
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
void procedure(){
	n=id=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int rt=build(1),lst=0;
	while(m--){
		int x=read()^lst,y=read();
		t[x][1][1]=max(y,0);
		while(fa[x]) x=fa[x],pushup(x);
		printf("%d\n",lst=t[rt][1][1]);
	}
}
```

## 字符串

### SAM 建立

[UOJ608 【UR #20】机器蚤分组](https://uoj.ac/problem/608)

```cpp
namespace SAM{
	int len[200005],fa[200005],son[200005][26],lst;
	inline void ins(int p,int v){
		len[p]=len[lst]+1;
		while(lst&&!son[lst][v]){
			son[lst][v]=p;
			lst=fa[lst];
		}
		if(!son[lst][v]){
			son[lst][v]=p;
		}else{
			int q=son[lst][v];
			if(len[q]==len[lst]+1){
				fa[p]=q;
			}else{
				int u=++m;
				len[u]=len[lst]+1,fa[u]=fa[q];
				memcpy(son[u],son[q],sizeof(son[u]));
				fa[p]=fa[q]=u;
				while(son[lst][v]==q){
					son[lst][v]=u;
					lst=fa[lst];
				}
			}
		}
		lst=p;
	}
}
```

## Bitset 优化

### 匈牙利

[QOJ6308 Magic](https://qoj.ac/submission/1987284)

```cpp
int n,p[N],ans;
bitset<N>e[N],vis;
bool match(int x){
	int y;
	while((y=((~vis)&e[x])._Find_first())<N){
		vis[y]=1;
 		if(!(~p[y]) || match(p[y])){ p[y]=x; return 1; }
	}
	return 0;
}
void solve(){
	int ans=0;
	memset(p,-1,sizeof(p));
	for(int i=0;i<n;i++)vis.reset(),ans+=match(i);
	return ans;
}
```

### Kosaraju

[SOJ2255 故障机器人Ⅱ](http://10.49.18.71/problem/2255)

e,g 分别是正图、反图。


```cpp
bitset<N>e[N],g[N],vis,op;
int col[1005],colt,stk[1005],tp;
void dfs(int x){
	op[x]=0;
	for(int i=(e[x]&op)._Find_first();i<n;i=(e[x]&op)._Find_next(i))
		dfs(i);
	stk[++tp]=x;
}
void dfs2(int x){
	col[x]=colt,op[x]=0;
	for(int i=(g[x]&op)._Find_first();i<n;i=(g[x]&op)._Find_next(i))
		dfs2(i);
}
void solve(){
	for(int i=0;i<n;i++) op[i]=1;
	for(int i=0;i<n;i++) if(op[i]) dfs(i);
	for(int i=0;i<n;i++) op[i]=1;
	for(;tp;--tp) if(op[stk[tp]]) ++colt,dfs2(stk[tp]);
}
```