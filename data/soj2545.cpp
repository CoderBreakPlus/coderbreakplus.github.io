#include<bits/stdc++.h>
#include"xor.h"
using namespace std;
const int N = 16;

struct Node{
	int s,t;
	data a[2][2];
};
bool operator< (const Node &A,const Node &B){
	return A.s!=B.s?A.s<B.s:A.t<B.t;
}
bool operator== (const Node &A,const Node &B){
	return A.s==B.s&&A.t==B.t;
}
Node operator* (const Node &A,const Node &B){
	Node C;
	C.s=A.s,C.t=A.t;
	for(int p:{0,1})for(int q:{0,1})
		C.a[p][q]=A.a[p][q]*B.a[p][q];
	return C;
}
data ans[1<<N];
void solve(vector<Node> M, data *ans, int N){
	sort(M.begin(), M.end());
	vector<Node> M2;

	for(auto x: M){
		if(!M2.empty()&&x==M2.back())
			M2[M2.size()-1]=M2[M2.size()-1]*x;
		else M2.push_back(x);
	}
	if(~N){
		vector<Node>ok[2];
		for(auto x:M2){
			for(int o:{0,1}){
				auto y = x;
				int flip_b = (y.s >> N) & 1;
            	int flip_c = (y.t >> N) & 1;
            	if(o&&flip_b){
            		swap(y.a[0][0],y.a[1][0]);
            		swap(y.a[0][1],y.a[1][1]);
            	}
            	if(o&&flip_c){
            		swap(y.a[0][0],y.a[0][1]);
            		swap(y.a[1][0],y.a[1][1]);
            	}
				y.s &= ~(1<<N), y.t &= ~(1<<N);
				if(y.s>y.t){
					swap(y.s,y.t);
					swap(y.a[0][1],y.a[1][0]);
				}
				ok[o].push_back(y);
			}
		}
		solve(ok[0], ans, N-1);
		solve(ok[1], ans+(1<<N), N-1);
	}else{
		auto x = M2[0];
		ans[0] = x.a[0][0];
	}
}
vector<data> convolution(int n, int m, vector<data> a, vector<data> b, vector<data> c, vector<int> S, vector<int> T){
	vector<Node>fuck;
	for(int i=0;i<n;i++){
		Node x;
		if(S[i]>T[i])swap(S[i],T[i]),swap(b[i],c[i]);
		x.s=S[i],x.t=T[i];
		x.a[0][0]=a[i]+b[i]+c[i];
		x.a[0][1]=a[i]+b[i]-c[i];
		x.a[1][0]=a[i]-b[i]+c[i];
		x.a[1][1]=a[i]-b[i]-c[i];
		fuck.push_back(x);
	}
	solve(fuck,ans,m-1);
	for(int i=0;i<m;i++)
		for(int j=0;j<(1<<m);j++){
			if((j>>i)&1) {
				data a0 = ans[j^(1<<i)], a1 = ans[j];
				ans[j^(1<<i)] = a0 + a1;
				ans[j] = a0 - a1;
			}
		}
	return vector<data>(ans, ans+(1<<m));
}