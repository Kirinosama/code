#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define N 300010  
#define ll long long  
using namespace std;  
int n,m,cnt,fa[N],c[N],deep[N],point[N],ans1[N],ans2[N],rt[N],next[N<<1];  
ll h[N],s[N],k[N],b[N];  
struct use{int st,en;}e[N<<1];  
struct hp{  
  ll k,b,v;  
  int dis,l,r;  
}t[N];  
ll read(){  
  ll x(0),f=1;char ch=getchar();  
  while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}  
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();  
  return x*f;  
}  
void add(int x,int y){  
  next[++cnt]=point[x];point[x]=cnt;  
  e[cnt].st=x;e[cnt].en=y;  
}  
void paint(int x,ll k,ll b){  
  if (x==0) return;  
  t[x].v=t[x].v*k+b;  
  t[x].k*=k;t[x].b*=k;t[x].b+=b;  
}  
void pushdown(int x){  
  paint(t[x].l,t[x].k,t[x].b);  
  paint(t[x].r,t[x].k,t[x].b);  
  t[x].k=1;t[x].b=0;  
}  
int merge(int a,int b){  
  if (!a||!b) return a+b;  
  pushdown(a);pushdown(b);  
  if (t[a].v>t[b].v) swap(a,b);  
  t[a].r=merge(t[a].r,b);  
  if (t[t[a].r].dis>t[t[a].l].dis) swap(t[a].l,t[a].r);  
  t[a].dis=t[t[a].r].dis+1;  
  return a;  
}  
void dfs(int x){  
  for (int i=point[x];i;i=next[i]){  
     int u=e[i].en;  
     deep[u]=deep[x]+1;  
     dfs(u);paint(rt[u],k[u],b[u]);  
     rt[x]=merge(rt[x],rt[u]);  
  }  
  while (rt[x]&&t[rt[x]].v<h[x]){  
    pushdown(rt[x]);ans1[x]++;  
    ans2[rt[x]]=deep[c[rt[x]]]-deep[x];  
    rt[x]=merge(t[rt[x]].l,t[rt[x]].r);  
  }  
}  
int main(){  
  n=read();m=read();  
  for (int i=1;i<=n;i++) h[i]=read();  
  for (int i=2;i<=n;i++){  
    fa[i]=read();add(fa[i],i);  
    k[i]=read();b[i]=read();  
    if (k[i]==0) k[i]=1;  
    else k[i]=b[i],b[i]=0;   
  }  
  for (int i=1;i<=m;i++){  
    s[i]=read();c[i]=read();  
    t[i].k=1;t[i].b=0;t[i].v=s[i];  
    rt[c[i]]=merge(rt[c[i]],i);   
  }  
  dfs(1);  
  while (rt[1]){  
    pushdown(rt[1]);  
    ans2[rt[1]]=deep[c[rt[1]]]+1;  
    rt[1]=merge(t[rt[1]].l,t[rt[1]].r);  
  }  
  for (int i=1;i<=n;i++) printf("%d\n",ans1[i]);  
  for (int i=1;i<=m;i++) printf("%d\n",ans2[i]);  
}   
