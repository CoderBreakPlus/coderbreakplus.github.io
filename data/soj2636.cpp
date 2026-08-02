// created time: 2026-08-02 18:54:30
#include<bits/stdc++.h>
#include"search.h"

using namespace std;
typedef long long ll;

void init(int c,int t){ }
int n,k;
struct sgt{
	vector<Data>t;
	void init(vector<Data>v){
		t.resize(2<<n);
		for(int i=0;i<(1<<n);i++)t[i+(1<<n)]=v[i];
		for(int i=(1<<n)-1;i>=1;i--)t[i]=t[i<<1]+t[i<<1|1];
	}
	void upd(int x,Data v){
		t[x+=(1<<n)]=v;
		for(x>>=1;x;x>>=1) t[x]=t[x<<1]+t[x<<1|1];
	}
}S[1005];
Data sum[200005];
int solve(vector<array<int,3>> v,Data res){
	for(int d=n;d>=1;d--){
		int cut=0;
		for(int i=0;i<k;i++)
			if(v[i][0]+(1<<d-1)<v[k-1][0]){
				cut=i+1;
				sum[0]=sum[0]+S[v[i][1]].t[v[i][2]<<1];
				v[i][0]+=(1<<d-1);
				v[i][2]=(v[i][2]<<1|1);
			}else v[i][2]<<=1;

		inplace_merge(v.begin(),v.begin()+cut,v.end());

		int i=0,sz=0; vector<array<int,3>>w(k);
		while(sz<k||!(res<sum[sz])){
			sum[sz+1]=sum[sz]+S[v[i][1]].t[v[i][2]];
			v[i][2]++,v[i][0]+=(1<<d-1);
			++sz,i=(i+1)%k;
		}

		for(int j=0;j<k;j++) w[j]=v[(i+j)%k],w[j][2]--,w[j][0]-=(1<<d-1);
		sum[0]=sum[sz-k],swap(w,v);
	}
	return v[k-1][0];
}
void search(int _k,int _n,int q, vector<vector<Data>>a){
	k=_k,n=_n;
	for(int i=0;i<k;i++) S[i].init(a[i]);

	while(q--){
		int op = query();
		if(!op){
			int i,j; Data x;
			query0(i,j,x);
			S[i].upd(j,x);
		}else{
			Data x; vector<int> c;
			query1(x,c);
			int mx=*max_element(c.begin(),c.end());

			vector<array<int,3>>all(k);
			for(int i=0;i<k;i++) all[i]={mx-c[i],i,1};
			sort(all.begin(),all.end());
			sum[0]=emptyData();

			report(solve(all,x)-mx);
		}
	}
}