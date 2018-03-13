#include <cstdio>  
#include <algorithm>  
#include <vector>  
using namespace std;  
#define INF 1000000000  
vector<int> g[30050];  
struct lwn{  
    int u,v,flow,cap;  
} a[900050];  
int cur[30050],num[30050],d[30050],p[30050],tot,n,m,i,j;  
inline void link(int x,int y,int z)  
{  
    a[tot].u=x;a[tot].v=y;a[tot].cap=z;a[tot].flow=0;  
    g[x].push_back(tot++);  
    a[tot].u=y;a[tot].v=x;a[tot].cap=a[tot].flow=0;  
    g[y].push_back(tot++);  
}  
inline int maxflow(int s,int t)  
{  
    int x=s,ans=0;num[0]=n;  
    while (d[s]<n){  
        if (x==t){  
            int jb=INF;  
            while (x!=s){  
                jb=min(jb,a[p[x]].cap-a[p[x]].flow);  
                x=a[p[x]].u;  
            }x=t;ans+=jb;  
            while (x!=s){  
                a[p[x]].flow+=jb;  
                a[p[x]^1].flow-=jb;  
                x=a[p[x]].u;  
            }  
        }  
        bool zw=true;  
        for (i=cur[x];i<g[x].size();i++) if (a[g[x][i]].cap>a[g[x][i]].flow && d[x]==d[a[g[x][i]].v]+1){  
            cur[x]=i;p[a[g[x][i]].v]=g[x][i];  
            x=a[g[x][i]].v;zw=false;break;  
        }  
        if (zw){  
            if (--num[d[x]]==0) return ans;cur[x]=0;  
            d[x]=n;for (i=cur[x];i<g[x].size();i++) if (a[g[x][i]].cap>a[g[x][i]].flow) d[x]=min(d[x],d[a[g[x][i]].v]+1);  
            num[d[x]]++;if (x!=s) x=a[p[x]].u;  
        }  
    }return ans;  
}  
int main()  
{  
    scanf("%d%d",&n,&m);int ans=0;  
    for (i=0;i<n;i++)  
    for (j=1;j<=m;j++){  
        int x;scanf("%d",&x);ans+=x;  
        link(n*m*3+1,i*m+j,x);  
    }  
    for (i=0;i<n;i++)  
    for (j=1;j<=m;j++){  
        int x;scanf("%d",&x);ans+=x;  
        link(i*m+j,n*m*3+2,x);  
    }  
    for (i=0;i<n;i++)  
    for (j=1;j<=m;j++){  
        int x;scanf("%d",&x);ans+=x;  
        link(n*m*3+1,n*m+i*m+j,x);  
        link(n*m+i*m+j,i*m+j,INF);  
        if (i) link(n*m+i*m+j,(i-1)*m+j,INF);  
        if (j!=1) link(n*m+i*m+j,i*m+j-1,INF);  
        if (i!=n-1) link(n*m+i*m+j,(i+1)*m+j,INF);  
        if (j!=m) link(n*m+i*m+j,i*m+j+1,INF);  
    }  
    for (i=0;i<n;i++)  
    for (j=1;j<=m;j++){  
        int x;scanf("%d",&x);ans+=x;  
        link(n*m*2+i*m+j,n*m*3+2,x);  
        link(i*m+j,n*m*2+i*m+j,INF);  
        if (i) link((i-1)*m+j,n*m*2+i*m+j,INF);  
        if (j!=1) link(i*m+j-1,n*m*2+i*m+j,INF);  
        if (i!=n-1) link((i+1)*m+j,n*m*2+i*m+j,INF);  
        if (j!=m) link(i*m+j+1,n*m*2+i*m+j,INF);  
    }n=n*m*3+2;  
    printf("%d\n",ans-maxflow(n-1,n));  
    return 0;  
}  