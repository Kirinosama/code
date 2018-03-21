#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj3052.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,m=rand()%100000+1,q=rand()%100000+1;printf("%d %d %d\n",n,m,q);
	for(int i=1;i<=m;i++) printf("%d ",rand()%100000+1);cout<<endl;
	for(int i=1;i<=n;i++) printf("%d ",rand()%100000+1);cout<<endl;
	for(int i=1;i<n;i++) printf("%d %d\n",i+1,rand()%i+1);
	for(int i=1;i<=n;i++) printf("%d ",rand()%m+1);cout<<endl;
	for(int i=1;i<=q;i++){
		if(rand()%2){
			printf("1 %d %d\n",rand()%n+1,rand()%n+1);
		}else{
			printf("0 %d %d\n",rand()%n+1,rand()%m+1);
		}
	}
	return 0;
}