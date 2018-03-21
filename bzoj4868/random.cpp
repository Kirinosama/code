#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj4868.in","w",stdout);
	srand(time(0));
	int A=rand()%100001,B=rand()%100001;long long C=1e16;
	int n=rand()%100000+1,m=rand()%100000+1;
	printf("%d %d %lld\n%d %d\n",A,B,C,n,m);
	for(int i=1;i<=n;i++)printf("%d ",rand()%100000+1);
	cout<<endl;
	for(int i=1;i<=m;i++)printf("%d ",rand()%100000+1);
	return 0;
}