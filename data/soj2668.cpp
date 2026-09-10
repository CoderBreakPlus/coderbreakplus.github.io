// created time: 2026-09-05
#include"b.h"
#include<bits/stdc++.h>
using namespace std;

void init(int c,int t){

}


vector<int> guess(int n){
	vector<int>sz(n+1), fir(n+1), cc(n+1);
	int mx=0;
	for(int i=1;i<=n;i++){
		int L=0,R=n-1,ok=n,mid=(L+R)>>1;
		vector<int>tmp(n);
		for(int j=mid;j<n;j++) tmp[j]=i;
		auto [a,b]=query(tmp);b+=a;

		cc[i]=1;

		if(b==n-mid){
			if(sz[mx]==n){
				sz[mx]=sz[i]=n/2, fir[i]=a;
			}else{
				sz[i]=n,mx=i;
			}
			continue;
		}
		sz[i]=b,fir[i]=a; if(sz[i]>sz[mx]) mx=i;
	}

	vector<int>ans(n,mx);
	vector<int>res_pos(n);
	for(int i=0;i<n;i++)res_pos[i]=i;

	for(int i=1;i<=n;i++)if(i!=mx){
		int lst=-1, ff=0;
		while(sz[i]--){
			int L=lst+1,R=res_pos.size()-1,ok=-1;
			if(!ff){
				if(fir[i]<=sz[i]) {
					while(res_pos[R]>=(n-1)/2) R--;
				}else{
					while(res_pos[L]<(n-1)/2) L++;
				}
				ff=1;
			}
			while(L<=R){
				int mid=(L+R)>>1,res;
				if(!ff) res=fir[i],ff=1;
				else{
					vector<int>tmp(n);
					for(int j=res_pos[mid]+1;j<n;j++) tmp[j]=i;
					res=query(tmp).first;
				}
				if(res<=sz[i]) ok=mid,R=mid-1;
				else L=mid+1;
			}
			assert(~ok);
			lst=ok;
			ans[res_pos[ok]]=i;
		}
		vector<int>new_pos;
		for(int j=0;j<n;j++)
			if(ans[j]==mx) new_pos.push_back(j);
		swap(res_pos,new_pos);
	}
	return ans;
}
