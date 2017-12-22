#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>  
#include<algorithm>  
#include<iostream>  
#define maxn 210  
#define maxm 400010   
#define inf 1000000000  
  
using namespace std;  
  
int head[maxn],to[maxm],c[maxm],next[maxm],q[maxn],d[maxn];  
bool a[maxn][maxn];  
int num1[maxn],num2[maxn],seq1[maxn],seq2[maxn];  
int n,m,k,ans,num,w,s,t,sum;  
  
void addedge(int x,int y,int z)  
{  
    num++;to[num]=y;c[num]=z;next[num]=head[x];head[x]=num;  
    num++;to[num]=x;c[num]=0;next[num]=head[y];head[y]=num;  
}  
  
bool build()  
{  
    s=0;t=n+m+1;  
    for (int i=1;i<=n;i++)  
      for (int j=1;j<=m;j++)  
        if (!a[i][j])  
        {  
            num1[i]++;num2[j]++;  
            addedge(i,n+j,1);  
        }  
    for (int i=1;i<=n;i++) if (num1[i]>=seq1[i]) addedge(s,i,num1[i]-seq1[i]),sum+=num1[i]; else return 0;  
    for (int i=1;i<=m;i++) if (num2[i]>=seq2[i]) addedge(n+i,t,num2[i]-seq2[i]); else return 0;  
    return 1;  
}  
  
bool bfs()  
{  
    for (int i=s;i<=t;i++) d[i]=-1;  
    int l=0,r=1;  
    q[1]=s;d[s]=0;  
    while (l<r)  
    {  
        int x=q[++l];  
        for (int p=head[x];p;p=next[p])  
          if (c[p] && d[to[p]]==-1)  
          {  
            d[to[p]]=d[x]+1;  
            q[++r]=to[p];  
          }  
    }  
    if (d[t]==-1) return 0;  
    else return 1;  
}  
  
int find(int x,int low)  
{  
    if (x==t || low==0) return low;  
    int totflow=0;  
    for (int p=head[x];p;p=next[p])  
      if (c[p] && d[to[p]]==d[x]+1)  
      {  
        int a=find(to[p],min(low,c[p]));  
        c[p]-=a;c[p^1]+=a;  
        totflow+=a;low-=a;  
        if (low==0) return totflow;  
      }  
    if (low) d[x]=-1;  
    return totflow;  
}  
  
void Dinic()  
{  
    while (bfs()) ans+=find(s,inf);  
}  
  
int main()  
{  
    scanf("%d%d%d",&n,&m,&k);  
    num=1;  
    for (int i=1;i<=n;i++) scanf("%d",&seq1[i]);  
    for (int i=1;i<=m;i++) scanf("%d",&seq2[i]);  
    for (int i=1;i<=k;i++)  
    {  
        int x,y;  
        scanf("%d%d",&x,&y);  
        a[x][y]=1;  
    }  
    if (!build()) {printf("JIONG!\n");return 0;}  
    Dinic();  
    printf("%d\n",sum-ans);  
    return 0;  
}  