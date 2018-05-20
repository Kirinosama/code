#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int maxn=1e5+1000,inf=1e8;
struct stu
{
    int to,next,dis;
}road[2*maxn]; int first[maxn],cnt=0;
int lastans,v,d,n,m,ty;
int fa[maxn],val[maxn];

void addedge(int x,int y,int dis)
{
    road[++cnt].to=y;
    road[cnt].dis=dis;
    road[cnt].next=first[x];
    first[x]=cnt;
}

void dfs1(int now)
{
    for(int i=first[now];i;i=road[i].next)
    {
        int to=road[i].to;
        if(to==fa[now]) continue;
        fa[to]=now;
        dfs1(to);
    }
}

void dfs(int now,int minn)
{
    if(minn<d) return;
    val[now]+=v;
    for(int i=first[now];i;i=road[i].next)
    {
        int to=road[i].to;
        if(to==fa[now]) continue;
        dfs(to,min(minn,road[i].dis));
    }
}

int main()
{
	freopen("ichi.in","r",stdin);
    scanf("%d%d%d",&n,&m,&ty);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=n-1;i++)
    {
        int x,y,dis;
        scanf("%d%d%d",&x,&y,&dis);
        addedge(x,y,dis);addedge(y,x,dis);
    }
    dfs1(1);
    while(m--)
    {
        int type;
        scanf("%d",&type);
        if(type==1)
        {
            int x;
            scanf("%d",&x);
            if(ty) x=(x+lastans)%n+1;
            printf("%d\n",val[x]);
            lastans=val[x];
        }
        else
        {
            int x;
            scanf("%d%d%d",&v,&d,&x);
            if(ty) x=(x+lastans)%n+1;
            dfs(x,inf);
        }
    }
    return 0;
}
