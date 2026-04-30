#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 10000;
	// cf1609f
	assert(!system("g++ gen.cpp -o gen -DLOCAL"));
	cerr<<"compiled gen"<<endl;
	assert(!system("g++ brute.cpp -o brute -DLOCAL"));
	cerr<<"compiled brute"<<endl;
	assert(!system("g++ cf1609f.cpp -o cf1609f -DLOCAL"));
	cerr<<"compiled cf1609f"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		// cerr<<"gen"<<endl;
		assert(!system("./brute"));
		// cerr<<"brute"<<endl;
		assert(!system("./cf1609f"));
		// cerr<<"cf1609f"<<endl;
		if(system("diff -Zq test.out test.ans")){
			cerr<<"WA on "<<i<<endl;
			exit(0);
		}else cerr<<"AC on "<<i<<endl;
	}
	return 0;
}