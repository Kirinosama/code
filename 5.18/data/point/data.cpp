#include<bits/stdc++.h>
#define L long long
using namespace std;
const int m=150,K=18;
int n,d,a,b;
inline int ran()
{
	return (rand()<<15)+rand();
}
int main()
{
	srand(time(0));
	ran();
	freopen("point1-3.in","w",stdout);
	int i,j,k;
	n=20;
	d=66;
	a=100001;
	b=30000;
	printf("%d %d %d %d\n",n,d,a,b);
	for(i=1;i<=n;i++)
	  printf("%d ",ran()%m+1);
	printf("\n");
	return 0;
}

