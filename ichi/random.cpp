#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){
	freopen("ichi.in","w",stdout);
	srand(time(0));
	int n=100000,m=100000,ty=0;cout<<n<<' '<<m<<' '<<ty<<endl; 
	for(int i=1;i<=n;i++)cout<<rand()%100001<<' ';
	cout<<endl;
	for(int i=1;i<n;i++)printf("%d %d %d\n",rand()%i+1,i+1,rand()%100000+1);
	for(int i=1;i<=m;i++){
		int opt=rand()%10;
		if(opt<0){
			cout<<1<<' '<<rand()%n+1<<endl;
		}else{
			cout<<2<<' '<<rand()%100000+1<<' '<<rand()%50000+1<<' '<<rand()%n+1<<endl;
		}
	}
	return 0;
}
