#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 1000;
	while(T--){
		system("./gen");
		if(system("./cf1758f")){
			cout<<"WA\n";exit(0);
		}else
			cout<<"AC\n";
	}
}