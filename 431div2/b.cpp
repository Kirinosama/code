#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const double eps=1e-8;
const int INF=0x3f3f3f3f;
#define MAXN 1010

struct node
{
	double x,y;
}p[MAXN];

int n,book[MAXN],book1[MAXN];

bool judge(node a,node b)
{
	double k=(b.y-a.y)/(b.x-a.x);
	double t=b.y-b.x*k;
	int cnt=0;
	node p1=(node){-1.0,0};
	node p2=(node){-1.0,0};
	memset(book,0,sizeof(book));
	memset(book1,0,sizeof(book1));
	for(int i=1;i<=n;i++)
	{
		if(fabs(p[i].x*k+t-p[i].y)<eps)
			book[i]=1;
		else cnt++;
	}
	if(cnt==0) return false;
	else if(cnt==1) return true;
	else
	{
		for(int i=1;i<=n;i++)
			if(!book[i])
			{
				if(p1.x==-1.0) p1=p[i];
				else p2=p[i];
			}
		double k1=(p2.y-p1.y)/(p2.x-p1.x);
		double t1=p2.y-p2.x/k1;

		if(fabs(k1-k)>eps) return false;

		for(int i=1;i<=n;i++)
			if(fabs(p[i].x*k1+t1-p[i].y)<eps)
			{
				book1[i]=1;
				if(book1[i]+book[i]!=1) return false;
			}
	}
	return true;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{ 
		scanf("%lf",&p[i].y);
		p[i].x=(double)i;
	}
	if(judge(p[1],p[2]) || judge(p[1],p[3]) || judge(p[2],p[3]))
		printf("Yes");
	else printf("No");
	return 0;
}