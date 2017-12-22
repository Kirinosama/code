#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010 
#define MAXM 10010
#define ii pair<int,int>

struct node
{
	int x,g,h;
	node(int x_,int g_,int h_){
		x=x_,g=g_,h=h_;
	}
	bool operator <(node a)const{
		return g+h>a.g+a.h;
	}
};

vector <ii> E1[MAXN];
vector <ii> E2[MAXN];
int n,m,k,s,t,dis[MAXN],cnt[MAXN],ans[MAXM];
bool instack[MAXN];

void spfa()
{
	queue <int> Q;
	memset(dis,0x7f,sizeof(dis));
	Q.push(t);dis[t]=0;instack[t]=true;
	while(!Q.empty())
	{
		int x=Q.front();Q.pop();instack[x]=false;
		for(int i=0;i<E2[x].size();i++)
		{
			int to=E2[x][i].first;
			if(dis[x]+E2[x][i].second<dis[to])
			{
				dis[to]=dis[x]+E2[x][i].second;
				if(!instack[to])
					instack[to]=true,Q.push(to);
			}
		}
	}
}

void Astar()
{
	priority_queue <node> Q;
	Q.push(node(s,0,dis[s]));
	memset(cnt,0,sizeof(cnt));
	while(!Q.empty())
	{
		node cur=Q.top();Q.pop();
		int x=cur.x;int g=cur.g;int h=cur.h;
		cnt[x]++;
		if(x==t) ans[cnt[x]]=g;
		if(cnt[x]<=k)
		{
			for(int i=0;i<E1[x].size();i++)
			{
				int to=E1[x][i].first;
				Q.push(node(to,g+E1[x][i].second,dis[to]));
			}
		}
	}
	for(int i=1;i<=k;i++) printf("%d\n",ans[i] ? ans[i] : -1);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		static int x,y,v;
		scanf("%d %d %d",&x,&y,&v);
		E1[y].push_back(ii(x,v));
		E2[x].push_back(ii(y,v));
	}
	s=1;t=n;
	spfa();
	Astar();
	return 0;
}