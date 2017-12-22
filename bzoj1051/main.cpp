#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cstdlib>  
#include <cmath>  
#include <algorithm>  
#include <stack>  
using namespace std; 

#define ll long long  
#define maxn 10005  
#define maxm 50005 
 
struct edge
{
    int next,to;
}e[maxm],d[maxm];  

int n,m,cnt,scc,top,ans;  
int h[maxn],s[maxn],sz[maxn],dfn[maxn],low[maxn],head[maxn],belong[maxn];  

inline int read()  
{  
    int x=0,f=1;char ch=getchar();  
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}  
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}  
    return x*f;  
}  

inline void dfs(int x)  
{  
    int tmp=0;  
    low[x]=dfn[x]=++cnt;  
    s[++top]=x;  
    for(int i=head[x];i;i=e[i].next)  
    {  
        int y=e[i].to;  
        if (!dfn[y])  
        {  
            dfs(y);  
            low[x]=min(low[x],low[y]);  
        }  
        else if (!belong[y]) low[x]=min(low[x],dfn[y]);  
    }  
    if (low[x]==dfn[x])  
    {  
        scc++;  
        while (tmp!=x)  
        {  
            tmp=s[top--];  
            belong[tmp]=scc;  
            sz[scc]++;  
        }  
    }  
}  
inline void rebuild()  
{  
    cnt=0;  
    for(int i=1;i<=n;i++)
    for(int j=head[i];j;j=e[j].next)  
    {  
        int x=belong[i],y=belong[e[j].to];  
        if (x!=y)  
        {  
            d[++cnt]=(edge){h[x],y};  
            h[x]=cnt;  
        }  
    }  
}  
int main()  
{  
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++) 
    {  
        int x,y;
        scanf("%d %d",&x,&y);
        e[i]=(edge){head[x],y};  
        head[x]=i;  
    }  
    for(int i=1;i<=n;i++)
        if (!dfn[i])
            dfs(i); 

    rebuild();  
    for(int i=1;i<=scc;i++)
        if (!h[i])  
        {  
            if (ans){ans=0;break;}  
            else ans=sz[i];  
        }  
    printf("%d\n",ans);  
}  