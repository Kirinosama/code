#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010

struct node
{
	int val,pos;
	bool operator < (node a)
	const{
		return val<a.val;
	}
}p[MAXN];

int n,father[MAXN],ans;
vector <int> s[MAXN];

int find(int x)
{
	if(father[x]!=x) father[x]=find(father[x]);
	return father[x];
}

void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy) father[fx]=fy;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i].val);
		p[i].pos=i;
	}
	sort(p+1,p+1+n);
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=n;i++)
	{
		merge(i,p[i].pos);
	}
	for(int i=1;i<=n;i++)
	{
		if(father[i]==i) ans++;
		s[find(i)].push_back(i);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		if(father[i]==i)
		{
			printf("%d ",(int)s[i].size());
			for(int j=0;j<s[i].size();j++)	
				printf("%d ",s[i][j]);
			printf("\n");
		}
	}
	return 0;
}