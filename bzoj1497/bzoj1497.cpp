#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
 
#define MAXE 320010
#define MAXNODE 60010
#define inf 1000000000  
 
struct edge
{
    int from,to,k;
}E[MAXE];
 
int last[MAXNODE],cur[MAXNODE],edge_cnt;
int n,m,s,t,ans,dis[MAXNODE],ne[MAXE];
int x,a,b,c;
 
inline void insert(int x,int y,int k)
{
    E[++edge_cnt].from=x;
    E[edge_cnt].to=y;
    E[edge_cnt].k=k;
  	ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}
 
inline void add(int x,int y,int k)
{
    insert(x,y,k);
    insert(y,x,0);
}
 
 
inline bool bfs()
{
    queue <int> Q;
    memset(dis,-1,sizeof(dis));
    Q.push(s);dis[s]=0;
    while(!Q.empty())
    {
        int tp=Q.front();Q.pop();
        if(tp==t) return true;
        for(int i=last[tp];i;i=ne[i])
        {
            int v=E[i].to;
            if(dis[v]==-1 && E[i].k)
            {
                dis[v]=dis[tp]+1;
                Q.push(v);
            }
        }
    }
    return false;
}
 
inline int dinic(int x,int f)
{
    int tmp,sum=0;
    if(x==t) return f;
    for(int &i=cur[x];i;i=ne[i])
    {
        int v=E[i].to;
        if(E[i].k && dis[v]==dis[x]+1)
        {
            tmp=dinic(v,min(f-sum,E[i].k));
            E[i].k-=tmp;
            E[i^1].k+=tmp;
            sum+=tmp;
            if(sum==f) return sum;
        }
    }
    if(sum==0) dis[x]=-1;
    return sum;
}
 
int main()
{
    scanf("%d %d",&n,&m);
    s=n+m+1;t=n+m+2;
    edge_cnt=1;
    for(int i=1;i<=n;i++)
    {
       scanf("%d",&x);
        add(i+m,t,x);
    }
    for(int i=1;i<=m;i++)
    {
       scanf("%d %d %d",&a,&b,&c);
        add(s,i,c); add(i,a+m,inf); add(i,b+m,inf);
        ans+=c;
    }
    while(bfs())
    {
        for(int i=1;i<=t;i++)
            cur[i]=last[i];
        ans-=dinic(s,inf);
    }
    printf("%d",ans);
    return 0;
}
