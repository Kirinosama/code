#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj1316.in","w",stdout);
	srand(time(0));
	int n=rand()%10000+1,m=rand()%100+1;cout<<n<<' '<<m<<endl;
	for(int i=1;i<n;i++) printf("%d %d %d\n",i+1,rand()%i+1,rand()%1000001);
	for(int i=1;i<=m;i++) printf("%d\n",rand()%1000001);
	return 0;
}