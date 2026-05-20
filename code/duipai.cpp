#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 10000;
	// cf1332g
	assert(!system("g++ gen.cpp -o gen -DLOCAL"));
	cerr<<"compiled gen"<<endl;
	assert(!system("g++ brute.cpp -o brute -DLOCAL"));
	cerr<<"compiled brute"<<endl;
	assert(!system("g++ cf1332g.cpp -o cf1332g -DLOCAL"));
	cerr<<"compiled cf1332g"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		cerr<<"gen"<<endl;
		assert(!system("./brute"));
		cerr<<"brute"<<endl;
		assert(!system("./cf1332g"));
		cerr<<"cf1332g"<<endl;
		if(system("diff -Zq test.out test.ans")){
			cerr<<"WA on "<<i<<endl;
			exit(0);
		}else cerr<<"AC on "<<i<<endl;
	}
	return 0;
}