#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a[110],A[32],bin[32];
ll ans,tot;

int main(){
    freopen("bzoj3105.in","r",stdin);
    cin>>n;bin[0]=1;
    for(int i=1;i<=31;i++)bin[i]=bin[i-1]<<1;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),tot+=a[i],a[i]=-a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        a[i]=-a[i];
        int t=a[i];
        for(int j=31;j>=0;j--)if(a[i]&bin[j]){
            if(A[j]) a[i]^=A[j];
            else{
                A[j]=a[i];
                for(int k=j-1;k>=0;k--)if(A[j]&bin[k])
                    A[j]^=A[k];
                for(int k=j+1;k<=31;k++)if(A[k]&bin[j])
                    A[k]^=A[j];
                break;
            }
        }
        if(a[i])ans+=t;
    }
    if(!ans) cout<<-1;
    else printf("%lld",tot-ans);
    return 0;
}
