#include <cstdio>  
#include <cstring>  
#include <algorithm>  
const int maxn=27;  
using namespace std;  
int T,n,a[maxn],sg[maxn],tot,ans;bool bo[20010];  
  
int getsg(int x){  
    if (sg[x]!=-1) return sg[x];//printf("xxxxx%d\n",x);  
    memset(bo,0,sizeof(bo));  
    for (int i=1;i<x;i++)  
        for (int j=1;j<=i;j++)  
            bo[getsg(i)^getsg(j)]=1;//,printf("%d %d\n",i,j)  
    for (int i=0;;i++) if (!bo[i]) return sg[x]=i;  
}  
  
int main(){  
    memset(sg,-1,sizeof(sg));  
    sg[1]=0;for (int i=2;i<26;i++) sg[i]=getsg(i);  
    //for (int i=1;i<=20;i++) printf("%d\n",sg[i]);  
    scanf("%d",&T);  
    while (T--){  
        scanf("%d",&n),ans=tot=0;  
        for (int i=1;i<=n;i++) scanf("%d",&a[i]);  
        for (int i=1;i<=n;i++) if (a[i]&1) ans^=sg[n-i+1];  
        for (int i=1;i<=n;i++)  
            for (int j=i+1;j<=n;j++)  
                for (int k=j;k<=n;k++)  
                    if (!(ans^sg[n-i+1]^sg[n-j+1]^sg[n-k+1]))  
                        if (++tot==1) printf("%d %d %d\n",i-1,j-1,k-1);  
        if (!tot) puts("-1 -1 -1");  
        printf("%d\n",tot);  
    }  
    return 0;  
}  
