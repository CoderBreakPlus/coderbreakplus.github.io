#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 1000;
	while(T--){
		system("./gen");
		system("./g");
		system("./brute");
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA"<<endl;exit(0);
		}else
			cout<<"AC"<<endl;
	}
}