#include<bits/stdc++.h>
using namespace std;
int cid;
const int B=9;
struct Basis{
	int v[B];
	Basis(){ memset(v,0,sizeof(v)); }
	bool ins(int x){
		for(int i=0;i<B;i++){
			if((x>>i)&1)continue;
			if(!v[i]){v[i]=x;return 1;}
			else x^=v[i];
		}
		return 0;
	}
}W;
vector<int>st;
bool vis[505],le;

string init(int subtask,int n,vector<int> p){
	cid=subtask;
	W=Basis(),le=0;

	int all=0;
	for(int i=n;i>=1;i--){
		vis[p[i]]=W.ins(p[i]);
		if(vis[i])all^=p[i],st.push_back(p[i]);
	}

	string ret;
	for(int i=0;i<B;i++)
		ret.push_back('0'+(all>>i&1));
	return ret;
}
bool receive_fruit(int id,bool is_lemon){
	if(is_lemon){
		if(vis[id]) return 0;
		for(int i=0;i<(1<<st.size());i++){
			int fuck=0;
			for(int j=0;j<st.size();j++)
				if((i>>j)&1) fuck^=st[j];
			if(fuck==id){
				for(int j=0;j<st.size();j++)
					if((i>>j)&1) vis[st[j]]=0;
				break;
			}
		}
		return 0;
	}else if(!le){
		if(vis[id]) st.pop_back();
		return vis[id];
	}else{
		return vis[id];
	}
}
int answer(int subtask, int n, std::string b, std::vector<int> uneaten){
	int tot=0;
	for(int i=0;i<B;i++)
		if(b[i]=='1')tot^=(1<<i);

	for(int i=1;i<=n;i++) tot^=i;
	for(int x:uneaten) tot^=x;
	return tot;
}