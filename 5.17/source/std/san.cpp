#include <bits/stdc++.h>
using namespace std;

const int mx=200,oo=1<<30;
struct edge{int s,t,c,n;}e[10000];
int n,m,tot=1,S,T,h[105],dis[105],H[105],ans;
queue <int> Q;

void addedge(int s,int t,int c)
{
	e[++tot]=(edge){s,t,c,h[s]},h[s]=tot;
	e[++tot]=(edge){t,s,0,h[t]},h[t]=tot;
}

bool bfs()
{
	int x,y,i;
	for (i=1; i<=T; i++)  dis[i]=0,H[i]=h[i];
	while (!Q.empty())  Q.pop();
	dis[T]=1,Q.push(T);
	while (!Q.empty())
		for (i=h[x=Q.front()],Q.pop(); y=e[i].t,i; i=e[i].n)
			if ((e[i^1].c)&&(!dis[y]))
				{
					dis[y]=dis[x]+1,Q.push(y);
					if (y==S)  return 1;
				}
	return 0;	
}

int dfs(int x,int a)
{
	if (x==T)  return a;
	int flow=0,t;
	for (int &i=H[x],y; y=e[i].t,i; i=e[i].n)
		if ((e[i].c)&&(dis[x]==dis[y]+1)&&(t=dfs(y,min(a,e[i].c))))
			if (e[i].c-=t,e[i^1].c+=t,flow+=t,!(a-=t))
				return flow;
	dis[x]=oo;
	return flow;
}

void work()
{
	scanf("%d %d",&n,&m),S=2*n+1,T=2*n+2,ans=n*mx;
	for (int i=1,x; i<=n; i++)
		scanf("%d",&x),addedge(S,i,mx),addedge(i,i+n,mx-x),addedge(i+n,T,mx);
	for (int i=1,x,y; i<=m; i++)
		scanf("%d %d",&x,&y),addedge(x,y,oo),addedge(x+n,y+n,oo);
	while (bfs())  ans-=dfs(S,oo);
	printf("%d",ans);
}

int main()
{
	freopen("san.in","r",stdin);
	freopen("san.out","w",stdout);
	work();
	return 0;
}
