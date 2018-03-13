#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("warehouse.in","w",stdout);
	srand(time(0));
	int n=10,m=5;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<n;i++) printf("%d %d %d\n",rand()%i+1,i+1,rand()%5+1);
	return 0;
}