#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
    int u,v;
    int w;
    Edge(){
        u=0,v=0;
        w=0;
    }
    Edge(int u_,int v_,int w_){
        u=u_,v=v_;
        w=w_;
    }
    bool operator <(const Edge& a)const{
        return w<a.w;
    }
};

int fa[505];
Edge edge[5005];
int n,m;
int p,q;
double ans=1e9;
int s,t;

int find(int a)
{
    if(fa[a]!=a)
        fa[a]=find(fa[a]);
    return fa[a];
}````````````````````````````````````````````````

void Union(int a,int b)
{
    fa[find(a)]=find(b);
}

bool Near(int a,int b)
{
    return find(a)==find(b);
}

void Clear()
{
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

void Solve()
{
    sort(edge+1,edge+1+m);
    for(int i=1;i<=m;i++){
        Clear();
        int p_=edge[i].w,q_=0x3f3f3f3f;
        for(int j=i;j>=1;j--)
            if(!Near(edge[j].u,edge[j].v)){
                Union(edge[j].u,edge[j].v);
                q_=edge[j].w;
                if(Near(s,t))
                    break;
            }
        if(!Near(s,t))
            continue;
        if((double)p_/(double)q_<ans){
            p=p_,q=q_;
            ans=(double)p/double(q);
        }
    }
    if(p==0&&q==0)
        printf("IMPOSSIBLE");
    else
        if(p%q==0)
            printf("%d",p/q);
        else
            printf("%d/%d",p/gcd(p,q),q/gcd(p,q));
}

void Readdata()
{
    //freopen("loli.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    scanf("%d%d",&s,&t);
}

void Close()
{
    fclose(stdin);
    fclose(stdout);
}

int main()
{
    Readdata();
    Solve();
   // Close();
    return 0;
}