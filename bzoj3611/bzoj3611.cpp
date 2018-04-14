#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
typedef long long ll;  
const int maxn=1000010,maxm=maxn<<1,maxk=23,inf=1e9;  
using namespace std;  
int n,q,dis[maxn],dfn[maxn],tim,dep[maxn],fa[maxn][maxk],num,poi[maxn];  
int stk[maxn],top,siz[maxn],maxs[maxn],mins[maxn],ans1,ans2;  
ll f[maxn];bool bo[maxn];  
bool cmp(int a,int b){return dfn[a]<dfn[b];}  
struct Tgraph{  
    int pre[maxm],now[maxn],son[maxm],tot;  
    void add(int a,int b){pre[++tot]=now[a],now[a]=tot,son[tot]=b;}  
    void dfs1(int x){  
        dfn[x]=++tim;  
        for (int i=1;i<=20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];  
        for (int y=now[x];y;y=pre[y]) if (son[y]!=fa[x][0])  
            dis[son[y]]=dis[x]+1,dep[son[y]]=dep[x]+1,fa[son[y]][0]=x,dfs1(son[y]);  
    }  
    void dfs2(int x){  
        siz[x]=bo[x],maxs[x]=0,mins[x]=inf,f[x]=0;  
        for (int y=now[x];y;y=pre[y]){  
            int d=dis[son[y]]-dis[x];  
            dfs2(son[y]),siz[x]+=siz[son[y]];  
            ans1=min(ans1,mins[x]+mins[son[y]]+d),mins[x]=min(mins[x],mins[son[y]]+d);  
            ans2=max(ans2,maxs[x]+maxs[son[y]]+d),maxs[x]=max(maxs[x],maxs[son[y]]+d);  
            f[x]+=f[son[y]]+1ll*siz[son[y]]*(num-siz[son[y]])*d;  
        }  
        if (bo[x]) ans1=min(ans1,mins[x]),ans2=max(ans2,maxs[x]),mins[x]=0;  
        now[x]=0;  
    }  
}g1,g2;  
  
int lca(int a,int b){  
    if (dep[a]<dep[b]) swap(a,b);  
    for (int h=dep[a]-dep[b],i=20;i>=0;i--) if (h>=(1<<i)) h-=(1<<i),a=fa[a][i];  
    if (a==b) return a;  
    for (int i=20;i>=0;i--) if (fa[a][i]!=fa[b][i]) a=fa[a][i],b=fa[b][i];  
    return fa[a][0];  
}  
  
void work(){  
    top=0;  
    for (int i=1;i<=num;i++){  
        if (!top){stk[++top]=poi[i];continue;}  
        int u=lca(stk[top],poi[i]);  
        while (dfn[u]<dfn[stk[top]]){  
            if (dfn[u]>=dfn[stk[top-1]]){  
                g2.add(u,stk[top]);  
                if (stk[--top]!=u) stk[++top]=u;  
                break;  
            }  
            g2.add(stk[top-1],stk[top]),top--;  
        }  
        stk[++top]=poi[i];  
    }  
    while (top>1) g2.add(stk[top-1],stk[top]),top--;  
    ans1=inf,ans2=0,g2.dfs2(stk[1]);  
    printf("%lld %d %d\n",f[stk[1]],ans1,ans2);  
    for (int i=1;i<=num;i++) bo[poi[i]]=0;g2.tot=0;  
}  
  
int main(){  
    scanf("%d",&n);  
    for (int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b),g1.add(a,b),g1.add(b,a);  
    g1.dfs1(1),scanf("%d",&q);  
    for (int i=1;i<=q;i++){  
        scanf("%d",&num);  
        for (int j=1;j<=num;j++) scanf("%d",&poi[j]),bo[poi[j]]=1;  
        sort(poi+1,poi+1+num,cmp),work();  
    }  
    return 0;  
}  
