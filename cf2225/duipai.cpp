#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 10000;
	// D
	assert(!system("g++ gen.cpp -o gen -DLOCAL"));
	cerr<<"compiled gen"<<endl;
	assert(!system("g++ brute.cpp -o brute -DLOCAL"));
	cerr<<"compiled brute"<<endl;
	assert(!system("g++ D.cpp -o D -DLOCAL"));
	cerr<<"compiled D"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		// cerr<<"gen"<<endl;
		assert(!system("./brute"));
		// cerr<<"brute"<<endl;
		assert(!system("./D"));
		// cerr<<"D"<<endl;
		if(system("diff -Zq test.out test.ans")){
			cerr<<"WA on "<<i<<endl;
			exit(0);
		}else cerr<<"AC on "<<i<<endl;
	}
	return 0;
}