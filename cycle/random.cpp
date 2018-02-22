#include <iostream>
#include <ctime>
using namespace std;

int a[30];

int main(){
	freopen("cycle.in","w",stdout);
	srand(time(0));
	int n=rand()%10+1;
	for(int i=1;i<=n;i++) a[i]=rand()%6;
	a[rand()%n+1]=0;
	cout<<n<<endl;
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}