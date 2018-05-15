/*
题意是要把所有的边加上或者减去一个值，使得最短路没有负环，输出最小非负解
要二分加上去的数字。这个没问题
然后要判断在最短路的路径上没有负环。不仅是判断负环的问题，还要求在最短路的路径上
因此在spfa判负环的基础上做这样的处理：
首先floyd预处理出各个点之间的连通性。我们只更新可以到达目标点的状态
即当当前这个点可以到达n点的时候才更新
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#include<deque>
#include<set>
#include<map>
#include<ctime>
#define LL long long
#define inf 598460606
#define pa pair<int,int>
#define pi 3.1415926535897932384626433832795028841971
#define mod 100007
using namespace std;
struct edge{
    int to,next,v;
}e[1000010];
int head[100010];
int rep[100010];
int dist[100010];
bool mrk[100010];
int go[110][110];
int q[mod];
int T,n,m,l,r,cnt,ans;
inline void ins(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].v=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline int jud(int lim)  
{  
    for (int i=1;i<=n;i++)mrk[i]=0;
    for (int i=1;i<=n;i++)dist[i]=inf;
    for (int i=1;i<=n;i++)rep[i]=0;
    memset(q,0,sizeof(q));
    q[1]=1;mrk[1]=1;dist[1]=0;rep[1]=1;
    int t=0,w=1;
    while (t<w)
    {  
        int now=q[++t];
        mrk[now]=0;
        for (int i=head[now];i;i=e[i].next)
        {
          if (dist[e[i].to]>dist[now]+e[i].v+lim&&go[e[i].to][n])
          {
            dist[e[i].to]=dist[now]+e[i].v+lim;
            
            if (!mrk[e[i].to]&&rep[e[i].to]<=n)
            {  
                mrk[e[i].to]=1;
                rep[e[i].to]++;
                if (rep[e[i].to]>n)return -1;
                q[++w]=e[i].to;
            }  
          }
      }
    }
    return dist[n];
}
inline void work()
{
    memset(e,0,sizeof(e));
    memset(head,0,sizeof(head));
    memset(go,0,sizeof(go));
    cnt=0;
    scanf("%d%d",&n,&m);
    int mn=inf;
    int mx=-inf;
    for (int i=1;i<=m;i++)
    {
      int x,y,z;
      scanf("%d%d%d",&x,&y,&z);
      ins(x,y,z);
      mn=min(mn,z);
      mx=max(mx,z);
      go[x][y]=1;
    }
    for(int i=1;i<=n;i++)go[i][i]=1;
    for(int k=1;k<=n;k++)
      for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
          go[i][j]=go[i][j]|(go[i][k]&go[k][j]);
    if (!go[1][n]){printf("-1\n");return;}
    l=-mx;r=-mn;
    ans=-1;
    while (l<=r)
    {
        int mid=(l+r)>>1,now=jud(mid);
        if (now>=0&&now!=inf){ans=now;r=mid-1;}
        else l=mid+1;
    }
    printf("%d\n",ans);
} 
int main()
{
    freopen("tstrip.in","r",stdin);
    freopen("tstrip.out","w",stdout);
    scanf("%d",&T);
    while (T--)work();
}