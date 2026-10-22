#include "std.cpp"
using namespace std;
map<pair<int,int>,int> active;
int deg[30],serial,checks;
void check(int n){
	auto s=query_path();set<int> ids(s.begin(),s.end());
	assert(ids.size()==s.size());
	int bal[30]={};long long h=0;
	for(auto [e,i]:active){
		int d=ids.erase(i)?1:-1;
		bal[e.first]+=d;bal[e.second]-=d;
		if(d==1)h=(h+Orientation::pw[i])%Orientation::mod;
	}
	assert(ids.empty());assert(h==query());
	for(int v=1;v<=n;v++)assert(abs(bal[v])==(deg[v]&1));
	++checks;
}
void toggle(int u,int v){
	if(u>v)swap(u,v);
	auto e=make_pair(u,v);auto it=active.find(e);
	if(it==active.end()){active[e]=++serial;add(u,v,serial);++deg[u];++deg[v];}
	else{active.erase(it);del(u,v);--deg[u];--deg[v];}
}
void start(int n,int q,int seed){init(n,q);Orientation::rng.seed(seed);active.clear();serial=0;fill(deg,deg+30,0);}
int main(){
	start(6,40000,1);vector<pair<int,int>>es;
	for(int i=1;i<=6;i++)for(int j=i+1;j<=6;j++)es.push_back({i,j});
	check(6);
	for(int i=1;i<(1<<15);i++){auto [u,v]=es[__builtin_ctz(i)];toggle(u,v);check(6);}
	for(int seed=0;seed<8;seed++){
		start(20,40000,seed);mt19937 gen(seed+1000);
		for(int k=0;k<30000;k++){
			int u=gen()%20+1,v=gen()%19+1;if(v>=u)v++;
			toggle(u,v);check(20);
		}
	}
	cout<<"PASS "<<checks<<" states: hash, edge membership, degree balance\n";
}
