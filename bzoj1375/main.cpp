#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 110
#define MAXM 610
#define ii pair<int,int>

struct edge
{
	int from,to,v1,v2;
}E[MAXM];

int ans,mi,n,m,s,t;
int edge_cnt,last[MAXN],ne[MAXM],f[MAXN][MAXN*100];
bool instack[MAXN][MAXN*100];

inline void add(int x,int y,int v1,int v2)
{
	E[++edge_cnt].from=x;
	E[edge_cnt].to=y;
	E[edge_cnt].v1=v1;
	E[edge_cnt].v2=v2;
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline void spfa()
{
	queue <ii> Q;
	Q.push(make_pair(s,0));
	memset(f,0x3f,sizeof(f));f[s][0]=0;instack[s][0]=true;
	while(!Q.empty())
	{
		ii p=Q.front();Q.pop();instack[p.first][p.second]=false;
		if(p.second>(n-1)*100) continue;
		for(int i=last[p.first];i;i=ne[i])
		{
			int v=E[i].to;
			if(f[v][E[i].v1+p.second]>f[p.first][p.second]+E[i].v2)
			{
				f[v][E[i].v1+p.second]=f[p.first][p.second]+E[i].v2;
				if(!instack[v][E[i].v1+p.second])
				{
					Q.push(make_pair(v,E[i].v1+p.second));
					instack[v][E[i].v1+p.second]=true;
				}
			}
		}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		static int x,y,v1,v2;
		scanf("%d %d %d %d",&x,&y,&v1,&v2);
		add(x,y,v1,v2);add(y,x,v1,v2);
	}
	spfa();mi=0x7fffffff;
	for(int i=0;i<=(n-1)*100;i++)
	{
		if(f[t][i]==0x3f3f3f3f)continue;
        if(f[t][i]>=mi)continue;
        mi=f[t][i];
        ans++;
	}
	cout<<ans;
	return 0;
}