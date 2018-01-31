#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj2908.in","w",stdout);
	srand(time(0));
	int n=rand()%10000+1;
	int m=rand()%10000+1;
	int k=30;
	printf("%d %d %d\n",n,m,k);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%(1<<k));
	cout<<endl;
	for(int i=1;i<n;i++)
		printf("%d %d\n",rand()%i+1,i+1);
	for(int i=1;i<=m;i++){
		int c=rand()%2;
		if(!c) printf("Replace %d %d\n",rand()%n+1,rand()%(1<<k));
		else printf("Query %d %d\n",rand()%n+1,rand()%n+1);
	}
	return 0;
}