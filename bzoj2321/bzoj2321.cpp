#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;
ll ans,x;

int main(){
    freopen("bzoj2321.in","r",stdin);
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++){
            scanf("%lld",&x);
            ans+=x*((i*i)+(j*j));
        }
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++){
            scanf("%lld",&x);
            ans-=x*((i*i)+(j*j));
        }
    printf("%lld",ans/2);
    return 0;
}
