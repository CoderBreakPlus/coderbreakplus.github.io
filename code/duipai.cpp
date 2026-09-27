#include<bits/stdc++.h>
using namespace std;

int main(){
	// int T = 1000;
	// while(T--){
	// 	system("./gen");
	// 	system("./cf1936d");
	// 	system("./brute");
	// 	if(system("diff -Zq test.out test.ans")){
	// 		cout<<"WA"<<endl;exit(0);
	// 	}else
	// 		cout<<"AC"<<endl;
	// }

	int T = 1000;
	while(T--){
		system("./gen");
		if(system("./cf1396e")){
			cout<<"WA"<<endl;exit(0);
		}else
			cout<<"AC"<<endl;
	}
}