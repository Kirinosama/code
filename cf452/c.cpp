#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll ans[60010],n;
int cnt;

int main(){
    freopen("cf452.in","r",stdin);
    scanf("%lld",&n);
    ll sum=n*(n+1)/2;
    ll part=(sum+1)/2;
   	ll lastch=n+1;
   	printf("%lld\n",2*part-sum);
    while(part){
    	ll p=min(part,lastch-1);
    	part-=p;lastch=p;
    	ans[++cnt]=p;
    }
    printf("%d ",cnt);
    for(int i=1;i<=cnt;i++) printf("%lld ",ans[i]);
    return 0;
}