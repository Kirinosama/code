#include<cstdio>
#include<cstring>
#include<iostream>
#define inf 0x7fffffff
using namespace std;
int n,m,cnt=1,ans,head[10001],q[10001],to[10001],h[10001];
bool mark[10001];
struct data{int to,next,v;}e[2000001];
void ins(int u,int v,int w)
{cnt++;e[cnt].to=v;e[cnt].v=w;e[cnt].next=head[u];head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
bool bfs()
{
     int t=0,w=1,i,now;
     memset(h,-1,sizeof(h));
     h[0]=q[0]=0;
     while(t<w)
     {
               now=q[t];t++;
               i=head[now];
               while(i)
               {
                       if(h[e[i].to]==-1&&e[i].v){h[e[i].to]=h[now]+1;q[w++]=e[i].to;}
                       i=e[i].next;
                       }
               }
     if(h[8001]==-1)return 0;
     return 1;
 }
int dfs(int x,int f)
{
    if(x==8001)return f;
    int i=head[x];
    int w,used=0;
    while(i)
    {
            if(e[i].v&&h[e[i].to]==h[x]+1)
            {
                w=f-used;
                w=dfs(e[i].to,min(w,e[i].v));
                if(w)
				{
				   to[x]=e[i].to;
                   if(e[i].to-n>0)mark[e[i].to-n]=1;
                }
                e[i].v-=w;
                e[i^1].v+=w;
                used+=w;
                if(used==f)return f;                      
                }
                i=e[i].next;
            }
    if(!used)h[x]=-1;
    return used;
    }
void dinic(){while(bfs())ans-=dfs(0,inf);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
       {
          int u,v;
          scanf("%d%d",&u,&v);
          insert(u,v+n,inf);
       }
    for(int i=1;i<=n;i++)insert(0,i,1);
	for(int i=1;i<=n;i++)insert(i+n,8001,1);
	ans=n;
	dinic();
    for(int i=1;i<=n;i++)
    {
        if(mark[i])continue;
        printf("%d",i);
        int k=i;
        while(to[k])
        {
            printf(" %d",to[k]-n);
            k=to[k]-n;
        }
        printf("\n");
    }
	printf("%d",ans);
    return 0;   	
}
