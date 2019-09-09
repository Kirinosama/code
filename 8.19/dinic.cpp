#include <bits/stdc++.h>
using namespace std;

struct edge
{
	int x,y,z;
}E[200010];

int last[100010],pre[200010],edge_cnt;
int n,m,s,t,dis[100010],ans,f,d;
queue<int>q;

void add(int x,int y,int z)
{
	edge_cnt++;
	E[edge_cnt].x=x;
	E[edge_cnt].y=y;
	E[edge_cnt].z=z;
	pre[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int bfs()
{
	q.push(s);
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=last[x];i!=0;i=pre[i])
		{
			if(E[i].z==0) continue;
			int y=E[i].y;
			if(dis[y]==-1)
			{
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	if(dis[t]==-1) return 0;
	return 1;
}

int dinic(int x,int flow)
{
	int sum=0;
	if(x==t) return flow;
	for(int i=last[x];i!=0;i=pre[i])
	{
		int y=E[i].y;
		if(E[i].z==0 || dis[y]!=dis[x]+1) continue;
		int p=dinic(y,min(flow-sum,E[i].z));
		sum+=p;E[i].z-=p;E[i^1].z+=p;
		if(sum==flow) return sum;
	}
	if(sum==0) dis[x]=-1;
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>f>>d;edge_cnt=1;
	s=2*n+f+d+1;t=s+1;
	for(int i=1;i<=n;i++){
		int a,b,x;
		add(2*i-1,2*i,1);
		add(2*i,2*i-1,0);
		scanf("%d%d",&a,&b);
		for(int j=1;j<=a;j++){
			scanf("%d",&x);
			add(2*n+x,2*i-1,1);
			add(2*i-1,2*n+x,0);
		}
		for(int j=1;j<=b;j++){
			scanf("%d",&x);
			add(2*i,2*n+f+x,1);
			add(2*n+f+x,2*i,0);
		}
	}
	for(int i=1;i<=f;i++){
		add(s,2*n+i,1);
		add(2*n+i,s,0);
	}
	for(int i=1;i<=d;i++){
		add(2*n+f+i,t,1);
		add(t,2*n+f+i,0);
	}
	while(bfs())
	{
		ans+=dinic(s,99999999);
	}
	cout<<ans;
	return 0;
}
