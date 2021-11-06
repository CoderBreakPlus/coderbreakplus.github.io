#include<cstdio>
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],ls[maxn<<2],rs[maxn<<2],v0[maxn<<2],v1[maxn<<2],v2[maxn<<2];
struct Node{
	int n0,n1,n2;
};
int read(){
	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x;
}
void pushup(int pos){
	v0[pos]=v0[pos<<1]+v0[pos<<1|1];
	v1[pos]=v1[pos<<1]+v1[pos<<1|1];
	v2[pos]=v2[pos<<1]+v2[pos<<1|1];
}
void build(int l,int r,int pos){
	ls[pos]=l,rs[pos]=r;
	if(l==r){
		if(a[l]==0) v0[pos]=1;
		else v1[pos]=1;
		return;
	}
	int mid=l+r>>1;
	if(l<=mid) build(l,mid,pos<<1);
	if(mid<r)  build(mid+1,r,pos<<1|1);
	pushup(pos);
}
void update(int l,int pos){
	if(ls[pos]==rs[pos]){
		v0[pos]=v1[pos]=0; v2[pos]=1;
		return;
	}
	int mid=ls[pos]+rs[pos]>>1;
	if(l<=mid) update(l,pos<<1);
	else update(l,pos<<1|1);
	pushup(pos);
}
Node Union(Node A,Node B){
	Node C;
	C.n0=A.n0+B.n0;
	C.n1=A.n1+B.n1;
	C.n2=A.n2+B.n2;
	return C;
}
Node query(int l,int r,int pos){
	if(l<=ls[pos]&&rs[pos]<=r) return (Node){v0[pos],v1[pos],v2[pos]};
	int mid=ls[pos]+rs[pos]>>1; Node ans=(Node){0,0,0};
	if(l<=mid) ans=query(l,r,pos<<1);
	if(mid<r){
		Node tmp=query(l,r,pos<<1|1);
		ans.n0+=tmp.n0,ans.n1+=tmp.n1,ans.n2+=tmp.n2;
	}
	return ans;
}
void Update(int s){
	a[s]=2; update(s,1);
}
bool all=1;
int main(){
	freopen("fruit.in","r",stdin);
	freopen("fruit.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=n;i++){
		if(a[i]!=a[i-1]) all=0;
	}
	if(all){
		for(int i=1;i<=n;i++) printf("%d\n",i);
		return 0;
	}
	build(1,n,1);
	while(1){
		int i;
		for(i=1;i<=n;i++)
			if(a[i]!=2) break;
		if(i==n+1) break;
		printf("%d ",i);
		while(1){
			if(i>n) break;
			int nowcol=a[i];
			int lft=i,rht=n,ans=-1;
			while(lft<=rht){
				int mid=lft+rht>>1;
				Node TMP=query(i,mid,1);
				if(nowcol==0){
					if(TMP.n0+TMP.n2==(mid-i+1)){
						ans=mid;
						lft=mid+1;
					}else rht=mid-1;
				}else{
					if(TMP.n1+TMP.n2==(mid-i+1)){
						ans=mid;
						lft=mid+1;
					}else rht=mid-1;
				}
			}
			if(ans==-1) break;
			Update(i), i=ans+1;
			if(i<=n) printf("%d ",i);
		}
		putchar('\n');
	}
	return 0;
}
