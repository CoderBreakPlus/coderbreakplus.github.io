// created time: 2026-07-13 14:47:02
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 10000;
	for(int i=1;i<=T;i++){
		system("./gen");
		system("./brute");
		system("./arc223e");

		if(system("diff -Zq test.out test.ans")){
			cout<<"WA on "<<i<<endl;exit(0);
		}else
			cout<<"AC on "<<i<<endl;
	}
}