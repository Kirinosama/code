#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 100010
#define ii pair<long long,long long>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,k;
ll ans;
priority_queue <ii,vector<ii>,greater<ii> > pq;

int main(){
    freopen("bzoj4198.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        ll x;scanf("%lld",&x);
        pq.push(ii(x,0));
    }
    while(k>2 && n%(k-1)!=1)
        n++,pq.push(ii(0,0));
    while(pq.size()>1){
        ll Max=0,sum=0;
        for(int i=1;i<=k;i++){
            Max=max(Max,pq.top().second+1);
            sum+=pq.top().first;
            pq.pop();
        }
        ans+=sum;
        pq.push(ii(sum,Max));
    }
    printf("%lld\n%lld",ans,pq.top().second);
    return 0;
}
