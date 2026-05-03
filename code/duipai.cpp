#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 10000;
	// soj2560
	assert(!system("g++ gen.cpp -o gen"));
	cerr<<"compiled gen"<<endl;
	assert(!system("g++ brute.cpp grader.cpp -o brute"));
	cerr<<"compiled brute"<<endl;
	assert(!system("g++ soj2560.cpp grader.cpp -o soj2560"));
	cerr<<"compiled soj2560"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen >test.in"));
		// cerr<<"gen"<<endl;
		assert(!system("./brute <test.in >test.out"));
		// cerr<<"brute"<<endl;
		assert(!system("./soj2560 <test.in >test.ans"));
		// cerr<<"soj2560"<<endl;
		if(system("diff -Zq test.out test.ans")){
			cerr<<"WA on "<<i<<endl;
			exit(0);
		}else cerr<<"AC on "<<i<<endl;
	}
	return 0;
}