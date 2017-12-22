#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 1010
const double eps=1e-8;

struct node
{
	double x,y;
	void in(){
		scanf("%lf %lf",&x,&y);
	}
}p[MAXN];

int n,k,cnt,father[MAXN];
double dist[MAXN*MAXN],ans;

double dis(node a,node b)
{
	return (double)sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

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

int solve(double cur)
{
	int res=0;
	for(int i=1;i<=n;i++) father[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(dis(p[i],p[j])<cur-eps)
				merge(i,j);
	for(int i=1;i<=n;i++) 
		if(father[i]==i)
			res++;
	return res;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) p[i].in();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			dist[++cnt]=dis(p[i],p[j]);
	sort(dist+1,dist+1+cnt);
	int l=1,r=cnt;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		double cur=dist[mid];
	//	cout<<cur<<endl;
		if(solve(cur)>=k)
		{
			ans=max(ans,cur);
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%.2f",ans);
	return 0;
}