#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define N 100005  
#define M 600005  
using namespace std;  
  
int n,m,tot,cnt,tp,dfsclk,fst[N],pnt[M],nxt[M],pos[N],low[N],stk[N],scc[N],sz[N];  
int et[N],u[M],v[M]; bool vis[N];  
int read(){  
    int x=0; char ch=getchar();  
    while (ch<'0' || ch>'9') ch=getchar();  
    while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }  
    return x;  
}  
void add(int aa,int bb){  
    pnt[++tot]=bb; nxt[tot]=fst[aa]; fst[aa]=tot;  
}  
void dfs(int x){  
    pos[x]=low[x]=++dfsclk; stk[++tp]=x; int p;  
    for (p=fst[x]; p; p=nxt[p]){  
        int y=pnt[p];  
        if (!pos[y]){ dfs(y); low[x]=min(low[x],low[y]); }  
        else if (!scc[y]) low[x]=min(low[x],pos[y]);  
    }  
    if (low[x]==pos[x])  
        for (cnt++; ; tp--){  
            sz[cnt]++; scc[stk[tp]]=cnt;  
            if (stk[tp]==x){ tp--; break; }  
        }  
}  
bool jdg(int x){  
    int p;  
    for (p=fst[x]; p; p=nxt[p]) if (et[pnt[p]]==1) return 0;  
    return 1;  
}  
int main(){  
    n=read(); m=read(); int i,j,p,ans=0;  
    if (n==1){ puts("1.000000"); return 0; }  
    for (i=1; i<=m; i++){  
        int x=read(),y=read(); add(x,y);  
    }  
    for (i=1; i<=n; i++) if (!pos[i]) dfs(i);  
    m=0;  
    for (i=1; i<=n; i++){  
        for (p=fst[i]; p; p=nxt[p]){  
            j=scc[pnt[p]];  
            if (!vis[j] && scc[i]!=j){  
                vis[j]=1;  
                u[++m]=scc[i]; v[m]=j;  
            }  
        }  
        for (p=fst[i]; p; p=nxt[p]) vis[scc[pnt[p]]]=0;  
    }  
    tot=0; for (i=1; i<=cnt; i++) fst[i]=0;  
    for (i=1; i<=m; i++){ add(u[i],v[i]); et[v[i]]++; }  
    for (i=1; i<=cnt; i++) if (!et[i]) ans++;  
    for (i=1; i<=cnt; i++)  
        if (!et[i] && sz[i]==1 && jdg(i)){  
            ans--; break;  
        }  
    printf("%.6f\n",(double)(n-ans)/n);  
    return 0;  
}  

