#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 210
#define P pair <double,double>

struct wuyao
{
	double x,y,r;
	int t;
	void in(){
		scanf("%lf %lf %lf %d",&x,&y,&r,&t);
	}
}yao[MAXN];

struct jingling
{
	double x,y;
	void in(){
		scanf("%lf %lf",&x,&y);
	}
}ling[MAXN];

struct shumu
{
	double x,y,r;
	void in(){
		scanf("%lf %lf %lf",&x,&y,&r);
	}
}shu[MAXN];

bool judge(P pos1,P pos2)
{
	double x1=pos1.first;
	double x2=pos2.first;
	double y1=pos1.second;
	double y2=pos2.second;
	if(x1==x2)
	{
		for(int i=1;i<=k;i++)
			if(fabs(x1-shu[i].x)<=shu[i].r)
				return false;
	}
	else if(y1==y2)
	{
		for(int i=1;i<=k;i++)
			if(fabs(y1-shu[i].y)<=shu[i].r)
				return false;
	}
	else
	{
		double k=(y2-y1)/(x2-x1);
		double b=y1-k*x1;
	}
}

void pre_make()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(judge(P(yao[i].x,yao[i].y),P(ling[j].x,ling[j].y))==true)
				dis[i][j]=1;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++) wu[i].in();
	for(int i=1;i<=m;i++) ling[i].in();
	for(int i=1;i<=k;i++) shu[i].in();
	pre_make();
	return 0;
}