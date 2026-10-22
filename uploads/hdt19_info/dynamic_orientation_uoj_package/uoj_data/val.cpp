// Standalone validator: stdin is a test, exit 0 means valid; no testlib needed.
#include <bits/stdc++.h>
using namespace std;
[[noreturn]] void fail(int line,const string &why){
	cerr<<"Invalid input at line "<<line<<": "<<why<<'\n';exit(1);
}
vector<long long> read_line(int line){
	string s;if(!getline(cin,s))fail(line,"unexpected EOF");
	istringstream in(s);vector<long long>a;string token;
	while(in>>token){
		long long x;auto result=from_chars(token.data(),token.data()+token.size(),x);
		if(result.ec!=errc()||result.ptr!=token.data()+token.size())fail(line,"invalid integer");
		a.push_back(x);
	}
	return a;
}
int main(int argc,char **argv){
	ios::sync_with_stdio(false);cin.tie(nullptr);
	int limit=200000;
	if(argc==2)limit=atoi(argv[1]);
	auto h=read_line(1);
	if(h.size()!=2||h[0]<1||h[0]>limit||h[1]<1||h[1]>limit)fail(1,"n/q out of range");
	int n=h[0],q=h[1],odd=0,paths=0,last=0;
	vector<int>degree(n+1);set<pair<int,int>>edges;
	for(int j=1;j<=q;j++){
		auto a=read_line(j+1);
		if(a.empty()||a[0]<1||a[0]>4)fail(j+1,"invalid operation");
		int op=a[0];
		if(op<=2){
			if(a.size()!=3||a[1]<1||a[1]>=a[2]||a[2]>n)fail(j+1,"invalid endpoints");
			int u=a[1],v=a[2];
			if(op==1){if(!edges.insert({u,v}).second)fail(j+1,"duplicate addition");}
			else if(!edges.erase({u,v}))fail(j+1,"deleting missing edge");
			for(int x:{u,v}){odd-=degree[x]&1;degree[x]+=op==1?1:-1;odd+=degree[x]&1;}
		}else{
			if(a.size()!=1)fail(j+1,"too many fields");
			if(op==3&&odd)fail(j+1,"odd degree at query");
			if(op==4&&(last!=3||++paths>10))fail(j+1,"invalid follow-up");
		}
		last=op;
	}
	string rest;while(getline(cin,rest))if(rest.find_first_not_of(" \t\r")==string::npos)continue;else fail(q+2,"trailing data");
}
