#include<iostream>
#include<map>
#include<string>
using namespace std;
int n; string opt,add;
map<string, int>M;
bool isint(char st){
	if(st>='0'&&st<='9') return 1;
	return 0;
}
bool Hefa(string add){
	int now=0,tmp,len=add.size();
	tmp=0;
	if(!isint(add[now])) return 0;
	while(now<len && isint(add[now])){
		if(add[now]=='0' && tmp==0 && now+1<len && isint(add[now+1])) return 0;
		tmp=tmp*10+add[now]-'0';
		if(tmp>65535) return 0;
		now++;
	}
	if(!(tmp>=0 && tmp<=255)) return 0;
	if(now==len) return 0; // 读入一个数 
	if(add[now]!='.') return 0; now++;
	if(now==len) return 0; // 读入一个字符
	 
	tmp=0;
	if(!isint(add[now])) return 0;
	while(now<len && isint(add[now])){
		if(add[now]=='0' && tmp==0 && now+1<len && isint(add[now+1])) return 0;
		tmp=tmp*10+add[now]-'0';
		if(tmp>65535) return 0;
		now++;
	}
	if(!(tmp>=0 && tmp<=255)) return 0;
	if(now==len) return 0; // 读入一个数 
	if(add[now]!='.') return 0; now++;
	if(now==len) return 0; // 读入一个字符 
	
	tmp=0;
	if(!isint(add[now])) return 0;
	while(now<len && isint(add[now])){
		if(add[now]=='0' && tmp==0 && now+1<len && isint(add[now+1])) return 0;
		tmp=tmp*10+add[now]-'0';
		if(tmp>65535) return 0;
		now++;
	}
	if(!(tmp>=0 && tmp<=255)) return 0;
	if(now==len) return 0; // 读入一个数 
	if(add[now]!='.') return 0; now++;
	if(now==len) return 0; // 读入一个字符 
	
	tmp=0;
	if(!isint(add[now])) return 0;
	while(now<len && isint(add[now])){
		if(add[now]=='0' && tmp==0 && now+1<len && isint(add[now+1])) return 0;
		tmp=tmp*10+add[now]-'0';
		if(tmp>65535) return 0;
		now++;
	}
	if(!(tmp>=0 && tmp<=255)) return 0;
	if(now==len) return 0; // 读入一个数
	if(add[now]!=':') return 0; now++;
	if(now==len) return 0; // 读入一个字符 
	
	tmp=0;
	if(!isint(add[now])) return 0;
	while(now<len && isint(add[now])){
		if(add[now]=='0' && tmp==0 && now+1<len && isint(add[now+1])) return 0;
		tmp=tmp*10+add[now]-'0';
		if(tmp>65535) return 0;
		now++;
	}
	if(now!=len) return 0; 
	if(!(tmp>=0 && tmp<=65535)) return 0;
	
	return 1;
}
int main(){
//	freopen("network.in","r",stdin);
//	freopen("network.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>opt>>add;
		if(!Hefa(add)){
			cout<<"ERR"<<endl;
			continue;
		}
		if(opt=="Server"){
			if(M.count(add)) cout<<"FAIL"<<endl;
			else{
				M[add]=i;
				cout<<"OK"<<endl;
			}
		}else{
			if(M.count(add)) cout<<M[add]<<endl;
			else cout<<"FAIL"<<endl;
		}
	}
	
	return 0;
}
