#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 1000;
	while(T--){
		system("./gen");
		system("./qoj8085");
		system("./std");
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA\n";exit(0);
		}else
			cout<<"AC\n";
	}
}