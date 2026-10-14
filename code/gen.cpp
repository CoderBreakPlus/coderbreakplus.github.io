#include<bits/stdc++.h>
using namespace std;
// ./gen [seed] [T=200] [maxn=10] [maxwild=3]
int main(int argc,char **argv){
	unsigned long long seed=argc>1?stoull(argv[1]):chrono::steady_clock::now().time_since_epoch().count();
	int T=argc>2?stoi(argv[2]):10;
	int N=argc>3?stoi(argv[3]):10;
	int W=argc>4?stoi(argv[4]):3;
	if(T<1||T>500000||N<1||N>20||W<0){cerr<<"invalid arguments\n";return 1;}
	mt19937_64 rng(seed);
	auto rnd=[&](int l,int r){return uniform_int_distribution<int>(l,r)(rng);};
	freopen("test.in","w",stdout);
	cout<<T<<'\n';
	while(T--){
		int n=rnd(1,N),w=min(n,W),x=rnd(0,w),y=rnd(0,w),mode=rnd(0,7);
		string a(n,'0');
		for(int i=0;i<n;i++){
			if(mode==0)a[i]='0';
			else if(mode==1)a[i]='1';
			else if(mode==2||mode==3)a[i]='0'+((i+mode)&1);
			else if(mode==4)a[i]='0'+(i>=n/2);
			else if(mode==5)a[i]='0'+(i<n/2);
			else a[i]='0'+rnd(0,1);
		}
		if(rnd(0,3)==0)x=y=0;
		cout<<n<<' '<<x<<' '<<y<<'\n'<<a<<'\n';
	}
	cerr<<"seed="<<seed<<'\n';
}
