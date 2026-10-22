#include "path.h"
#include <bits/stdc++.h>
using namespace std;
namespace {
const int MOD=998244353;
struct Op{int type,u=0,v=0;};
[[noreturn]] void fail(const char *message){
	fprintf(stderr,"Wrong Answer: %s\n",message);puts("WA");exit(0);
}
}
int main(){
	int n,q;
	if(scanf("%d%d",&n,&q)!=2)return 1;
	if(n<1||n>200000||q<1||q>200000)return 1;
	vector<Op>ops(q);
	for(auto &o:ops){
		if(scanf("%d",&o.type)!=1)return 1;
		if(o.type==1||o.type==2)
			if(scanf("%d%d",&o.u,&o.v)!=2)return 1;
	}
	fclose(stdin);
	vector<int>u(q+1),v(q+1),pw(q+1,1),seen(q+1),balance(n+1);
	vector<bool>alive(q+1);
	map<pair<int,int>,int>edges;
	int serial=0,last_hash=0,last_type=0,paths=0;
	for(int i=1;i<=q;i++)pw[i]=2LL*pw[i-1]%MOD;
	init(n,q);
	for(const auto &o:ops){
		if(o.type==1){
			int i=++serial;u[i]=o.u;v[i]=o.v;alive[i]=true;
			edges[{o.u,o.v}]=i;add(o.u,o.v,i);
		}else if(o.type==2){
			auto it=edges.find({o.u,o.v});if(it==edges.end())return 1;
			alive[it->second]=false;edges.erase(it);del(o.u,o.v);
		}else if(o.type==3){
			last_hash=query();
			if(last_hash<0||last_hash>=MOD)fail("hash out of range");
		}else if(o.type==4){
			if(last_type!=3||++paths>10)return 1;
			auto s=query_path();
			if(s.size()>edges.size())fail("too many edge IDs");
			int hash=0;
			for(int i:s){
				if(i<1||i>serial||!alive[i])fail("nonexistent edge ID");
				if(seen[i]==paths)fail("duplicate edge ID");
				seen[i]=paths;hash=(hash+pw[i])%MOD;
			}
			if(hash!=last_hash)fail("hash does not match query");
			fill(balance.begin(),balance.end(),0);
			for(int i=1;i<=serial;i++)if(alive[i]){
				int d=seen[i]==paths?1:-1;
				balance[u[i]]+=d;balance[v[i]]-=d;
			}
			for(int x=1;x<=n;x++)if(balance[x])fail("indegree differs from outdegree");
		}else return 1;
		last_type=o.type;
	}
	// Local grader: no private token.
	puts("AC");
}
