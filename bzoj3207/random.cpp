#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj3207.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,m=rand()%100000+1,k=rand()%20+1;
	printf("%d  %d %d\n",n,m,k);
	for(int i=1;i<=n;i++) printf("%d ",rand()%2000000000+1);cout<<endl;
	for(int i=1;i<=m;i++){
		int l=rand()%(n-k)+1;
		int r=rand()%(n-(l+k-1))+l+k-1;
		printf("%d %d ",l,r);
		for(int j=1;j<=k;j++) printf("%d ",rand()%2000000000+1);cout<<endl;
	}
	return 0;
}