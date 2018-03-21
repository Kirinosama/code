#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define N 1000010  
#define LL long long  
using namespace std;  
LL f[N],g[N],a[N],q1[N],q2[N];  
int ans,n,k,x,cnt,y,v,point[N],next[N<<1];  
struct use{  
  int st,en,v;  
}e[N<<1];  
int read(){  
  int x(0);char ch=getchar();  
  while (ch<'0'||ch>'9') ch=getchar();  
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();  
  return x;  
}  
void add(int x,int y,int v){  
  next[++cnt]=point[x];point[x]=cnt;  
  e[cnt].st=x;e[cnt].en=y;e[cnt].v=v;  
}  
void getf(int x,int fa){  
  for (int i=point[x];i;i=next[i])  
    if (e[i].en!=fa){  
      getf(e[i].en,x);  
      f[x]=max(f[x],f[e[i].en]+e[i].v);  
    }  
}  
void getg(int x,int fa){  
  LL mx=0,cmx=0;  
  for (int i=point[x];i;i=next[i])  
    if (e[i].en!=fa){  
      if (f[e[i].en]+e[i].v>mx) cmx=mx,mx=f[e[i].en]+e[i].v;  
      else cmx=max(cmx,f[e[i].en]+e[i].v);  
      g[e[i].en]=g[x]+e[i].v;  
    }  
  for (int i=point[x];i;i=next[i])  
    if (e[i].en!=fa){  
      if (f[e[i].en]+e[i].v==mx) g[e[i].en]=max(g[e[i].en],e[i].v+cmx);  
      else g[e[i].en]=max(g[e[i].en],e[i].v+mx);  
      getg(e[i].en,x);  
    }  
}  
void solve(){  
  int l1=1,l2=1,r1=0,r2=0,t=1;  
  for (int i=1;i<=n;i++){  
    while (l1<=r1&&a[i]<=a[q1[r1]]) r1--;  
    while (l2<=r2&&a[i]>=a[q2[r2]]) r2--;  
    q1[++r1]=i;q2[++r2]=i;  
    while (a[q2[l2]]-a[q1[l1]]>k){  
      if (q2[l2]<=q1[l1]) t=q2[l2]+1,l2++;  
      else t=q1[l1]+1,l1++;  
    }   
    ans=max(ans,i-t+1);  
  }  
}  
int main(){  
  //freopen("a.in","r",stdin);  
  //freopen("a.out","w",stdout);  
  n=read();k=read();  
  for (int i=2;i<=n;i++){  
    x=read();v=read();  
    add(i,x,v);add(x,i,v);  
  }   
  getf(1,0);  
  getg(1,0);  
  for (int i=1;i<=n;i++) a[i]=max(f[i],g[i]);  
  solve();  
  cout<<ans<<endl;   
}  