#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll ans,tot;
int a[250010],b[250010],book[250010],n;
priority_queue <ii> Q;

struct cmp{
    bool operator () (const ii &x,const ii &y)const{
        return x.first<y.first;
    }
};

int main(){
    freopen("bzoj2802.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n;i++){
        tot+=a[i];
        if(tot>=b[i])ans++,tot-=b[i],Q.push(ii(b[i],i)),book[i]=1;
        else if(!Q.empty() && Q.top().first>b[i]) tot+=Q.top().first-b[i],book[Q.top().second]=0,Q.pop(),Q.push(ii(b[i],i)),book[i]=1;
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)if(book[i])
        printf("%d ",i);
    return 0;
}
