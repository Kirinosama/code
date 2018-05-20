#include<bits/stdc++.h>
#define L long long
using namespace std;
int t;
L n;
inline L ran()
{
	return ((L)rand()<<45)+((L)rand()<<30)+(rand()<<15)+rand();
}
int main()
{
	freopen("number2.in","w",stdout);
	int i;
	t=10000;
	n=200000;
	printf("%d\n",t);
	for(i=1;i<=t;i++)
	  printf("%lld\n",ran()%n+1);
	return 0;
}
