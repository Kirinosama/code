#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a[100010],f[40];

int main(){
    freopen("bzoj4300.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int x=a[i],Max=0;
        for(int j=1;j<=31;j++,x>>=1)if(x&1)
            Max=max(Max,f[j]+1);
        for(int j=1;j<=31;j++,a[i]>>=1)if(a[i]&1)
            f[j]=max(f[j],Max);
    }
    int ans=0;
    for(int i=1;i<=31;i++)ans=max(ans,f[i]);
    cout<<ans;
    return 0;
}
