// created time: 2026-09-17 11:10:46
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
bool check(int x,int y,int z){
	int a=x*y/__gcd(x,y),b=y*z/__gcd(y,z),c=z*x/__gcd(x,z);
	if(__gcd(a,b)!=y||__gcd(b,c)!=z||__gcd(a,c)!=x) return false;
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	int _;cin>>_;
	while(_--){
		vector<array<int,3> > ans;
		int n;cin>>n;
		if(n<=20){
			vector<int> p;
			for(int i=1;i<=n;i++) p.push_back(i);
			while(1){
				shuffle(p.begin(),p.end(),rnd);
				bool flag=true;
				for(int i=n-1;i%3!=2;i--) if(2*p[i]>n) flag=false;
				for(int i=0;i+2<n;i+=3) if(!check(p[i],p[i+1],p[i+2])){
					flag=false;
					break;
				}
				if(flag){
					cout<<n/3<<'\n';
					for(int i=0;i+2<n;i+=3) cout<<p[i]<<" "<<p[i+1]<<" "<<p[i+2]<<'\n';
					break;
				}
			}
			continue;
		}
		if(n%4==3) ans.push_back({n-2,n-1,n}),n-=3;
		if(n%4==0) ans.push_back({1,n-1,n}),n-=2;
		for(int i=(n-1)/4*4+1;i*2>n;i-=4){
			ans.push_back({i-2,i-1,i});
		}
		for(int i=(n-2)/4*4+2;i*2>n;i-=12){
			ans.push_back({i-8,i-4,i});
		}
		cout<<ans.size()<<'\n';
		for(auto i:ans) cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<'\n';
	}
	return 0;
}
