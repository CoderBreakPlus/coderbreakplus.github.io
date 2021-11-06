#include<cstdio>
using namespace std;
int n,q,a[8005],f[8005];
int read(){
	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x;
}
void Update(int x,int v){
	for(int i=1;i<x;i++)
		if(a[x]<a[i]) f[i]--;
	for(int i=x+1;i<=n;i++)
		if(a[x]<=a[i]) f[i]--;
	a[x]=v;
	for(int i=1;i<x;i++)
		if(a[x]<a[i]) f[i]++;
	for(int i=x+1;i<=n;i++)
		if(a[x]<=a[i]) f[i]++;
	f[x]=0;
	for(int i=1;i<x;i++)
		if(a[i]<=a[x]) f[x]++;
	for(int i=x+1;i<=n;i++)
		if(a[i]<a[x]) f[x]++;
}
int main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++)
			if(a[j]<=a[i]) f[i]++;
		for(int j=i+1;j<=n;j++)
			if(a[j]<a[i]) f[i]++;
	}
	while(q--){
		int opt,x,v;
		opt=read();
		if(opt==1){
			x=read(),v=read();
			Update(x,v);
		}else{
			x=read();
			printf("%d\n",f[x]+1);
		}
	}
	return 0;
}
