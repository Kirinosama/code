#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cmath>  
#define ll long long  
#define N 100005  
using namespace std;  
  
int n,m,cnt1,cnt2,tot,dfsclk,f[N],g[N],fst[N],pnt[N<<1],nxt[N<<1],id[N<<1],blg[N<<1];  
int bin[25],pos[N],fa[N][17],c[N],d[N],u[N],v[N],w[N],last[N];  
struct node{ int l,r,t,id; }a[N],b[N]; ll ans[N],sum; bool vis[N];  
int read(){  
    int x=0; char ch=getchar();  
    while (ch<'0' || ch>'9') ch=getchar();  
    while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }  
    return x;  
}  
void add(int x,int y){  
    pnt[++tot]=y; nxt[tot]=fst[x]; fst[x]=tot;  
}  
void dfs(int x){  
    f[x]=++dfsclk; id[dfsclk]=x; int i,p;  
    for (i=1; bin[i]<=d[x]; i++) fa[x][i]=fa[fa[x][i-1]][i-1];  
    for (p=fst[x]; p; p=nxt[p]){  
        int y=pnt[p];  
        if (y!=fa[x][0]){  
            fa[y][0]=x; d[y]=d[x]+1; dfs(y);  
        }  
    }  
    g[x]=++dfsclk; id[dfsclk]=x;  
}  
int lca(int x,int y){  
    if (d[x]<d[y]) swap(x,y); int tmp=d[x]-d[y],i;  
    for (i=0; bin[i]<=tmp; i++)  
        if (tmp&bin[i]) x=fa[x][i];  
    for (i=16; i>=0; i--)  
        if (fa[x][i]!=fa[y][i]){ x=fa[x][i]; y=fa[y][i]; }  
    return (x==y)?x:fa[x][0];  
}  
bool cmp(node x,node y){  
    return blg[x.l]<blg[y.l] || blg[x.l]==blg[y.l] && blg[x.r]<blg[y.r] || blg[x.l]==blg[y.l] && blg[x.r]==blg[y.r] && x.t<y.t;  
}  
void mdy(int x){  
    if (vis[x]) sum-=(ll)v[c[x]]*w[u[c[x]]--]; else  
        sum+=(ll)v[c[x]]*w[++u[c[x]]];  
    vis[x]^=1;  
}  
void chg(int x,int y){  
    if (vis[x]){ mdy(x); c[x]=y; mdy(x); }else c[x]=y;  
}  
int main(){
    freopen("bzoj3052.in","r",stdin);  
    n=read(); m=read(); int cas=read(),i,l,r,t;  
    bin[0]=1; for (i=1; i<=17; i++) bin[i]=bin[i-1]<<1;  
    for (i=1; i<=m; i++) v[i]=read();  
    for (i=1; i<=n; i++) w[i]=read();  
    for (i=1; i<n; i++){  
        l=read(); r=read(); add(l,r); add(r,l);  
    }  
    for (i=1; i<=n; i++) c[i]=last[i]=read();  
    int sz=(int)pow(n,2.0/3);  
    dfs(1); for (i=1; i<=dfsclk; i++) blg[i]=(i-1)/sz;  
    while (cas--){  
        t=read(); l=read(); r=read();  
        if (t){  
            if (f[l]>f[r]) swap(l,r);  
            a[++cnt1].r=f[r]; a[cnt1].id=cnt1; a[cnt1].t=cnt2;  
            a[cnt1].l=(lca(l,r)==l)?f[l]:g[l];  
        } else{ b[++cnt2].l=l; b[cnt2].t=last[l]; last[l]=b[cnt2].r=r; }  
    }  
    sort(a+1,a+cnt1,cmp); l=1; r=0; t=1;  
    for (i=1; i<=cnt1; i++){  
        for (; t<=a[i].t; t++) chg(b[t].l,b[t].r); for (; t>a[i].t; t--) chg(b[t].l,b[t].t);  
        while (l>a[i].l) mdy(id[--l]); while (l<a[i].l) mdy(id[l++]);  
        while (r>a[i].r) mdy(id[r--]); while (r<a[i].r) mdy(id[++r]);  
        int x=id[l],y=id[r],tmp=lca(x,y);  
        if (x!=tmp && y!=tmp){ mdy(tmp); ans[a[i].id]=sum; mdy(tmp); }  
        else ans[a[i].id]=sum;  
    }  
    for (i=1; i<=cnt1; i++) printf("%lld\n",ans[i]);  
    return 0;  
}  