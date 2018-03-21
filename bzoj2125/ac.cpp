#include<iostream>  
#include<cstdio>  
#define N 10005  
#define M 100005  
using namespace std;  
  
int n,m,cas,dfsclk,cnt,tot=1,pnt[M],len[M],nxt[M];  
int mrk[N],fa[N],anc[N],d[N],val[N],last[N],blg[N],sz[N],son[N],sum[N];  
struct graph{  
    int fst[N];  
    void add(int x,int y,int z){  
        pnt[++tot]=y; len[tot]=z; nxt[tot]=fst[x]; fst[x]=tot;  
    }  
}g1,g2;  
void dfs1(int x){  
    int p; mrk[x]=++dfsclk;  
    for (p=g1.fst[x]; p; p=nxt[p]) if ((p^1)!=last[x]){  
        int y=pnt[p];  
        if (!mrk[y]){  
            last[y]=p; dfs1(y);  
        } else if (mrk[y]>mrk[x]){  
            cnt++; int tmp=len[p];  
            for (; y!=x; y=pnt[last[y]^1]){  
                val[y]=tmp; blg[y]=cnt;  
                fa[y]=x; tmp+=len[last[y]];  
            }  
            sum[cnt]=tmp; blg[x]=cnt;  
            for (y=pnt[p]; y!=x; y=pnt[last[y]^1])  
                g2.add(x,y,min(val[y],tmp-val[y]));  
        }  
    }  
}  
void dfs2(int x){  
    int p; sz[x]=1;  
    for (p=g2.fst[x]; p; p=nxt[p]){  
        int y=pnt[p]; d[y]=d[x]+len[p];  
        dfs2(y); sz[x]+=sz[y];  
        if (sz[y]>sz[son[x]]) son[x]=y;  
    }  
}  
void divide(int x,int tp){  
    int p; anc[x]=tp;  
    if (son[x]) divide(son[x],tp);  
    for (p=g2.fst[x]; p; p=nxt[p]){  
        int y=pnt[p];  
        if (y!=son[x]) divide(y,y);  
    }  
}  
int lca(int x,int y){  
    for (; anc[x]!=anc[y]; x=fa[anc[x]])  
        if (d[anc[x]]<d[anc[y]]) swap(x,y);  
    return (d[x]<d[y])?x:y;  
}  
int findup(int x,int y){  
    int z=0;  
    for (; anc[x]!=anc[y]; x=fa[anc[x]]) z=anc[x];  
    return (x==y)?z:son[y];  
}  
int main(){  
    freopen("bzoj2125.in","r",stdin);
    freopen("bzoj21251.out","w",stdout);
    scanf("%d%d%d",&n,&m,&cas); int i,x,y,z,u,v;  
    for (i=1; i<=m; i++){  
        scanf("%d%d%d",&x,&y,&z);  
        g1.add(x,y,z); g1.add(y,x,z);  
    }  
    dfs1(1);  
    for (i=1; i<=n; i++)  
        if (!fa[i]){  
            fa[i]=pnt[last[i]^1];  
            g2.add(fa[i],i,len[last[i]]);  
        }  
    dfs2(1); divide(1,1);  
    while (cas--){  
        scanf("%d%d",&x,&y); z=lca(x,y);  
        if (x==z || y==z) printf("%d\n",d[x]+d[y]-(d[z]<<1)); else{  
            u=findup(x,z); v=findup(y,z);  
            if (blg[u]==blg[v] && blg[u]){  
                if (fa[u]!=z) u=z; if (fa[v]!=z) v=z;  
                if (val[u]>val[v]) swap(u,v);  
                printf("%d\n",d[x]-d[u]+d[y]-d[v]+min(val[v]-val[u],val[u]-val[v]+sum[blg[u]]));  
            } else printf("%d\n",d[x]+d[y]-(d[z]<<1));  
        }  
    }  
    return 0;  
}  