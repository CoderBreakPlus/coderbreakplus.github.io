#include "path.h"
#include <bits/stdc++.h>
using namespace std;
namespace {
const int MOD=998244353;
struct Operation { int type,u=0,v=0; };
using Key=unsigned long long;
Key key(int u,int v){if(u>v)swap(u,v);return (Key(u)<<32)|unsigned(v);}
[[noreturn]] void fail(const char *message){
    fprintf(stderr,"Wrong Answer: %s\n",message);
    puts("WA"); exit(0);
}
}
int main(){
    int n,q;
    if(scanf("%d%d",&n,&q)!=2)return 1;
    if(n<1||n>200000||q<1||q>200000)return 1;
    // Read all operations before calling contestant code, then close input.
    vector<Operation> ops(q);
    for(auto &op:ops){
        if(scanf("%d",&op.type)!=1)return 1;
        if(op.type==1||op.type==2)
            if(scanf("%d%d",&op.u,&op.v)!=2)return 1;
    }
    fclose(stdin);
    unordered_map<Key,int> edges;
    edges.reserve(q*2+1);
    vector<int> seen(q+1,0);
    int serial=0,stamp=0,last_hash=0,last_type=0,path_count=0;
    init(n,q);
    for(const auto &op:ops){
        if(op.type==1){
            edges.emplace(key(op.u,op.v),++serial);add(op.u,op.v);
        }else if(op.type==2){
            edges.erase(key(op.u,op.v));del(op.u,op.v);
        }else if(op.type==3){
            last_hash=query();
            if(last_hash<0||last_hash>=MOD)fail("hash out of range");
        }else if(op.type==4){
            if(last_type!=3||++path_count>10)return 1;
            vector<int> path=query_path();
            if(path.size()!=edges.size()+1||path.empty())fail("wrong path length");
            if(path.front()!=path.back())fail("path is not closed");
            ++stamp;
            long long hash=0,power=1;
            for(size_t i=0;i<path.size();i++){
                int v=path[i];
                if(v<1||v>n)fail("vertex out of range");
                hash=(hash+v*power)%MOD;power=power*100%MOD;
                if(i){
                    auto it=edges.find(key(path[i-1],v));
                    if(it==edges.end())fail("nonexistent edge");
                    if(seen[it->second]==stamp)fail("repeated edge");
                    seen[it->second]=stamp;
                }
            }
            if(hash!=last_hash)fail("hash does not match query");
        }else return 1;
        last_type=op.type;
    }
    // The online version emits its private UOJ token only after all checks.
    // No private token in the public local grader.
    puts("AC");
}
