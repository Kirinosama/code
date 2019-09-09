#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int e[301][301]={0},book[301]={0},top=0,minstep=999999999,ans=0,n,m,flag=0;
struct node
{
    int u,v,w;
}s[301];

void dfs(int u)
{
    if(flag==1)return;
    if(book[u]==1)
    {
        top--;
        return ;
    }
    book[u]=1;
    if(u==n)
    {
        for(int i=1;i<=top;i++)
        {
            if(minstep < s[i].w) minstep=s[i].w;
        }
        for(int i=1;i<=top;i++)
        {
            e[s[i].u][s[i].v]-=minstep;
        }
        flag=1;
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(e[u][i]!=0 && flag==0)
        {
            top++;
            s[top].u=u;
            s[top].v=i;
            s[top].w=e[u][i];
            dfs(i);
        }
    }
    top--;
    return ;
}

int main()
{
    cin >> m >> n;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        e[u][v]+=w;
    }
    while(1>0)
    {   
        memset(book,0,sizeof(book));
        minstep=999999999;
        top=0;
        flag=0;
        dfs(1);
        if(minstep==999999999)break;
        else ans+=minstep;
    }
    cout << ans;
    return 0;
}
