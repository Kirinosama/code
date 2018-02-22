#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("game.in","w",stdout);
	srand(time(0));
	int T=rand()%10+1;
	while(T--){
		int n=rand()%100+1,m=rand()%100+1;
		printf("%d %d\n",n,m);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) printf("%c",rand()%2?'@':'#');
			cout<<endl;
		}
		printf("%d %d %d %d\n",rand()%n,rand()%m,rand()%n,rand()%m);
	}
	cout<<"0 0";
	return 0;
}