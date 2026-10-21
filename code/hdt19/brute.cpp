#include<bits/stdc++.h>
#include"path.h"
#ifdef LOCAL
#include"grader.cpp"
#endif
using namespace std;

const int N = 1005;
const int mod = 998244353;
#define pb emplace_back
namespace brute{
	int n;
	set<int>S[N+5],E[N+5];

	void init(int N,int Q){ n=N; }
	void add(int x,int y){ S[x].emplace(y),S[y].emplace(x); }
	void del(int x,int y){ S[x].erase(y),S[y].erase(x); }

	vector<int>seq;

	void dfs(int x){
		while(!E[x].empty()){
			int y=*E[x].begin();
			E[x].erase(y),E[y].erase(x);
			dfs(y);
		}
		seq.pb(x);
	}
	int query(){
		seq.clear();
		for(int i=1;i<=n;i++) E[i]=S[i];
		dfs(1);

		int ret=0;
		for(int i=seq.size()-1;i>=0;i--)
			ret=(ret*100ull+seq[i])%mod;
		return ret;
	}
	vector<int> query_path(){
		return seq;
	}
}
void init(int n,int q){ assert(n<=1000&&q<=1000); return brute::init(n,q); }
void add(int x,int y){ return brute::add(x,y); }
void del(int x,int y){ return brute::del(x,y); }
int query(){ return brute::query(); }
vector<int> query_path(){ return brute::query_path(); }