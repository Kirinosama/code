#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	freopen("point.in","w",stdout);
	srand(time(0));
	int n=12;cout<<n<<endl;
	for(int i=1;i<=n;i++){
		int t=rand()%20+1;int d=rand()%30+1;
		int a=rand()%1000000+1,b=a+1;
		printf("%d %d %d %d\n",t,d,a,b);
		for(int i=1;i<=t;i++)printf("%d ",rand()%150+1);
		cout<<endl;
	}
	return 0;
}
