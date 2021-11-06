#include<cstdio>
using namespace std;
int T,n,a[1000005],lst[1000005],now;
bool check(int l1,int r1,int l2,int r2){
//	printf("[%d,%d] [%d,%d]\n",l1,r1,l2,r2);
	if(l1>r1 && l2>r2) return 1;
	if(l1<r1 && a[l1]==a[r1]){
		lst[++now]=1;
		if(check(l1+1,r1-1,l2,r2)){
			lst[++now]=1;
			return 1;
		}
	}else if(l1<=r1 && l2<=r2 && a[l1]==a[l2]){
		lst[++now]=1;
		if(check(l1+1,r1,l2+1,r2)){
			lst[++now]=2;
			return 1;
		}
	}else if(l2<r2 && a[l2]==a[r2]){
		lst[++now]=2;
		if(check(l1,r1,l2+1,r2-1)){
			lst[++now]=2;
			return 1;
		}
	}else if(l1<=r1 && l2<=r2 && a[r1]==a[r2]){
		lst[++now]=2;
		if(check(l1,r1-1,l2,r2-1)){
			lst[++now]=1;
			return 1;
		}
	}
	return 0;
}
int main(){
	freopen("palin.in","r",stdin);
	freopen("palin.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		now=0;
		scanf("%d",&n); n*=2;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int s1,s2;
		for(int i=2;i<=n;i++)
			if(a[i]==a[1]) s1=i;
		for(int i=1;i<n;i++)
			if(a[i]==a[n]) s2=i;
		if(check(2,s1-1,s1+1,n)){
			putchar('L');
			for(int i=1;i<=now;i++)
				if(lst[i]==1) putchar('L');
				else putchar('R');
			puts("L");
		}else{
			now=0;
			if(check(1,s2-1,s2+1,n-1)){
				putchar('R');
				for(int i=1;i<=now;i++)
					if(lst[i]==1) putchar('L');
					else putchar('R');
				puts("L");
			}else puts("-1");
		}
	}
	return 0;
}
