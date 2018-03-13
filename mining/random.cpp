#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("mining.in","w",stdout);
	srand(time(0));
	int n=10,m=100;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++) printf("%d %d\n",rand()%10+1,rand()%m+1);
	return 0;
}