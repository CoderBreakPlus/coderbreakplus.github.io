令 $a_i < b_i$。考虑若 $b_i>a_j$，则连边 $i \to j$。两个点之间可能连了双向边。

一个排列 $p_1,p_2,\cdots,p_n$ 合法当且仅当存在一个 $x$ 使得存在 $p_1 \to p_2 \to \cdots \to p_x$ 的连边和 $p_n \to p_{n-1} \to \cdots \to p_x$ 的连边。动态维护这个形如 `>>>><<<<<` 的结构。

考虑枚举 $p_x=i$，为了防止算重，钦定 $p_{x-1} \to i$ 是单向边。

初始排列只有 $i$，接下来按照 $b$ 从大到小的顺序插入（以下默认 $b_i > b_{i+1}$）。

插入 $j$ 的时候，如果 $b_j$ 大于某个 $a_k$，则可以跟在 $k$ 的后面（连接 $k \to j$）。如果 $k$ 本来有后继 $l$，显然有 $b_l > b_j > a_j$，所以 $j \to l$ 的边一定存在，不影响。

关键在于处理 $j$ 直接跟在 $i$ 的前后的情况。跟在后面无所谓，跟在前面我们得刷新一下现在 $p_{x-1}$ 和 $i$ 的连边状态。dp 的时候记录一个 $0/1$ 即可。据此我们先写出 $\mathcal{O}(n^2)$ 的代码。

```cpp
int n,a[200005],b[200005],o[200005],aa[200005],bb[200005];
int f[2],g[2];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		o[i]=i;
		a[i]=aa[i]=read(),b[i]=bb[i]=read();
		if(a[i]>b[i])swap(a[i],b[i]),swap(aa[i],bb[i]);
	}
	sort(o+1,o+n+1,[&](int x,int y){ return b[x]>b[y]; });
	for(int i=1;i<=n;i++) a[i]=aa[o[i]],b[i]=bb[o[i]];

	int ans=0;
	for(int i=1;i<=n;i++){
		f[0]=1,f[1]=0;
		for(int j=1;j<=n;j++)if(j!=i){
			int o=a[i]<b[j],cnt=o;
			for(int k=1;k<j;k++)if(k!=i)cnt+=(a[k]<b[j]);
			for(int k:{0,1})g[k]=(ull)f[k]*cnt%mod;
			if(o){
				int oo=a[j]<b[i];
				g[oo]=((ull)g[oo]+f[0]+f[1])%mod;
			}
			f[0]=g[0],f[1]=g[1]; // 0 是单向边，1 是双向边
		}
		addmod(ans+=f[0]);
	}
	printf("%d\n",ans);
}
```

发现 $j$ 从 $1 \sim n$ 的过程很像矩阵乘法，随着 $i$ 的移动矩阵的修改量又不多。那我们直接线段树维护矩阵乘法就好了。

具体地，维护两棵线段树，分别是 $a_i>b_j$ 和 $a_i<b_j$ 两种情况下的矩阵，随着 $i$ 的移动总修改量线性，查询的时候一定是一段前缀用第一棵线段树，剩下的后缀用第二棵线段树（利用 $b$ 的有序）。

```cpp
int n,a[200005],b[200005],o[200005],aa[200005],bb[200005];

struct Mat{
	int a[2][2];
	Mat(){ memset(a,0,sizeof(a)); }
	Mat(int x,int y,int z,int w){ a[0][0]=x,a[0][1]=y,a[1][0]=z,a[1][1]=w; }
	int* operator[](int x){ return a[x]; }
	const int* operator[](int x)const{ return a[x]; }
};

Mat operator* (const Mat &A, const Mat &B){
	Mat C;
	for(int i:{0,1})for(int j:{0,1})for(int k:{0,1})
		C[i][k]=(C[i][k]+(ull)A[i][j]*B[j][k])%mod;
	return C;
}
struct Seg{
	Mat t[800005];
	void pushup(int p){
		t[p]=t[p<<1]*t[p<<1|1];
	}
	void update(int p,int l,int r,int x,Mat w){
		if(l==r){
			t[p]=w;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)update(p<<1,l,mid,x,w);
		else update(p<<1|1,mid+1,r,x,w);
		pushup(p);
	}
	Mat query(int p,int l,int r,int ql,int qr){
		if(r<ql||qr<l) return Mat(1,0,0,1);
		if(ql<=l && r<=qr) return t[p];
		int mid=(l+r)>>1;
		return query(p<<1,l,mid,ql,qr)*query(p<<1|1,mid+1,r,ql,qr);
	}
}S0,S1;

int sb[200005],c[400005];
void upd(int x,int w){
	while(x<=2*n){
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
void upd_one(int i,int j){
	if(j>n||j<1)return;
	int cnt=sb[j]+(j<i);
	Mat now(cnt,0,0,cnt);

	S0.update(1,1,n,j,now);

	int oo=a[j]<b[i];	
	now[0][oo]++,now[1][oo]++;

	S1.update(1,1,n,j,now);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		o[i]=i;
		a[i]=aa[i]=read(),b[i]=bb[i]=read();
		if(a[i]>b[i])swap(a[i],b[i]),swap(aa[i],bb[i]);
	}
	sort(o+1,o+n+1,[&](int x,int y){ return b[x]>b[y]; });
	for(int i=1;i<=n;i++) a[i]=aa[o[i]],b[i]=bb[o[i]];

	for(int i=1;i<=n;i++){
		sb[i]=qry(b[i]-1);
		upd(a[i],1);
	}
	int ans=0;
	for(int j=1;j<=n;j++)upd_one(1,j);

	vector<int>vec;
	for(int j=1;j<=n;j++)vec.pb(j);
	sort(vec.begin(),vec.end(),[&](int x,int y){ return a[x]<a[y]; });

	for(int i=1;i<=n;i++){
		int x = lower_bound(b+1,b+n+1,a[i],greater<>())-(b+1);
		addmod(ans += (Mat(1,0,0,0)*S1.query(1,1,n,1,i-1)*S1.query(1,1,n,i+1,x)*S0.query(1,1,n,x+1,n))[0][0]);
		if(i<n){
			upd_one(i+1, i);
			while(!vec.empty() && a[vec.back()]>b[i+1]){
				upd_one(i+1, vec.back());
				vec.pop_back();
			}
		}
	}
	printf("%d\n",ans);
}
```