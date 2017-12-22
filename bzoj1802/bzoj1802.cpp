#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
ll a[1005],s[2],f[1005],n,ans,flag;
int main(){
    scanf("%lld",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for (int i=3;i<=n;i++)
        if (a[i]+a[i-1]==2) flag=1;
    if (!flag){
        for (int i=2;i<=n;i+=2) s[a[i]]++;
        printf("%lld\n%lld",s[0],s[1]);
        return 0;
    }
    for (int i=1;i<=n;i++) f[i]=(a[i]==1)?1:1e15;
    for (int i=1;i<=n;i++)
        if (i>2&&a[i]&&a[i-1]){
            for (int j=i-2;j>=1;j--) f[j]=min(f[j],f[j+1]+f[j+2]);
            for (int j=i+1;j<=n;j++) f[j]=min(f[j],f[j-1]+f[j-2]); 
        }
    for (int i=2;i<n;i+=2) ans+=f[i];
    printf("0\n%lld",ans);
}