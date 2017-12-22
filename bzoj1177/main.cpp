#include <cstdio>
#include <iostream>
#include <memory.h>
#define N 1510
#define clr(a) memset(a,0,sizeof(a))
#define fp(a,b,c) for(a=b;a<=c;a++) 
#define fd(a,b,c) for(a=c;a>=b;a--)
using namespace std;
int i,j,n,m,k,ans=0,s[N][N],a[N][N],b[N][N],c[N][N],d[N][N],h[N],l[N];
int main()
{
 // freopen("1177.in","r",stdin);
  clr(s);clr(a);clr(b);clr(c);clr(d);clr(l);clr(h);
  scanf("%d%d%d",&n,&m,&k);
  fp(i,1,n) fp(j,1,m) scanf("%d",&s[i][j]),s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
  fd(i,k,n) fd(j,k,m) s[i][j]-=s[i-k][j]+s[i][j-k]-s[i-k][j-k],h[i]=max(h[i],s[i][j]),l[j]=max(l[j],s[i][j]);
  fp(i,k,n) fp(j,k,n) a[i][j]=max(s[i][j],max(a[i-1][j],a[i][j-1]));
  fp(i,k,n) fd(j,1,m-k+1) b[i][j]=max(s[i][j+k-1],max(b[i-1][j],b[i][j+1]));
  fd(i,1,n-k+1) fp(j,k,m) c[i][j]=max(s[i+k-1][j],max(c[i+1][j],c[i][j-1]));
  fd(i,1,n-k+1) fd(j,1,m-k+1) d[i][j]=max(s[i+k-1][j+k-1],max(d[i+1][j],d[i][j+1]));
  fp(i,k,n-k) fp(j,k,m-k) ans=max(ans,max(a[i][m]+c[i+1][j]+d[i+1][j+1],c[i+1][m]+a[i][j]+b[i][j+1])),ans=max(ans,max(c[1][j]+b[i][j+1]+d[i+1][j+1],a[i][j]+c[i+1][j]+d[1][j+1]));
  fp(i,k,n-2*k) fp(j,i+k,n-k) ans=max(ans,b[i][1]+h[j]+d[j+1][1]);
  fp(i,k,m-2*k) fp(j,i+k,m-k) ans=max(ans,a[n][i]+l[j]+d[1][j+1]);
  printf("%d\n",ans);
}