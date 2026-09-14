// created time: 2026-09-14 14:06:22
#include<vector>
#include"sorting.h"

using namespace std;
vector<int> sorting(int n){
	vector<int>a(1<<n);
	for(int i=0;i<(1<<n);i++)a[i]=i;
	for(int i=0;i<n;i++)
		for(int j=i;j>=0;j--){
			vector<pair<int,int>>pairs; int m=0;
			for(int x=0;x<(1<<j);x++)
				for(int y=0;y<(1<<n);y+=(1<<j+1))
					pairs.pb(a[x+y],a[x+y+(1<<j)]);
			vector<bool>ret=calc(pairs);
			for(int x=0;x<(1<<j);x++)
				for(int y=0;y<(1<<n);y+=(1<<j+1))
					if(ret[m++]==((y>>i+1)&1)) swap(a[x+y],a[x+y+(1<<j)]);
		}
	return a;
}