// created time: 2026-06-15 10:22:39
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T = 1000;
	assert(!system("g++ C.cpp -o C -DLOCAL"));
	assert(!system("g++ bruteC.cpp -o bruteC -DLOCAL"));
	assert(!system("g++ gen.cpp -o gen -DLOCAL"));
	cout<<"Compiled"<<endl;
	for(int i=1;i<=T;i++){
		assert(!system("./gen"));
		assert(!system("./bruteC"));
		assert(!system("./C"));
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA on "<<i<<endl;
			exit(0);
		}else
			cout<<"AC on "<<i<<endl;
	}
}