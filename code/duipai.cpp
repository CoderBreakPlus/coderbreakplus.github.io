#include<bits/stdc++.h>
using namespace std;

int main(){
	// int T = 100;
	// while(T--){
	// 	system("./gen");
	// 	system("./brute");
	// 	system("./soj2672");

	// 	if(system("diff -Zq test.out test.ans")){
	// 		cout<<"WA"<<endl;exit(0);
	// 	}else
	// 		cout<<"AC"<<endl;
	// }

	int T = 10000;
	for(int i=1;i<=T;i++){
		system("./gen");
		if(system("./soj2676")){
			cout<<"WA"<<endl;exit(0);
		}else
			cout<<"AC on "<<i<<endl;
	}
}