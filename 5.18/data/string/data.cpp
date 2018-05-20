#include<bits/stdc++.h>
#define L long long
using namespace std;
int t,n;
inline L ran()
{
	return ((L)rand()<<45)+((L)rand()<<30)+(rand()<<15)+rand();
}
int main()
{
	freopen("string1.in","w",stdout);
	t=500;
	n=20;
	printf("%d\n",t);
	while(t--)
	  printf("%lld\n",ran()%n+1);
	return 0;
}
