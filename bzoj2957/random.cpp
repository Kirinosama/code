#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj2957.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,m=rand()%100000+1;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=m;i++){
		int x=rand()%n+1;
		int y=rand()%1000000000+1;
		cout<<x<<' '<<y<<endl;
	}
	return 0;
}