#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXE 400010
#define MAXN 200010

struct node
{
	int u,v,w;
}E[MAXE];

vector <int> son[MAXN];
vector <int> down[MAXN];
vector <int> car_member[MAXN];
int up[MAXN];
int car[MAXN];

bool operator < (const node &a,const node &b)
{
	return a.w<b.w;
}

int n,m;
int father[MAXN];

int find(int x)
{
	if(father[x]!=x)
		return find(father[x]);
	else
		return x;
}

void kruskal()
{
	int cnt=0;
	int res=0;
	for(int i=1;i<=n;i++)
	{
		father[i]=i;
		car[i]=i;
		car_member[i].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		int fx=find(E[i].u);
		int fy=find(E[i].v);
		if(fx>fy)
			swap(fx,fy);
		if(fx!=fy)
		{
			father[fx]=fy;
			cnt++;
			res+=E[i].w;
			son[E[i].u].push_back(E[i].v);
			son[E[i].v].push_back(E[i].u);
		}
		if(cnt==n-1)
		{
			printf("%d\n",res);
			return;
		}
	}
}

void build(int x,int fa)
{
	up[x]=fa;
	for(int i=0;i<son[x].size();i++)
		if(son[x][i]!=fa)
		{
			down[x].push_back(son[x][i]);
			build(son[x][i],x);
		}
}

void solve(int x)
{
	for(int i=0;i<down[x].size();i++)
	{
		solve(down[x][i]);
		int from=down[x][i];
		printf("Drive %d %d %d\n",car[from],from,x);
		if(car_member[car[from]].size()>car_member[car[x]].size())
			swap(car[from],car[x]);
		while(!car_member[car[from]].empty())
		{
			car_member[car[x]].push_back(car_member[car[from]].back());
			printf("Move %d %d %d\n",car_member[car[from]].back(),car[from],car[x]);
			car_member[car[from]].pop_back();
		}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&E[i].u,&E[i].v,&E[i].w);
		if(E[i].u>E[i].v)
			swap(E[i].u,E[i].v);
	}
	sort(E+1,E+m+1);
	kruskal();
	build(1,0);
	solve(1);
	cout<<"Done";
//	for(int i=1;i<=n;i++)
//		printf("%d ",up[i]);
	return 0;
}