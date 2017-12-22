#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

typedef long long LL;
const int inf = (1<<30);
const int MAXN = 2011;

int n,m,ans,ans2;
int a[MAXN][MAXN];
int topl[MAXN],topr[MAXN],nowl,nowr,up[MAXN];

inline int getint()
{
    int w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar(); if(c=='-') q=1,c=getchar(); 
    while (c>='0' && c<='9') w=w*10+c-'0', c=getchar(); return q ? -w : w;
}

inline void getA(){
    int lin; memset(up,0,sizeof(up));
    for(int i=1;i<=m;i++) topl[i]=1,topr[i]=m;
    for(int i=1;i<=n;i++){
    nowl=0,nowr=m+1;
    for(int j=1;j<=m;j++) {
        if(a[i][j]) {
        up[j]=0;
        topl[j]=1; nowl=j;
        }
        else up[j]++,topl[j]=max(nowl+1,topl[j]);
    }
    for(int j=m;j>=1;j--) {
        if(a[i][j]) {
        topr[j]=m; nowr=j;
        }
        else {
        topr[j]=min(topr[j],nowr-1);
        lin=min(topr[j]-topl[j]+1,up[j]); lin*=lin;
        ans=max(ans,lin);lin=(topr[j]-topl[j]+1)*up[j];
        ans2=max(ans2,lin);
        }
    }
    }
}

inline void work(){
    n=getint(); m=getint(); for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(((i&1)==(j&1) && a[i][j])||((i&1)!=(j&1) && !a[i][j])) a[i][j]=1; else a[i][j]=0;
    getA(); for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=!a[i][j];  getA();
    printf("%d\n%d",ans,ans2);
}

int main()
{
    work();
    return 0;
}