#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100010
int n,m,a[MAXN],u,v,j;
set<pair<int,int> >S;
int flag;

int main()
{
	freopen("input","r",stdin);
	srand(529);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&u,&v);
		S.insert(pair<int,int>(u,v));
		S.insert(pair<int,int>(v,u));
	}
	for(int i=1;i<=300;i++)
	{
		for(int i=1;i<=n;i++)
			a[i]=i;
		random_shuffle(a+1,a+n+1);
		a[n+1]=a[1];
		for(j=1;j<=m;j++)
		{
			if(S.count(pair<int,int>(a[j],a[j+1])))
				break;
		}

		if(j==m+1)
		{
			for(j=1;j<=m;j++)
				printf("%d %d\n",a[j],a[j+1]);
			flag=1;

			break;
		}
	}
	if(!flag)
		printf("-1");
	return 0;
}