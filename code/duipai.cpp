#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 100;
	while(T--){
		system("./gen");
		system("./agc030e");
		system("./brute");
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA"<<endl;exit(0);
		}else
			cout<<"AC"<<endl;
	}

	// int T = 1000;
	// while(T--){
	// 	system("./gen");
	// 	if(system("./agc030e")){
	// 		cout<<"WA"<<endl;exit(0);
	// 	}else
	// 		cout<<"AC"<<endl;
	// }
}