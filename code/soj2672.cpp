#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
int n,own[2];
unordered_map<ull,bool> memo;
bool dfs(int mask,int x,int y,int turn,int last){
	if(!(mask&own[turn])&&!(turn?y:x))return true;
	if(!(mask&own[turn^1])&&!(turn?x:y))return false;
	ull key=mask;
	key=key*21+x;key=key*21+y;
	key=key*(n+2)+last+1;key=key*2+turn;
	auto it=memo.find(key);
	if(it!=memo.end())return it->second;
	bool win=false;
	if(last!=-1&&!dfs(mask,x,y,turn^1,-1))win=true;
	int cards=mask&own[turn];
	if(last!=-1)cards=last+1<n?(cards&(1<<(last+1))):0;
	for(int s=cards;s&&!win;s&=s-1){
		int i=__builtin_ctz((unsigned)s);
		if(!dfs(mask^(1<<i),x,y,turn^1,i))win=true;
	}
	if(!win&&(turn?y:x)&&last!=n){
		if(!dfs(mask,x-(turn==0),y-(turn==1),turn^1,n))win=true;
	}
	return memo[key]=win;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios::sync_with_stdio(false);cin.tie(nullptr);
	int T;cin>>T;
	while(T--){
		int x,y;string a;cin>>n>>x>>y>>a;
		own[0]=own[1]=0;
		for(int i=0;i<n;i++)own[a[i]-'0']|=1<<i;
		memo.clear();
		cout<<(dfs((1<<n)-1,x,y,0,-1)?"Alice":"Bob")<<'\n';
	}
}
