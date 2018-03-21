#include <iostream>
#include <ctime>
using namespace std;

int a[3000010];

int main(){
	freopen("bzoj3631.in","w",stdout);
	srand(time(0));
	int n=rand()%3000000+1;cout<<n<<endl;
	for(int i=1;i<=n;i++)a[i]=i;
	random_shuffle(a+1,a+n+1);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	cout<<endl;
	for(int i=1;i<=n;i++) printf("%d %d\n",rand()%i+1,i+1);
	return 0;
}