#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>  
#include<iostream>  
#include<algorithm>  
#include<queue>  
#define inf 2000000000  
#define pa pair<int,int>  
#define maxn 100010  
#define maxm 400010  
  
using namespace std;  
  
int head[maxn],to[maxm],len[maxm],next[maxm],dis[maxn];  
bool vis[maxn];  
priority_queue<pa,vector<pa>,greater<pa> > q;  
int n,m,mn,num,s,t1,t2;  
  
void addedge(int x,int y,int z)  
{  
    num++;to[num]=y;len[num]=z;next[num]=head[x];head[x]=num;  
}  
  
void dijkstra(int x)  
{  
    memset(vis,0,sizeof(vis));  
    for (int i=1;i<=n;i++) dis[i]=inf;  
    dis[x]=0;  
    q.push(make_pair(0,x));  
    while (!q.empty())  
    {  
        int x=q.top().second;q.pop();  
        if (vis[x]) continue;vis[x]=1;  
        for (int p=head[x];p;p=next[p])  
          if (dis[x]+len[p]<dis[to[p]])  
          {  
            dis[to[p]]=dis[x]+len[p];  
            q.push(make_pair(dis[to[p]],to[p]));  
          }  
    }  
}  
  
int main()  
{  
    scanf("%d%d%d%d%d",&m,&n,&s,&t1,&t2);  
    for (int i=1;i<=m;i++)  
    {  
        int x,y,z;  
        scanf("%d%d%d",&x,&y,&z);  
        addedge(x,y,z);addedge(y,x,z);  
    }  
    dijkstra(s);  
    mn=min(dis[t1],dis[t2]);  
    dijkstra(t1);  
    mn+=dis[t2];  
    printf("%d\n",mn);  
    return 0;  
}  