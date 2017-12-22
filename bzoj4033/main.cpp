#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 2020
using namespace std;
struct edge{
    int to,f,next;
}table[M<<1];
int head[M],tot;
int n,k;
int size[M];
long long f[M][M];

void Add(int x,int y,int z)
{
    table[++tot].to=y;
    table[tot].f=z;
    table[tot].next=head[x];
    head[x]=tot;
}
void Tree_DP(int x,int from)
{
    int i,j,k;
    size[x]=1;
    for(i=head[x];i;i=table[i].next)
        if(table[i].to!=from)
        {
            Tree_DP(table[i].to,x);
            for(j=size[x];~j;j--)
            {
                for(k=1;k<=size[table[i].to];k++)
                    f[x][j+k]=max(f[x][j+k],f[x][j]+f[table[i].to][k]+(long long)k*(::k-k)*table[i].f+(long long)(size[table[i].to]-k)*(n-::k-size[table[i].to]+k)*table[i].f );
                f[x][j]=f[x][j]+f[table[i].to][0]+(long long)size[table[i].to]*(n-::k-size[table[i].to])*table[i].f;
            }
            size[x]+=size[table[i].to];
        }
}
int main()
{
    int i,x,y,z;
    cin>>n>>k;
    for(i=1;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        Add(x,y,z);Add(y,x,z);
    }
    Tree_DP(1,0);
    cout<<f[1][k]<<endl;
    return 0;
}