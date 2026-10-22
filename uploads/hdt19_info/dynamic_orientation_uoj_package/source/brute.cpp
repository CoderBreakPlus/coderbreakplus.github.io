// Slow reference: rebuild a balanced orientation at every query.
#include "path.h"
#include <bits/stdc++.h>
using namespace std;
namespace Brute{
const int N=200005,mod=998244353;
int n,tot,u[N],v[N],pw[N];bool alive[N],used[N];
map<pair<int,int>,int>ids;
vector<int>g[N],chosen;
}
void init(int n,int q){
	using namespace Brute;Brute::n=n;tot=0;ids.clear();chosen.clear();
	fill(alive,alive+q+1,false);pw[0]=1;
	for(int i=1;i<=q;i++)pw[i]=2LL*pw[i-1]%mod;
}
void add(int u,int v,int i){
	using namespace Brute;tot=i;Brute::u[i]=u;Brute::v[i]=v;alive[i]=true;ids[{u,v}]=i;
}
void del(int u,int v){using namespace Brute;auto it=ids.find({u,v});alive[it->second]=false;ids.erase(it);}
int query(){
	using namespace Brute;chosen.clear();
	for(int x=1;x<=n;x++)g[x].clear();
	fill(used,used+tot+1,false);
	for(int i=1;i<=tot;i++)if(alive[i]){g[u[i]].push_back(i);g[v[i]].push_back(i);}
	vector<int>st;int h=0;
	for(int x=1;x<=n;x++){
		st.push_back(x);
		while(!st.empty()){
			int a=st.back();
			while(!g[a].empty()&&used[g[a].back()])g[a].pop_back();
			if(g[a].empty()){st.pop_back();continue;}
			int i=g[a].back();g[a].pop_back();used[i]=true;
			if(a==u[i]){chosen.push_back(i);h=(h+pw[i])%mod;}
			st.push_back(u[i]^v[i]^a);
		}
	}
	return h;
}
vector<int>query_path(){return Brute::chosen;}
