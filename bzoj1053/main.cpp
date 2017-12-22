#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <ctime>
#include <queue>
#include <cmath>
#include <algorithm>

#define INF 1000000000
#define ll long long
using namespace std;


int n,L,mid;

struct node
{
	int x[20005],y[20005],top;
}a,b;

void cut(node &a,int x1,int y1,int x2,int y2)
{
	int tot=0;
	for(int i=1;i<=a.top;i++)
		if(a.x[i]<x1||a.x[i]>x2||a.y[i]<y1||a.y[i]>y2)
		{
			tot++;
			a.x[tot]=a.x[i];
			a.y[tot]=a.y[i];
		}
	a.top=tot;
} 
void solve(node &a,int fc)
{
	int x1=INF,y1=INF,x2=-INF,y2=-INF;
	for(int i=1;i<=a.top;i++)
	{
		x1=min(a.x[i],x1),x2=max(a.x[i],x2);
		y1=min(a.y[i],y1),y2=max(a.y[i],y2);
	}
	if(fc==1)
		cut(a,x1,y1,x1+mid,y1+mid);
	if(fc==2)
		cut(a,x2-mid,y1,x2,y1+mid);
	if(fc==3)
		cut(a,x1,y2-mid,x1+mid,y2);
	if(fc==4)
		cut(a,x2-mid,y2-mid,x2,y2);
}
bool jud()
{
	node b;
	for(int x=1;x<=4;x++)
		for(int y=1;y<=4;y++)
		{
			b.top=a.top;
			for(int i=1;i<=b.top;i++)
				b.x[i]=a.x[i],b.y[i]=a.y[i];
			solve(b,x);
			solve(b,y);
		    int x1=INF,y1=INF,x2=-INF,y2=-INF;
			for(int i=1;i<=b.top;i++)
			{
				x1=min(b.x[i],x1),x2=max(b.x[i],x2);
				y1=min(b.y[i],y1),y2=max(b.y[i],y2);
			}
			if(x2-x1<=mid&&y2-y1<=mid)
				return 1;
		}
	return 0;
}
int main()
{
	scanf("%d",&n);
	a.top=n;
	for(int i=1;i<=a.top;i++)
	scanf("%d %d",&a.x[i],&a.y[i]);
	int l=1,r=INF;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(jud())
			L=mid,r=mid-1;
		else
			l=mid+1;
	}
	printf("%d\n",L);
	return 0;
}