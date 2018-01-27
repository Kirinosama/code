#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 120100
using namespace std;

int n,m;

namespace Tree{
    int n;
    struct abcd{
        int to,next;
    }table[M];
    int head[M],tot=1;
    int f[M][2];
    void Add(int x,int y)
    {
        table[++tot].to=y;
        table[tot].next=head[x];
        head[x]=tot;
    }
    void Tree_DP(int x,int from)
    {
        int i;
        if(x<=::n)
        {
            f[x][0]=0;f[x][1]=1;
            for(i=head[x];i;i=table[i].next)
                if(table[i].to!=from)
                {
                    Tree_DP(table[i].to,x);
                    if(table[i].to>::n)
                        continue;
                    f[x][0]+=max(f[table[i].to][0],f[table[i].to][1]);
                    f[x][1]+=f[table[i].to][0];
                }
        }
        else
        {
            static int g[M][2];int top=0;
            for(i=head[x];i;i=table[i].next)
                if(table[i].to!=from)
                    Tree_DP(table[i].to,x);
            for(i=head[x];i;i=table[i].next)
            {
                g[++top][0]=f[table[i].to][0];
                g[  top][1]=f[table[i].to][1];
            }
            for(i=top-1;i;i--)
            {
                g[i][0]+=max(g[i+1][0],g[i+1][1]);
                g[i][1]+=g[i+1][0];
            }
            f[from][0]=g[1][0];
            for(i=1;i<top;i++)
            {
                g[i][0]-=max(g[i+1][0],g[i+1][1]);
                g[i][1]-=g[i+1][0];
            }
            g[top][1]=0xefefefef;
            for(i=top-1;i;i--)
            {
                g[i][0]+=max(g[i+1][0],g[i+1][1]);
                g[i][1]+=g[i+1][0];
            }
            f[from][1]=g[1][1];
        }
    }
}

namespace Cactus{
    struct abcd{
        int to,next;
    }table[M];
    int head[M],tot=1;
    int fa[M],dfn[M],T;
    bool on_ring[M];
    void Add(int x,int y)
    {
        table[++tot].to=y;
        table[tot].next=head[x];
        head[x]=tot;
    }
    void DFS(int x,int from)
    {
        int i;
        dfn[x]=++T;
        for(i=head[x];i;i=table[i].next)
            if(i^from^1)
            {
                if(!dfn[table[i].to])
                {
                    fa[table[i].to]=x;
                    on_ring[x]=false;
                    DFS(table[i].to,i);
                    if(!on_ring[x])
                    {
                        Tree::Add(x,table[i].to);
                        Tree::Add(table[i].to,x);
                    }
                }
                else
                {
                    if(dfn[table[i].to]>dfn[x])
                        continue;
                    int temp=x;++Tree::n;
                    while(1)
                    {
                        Tree::Add(Tree::n,temp);
                        Tree::Add(temp,Tree::n);
                        on_ring[temp]=true;
                        if(temp==table[i].to)
                            break;
                        temp=fa[temp];
                    }
                }
            }

    }
}

int main()
{
    freopen("bzoj4316.in","r",stdin);
    freopen("output2","w",stdout);
    int i,x,y;
    cin>>n>>m;Tree::n=n;
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        Cactus::Add(x,y);
        Cactus::Add(y,x);
    }
    Cactus::DFS(1,0);
    Tree::Tree_DP(1,0);
    cout<<max(Tree::f[1][0],Tree::f[1][1])<<endl;
}