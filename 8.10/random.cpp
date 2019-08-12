#include <bits/stdc++.h>
using namespace std;

int book[6010];

int main(){
	srand(time(0));
	//freopen("a.in","w",stdout);
	int n=100;
	int m=60;
	int p=1000;
	printf("%d %d %d\n",n,m,p);
	for(int i=1;i<=n;i++){
		printf("%d %d\n",rand()%20+1,rand()%20001-10000);
	}
	return 0;
}
