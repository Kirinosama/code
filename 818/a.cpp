#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,m,book[100],a;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&a);
		book[a-'a'+1]++;
	}
	for(int i=1;i<=26;i++)
	{
		if(book[i]>m) 
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}