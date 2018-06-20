#include <bits/stdc++.h>
using namespace std;

int main(){
	srand(time(0));
	freopen("function.in","w",stdout);
	int n=100000;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)printf("%d ",rand()%1000000001);
	cout<<endl<<100000<<endl;
	for(int i=1;i<=100000;i++){
		printf("%d %d\n",rand()%100000+1,rand()%n+1);
	}
}
