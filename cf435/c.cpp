#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int st,x,n;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&x);
	if(n==1)
	{
		printf("YES\n%d",x);
		return 0;
	}
	if(n==2)
	{
		if(x==0) printf("NO");
		else printf("YES\n%d 0",x);
		return 0;
	}
	int p=(n-1)>>1;
	int rem=n-1-p*2;
	if(p&1) st=x^1;
	else st=x;
	if(st==0 && rem)
	{
		printf("YES\n");p--;
		printf("%d 30000 40000 59760 ",st);
		for(int i=1;i<=p;i++) printf("%d %d ",i*2,i*2+1);
	}
	else
	{
		printf("YES\n");
		printf("%d ",st);
		if(rem) printf("0 ");
		for(int i=1;i<=p;i++) printf("%d %d ",i*2+13000,i*2+13001);
	}
	return 0;
}