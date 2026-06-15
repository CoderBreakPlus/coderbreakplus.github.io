// created time: 2026-06-15 10:22:39
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T = 1000;
	assert(!system("g++ I.cpp -o I -DLOCAL"));
	assert(!system("g++ brute.cpp -o brute -DLOCAL"));
	assert(!system("g++ gen.cpp -o gen -DLOCAL"));
	cout<<"Compiled"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		assert(!system("./brute"));
		assert(!system("./I"));
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA on "<<i<<endl;
			exit(0);
		}else
			cout<<"AC on "<<i<<endl;
	}
}