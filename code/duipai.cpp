// created time: 2026-06-01 08:18:17
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){
	int T=1000;
	// p16607
	assert(!system("g++ p16607.cpp -o p16607 -DLOCAL -fsanitize=address,undefined"));
	assert(!system("g++ brute.cpp -o brute -DLOCAL -fsanitize=address,undefined"));
	assert(!system("g++ gen.cpp -o gen -DLOCAL -fsanitize=address,undefined"));
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		assert(!system("./brute"));
		assert(!system("./p16607"));
		if(system("diff -Zq test.out test.ans")) {
			cout<<"WA on "<<i<<endl;
			exit(0);
		}
		cout<<"AC on "<<i<<endl;
	}
	return 0;
}