#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll a[MAXN],sum,ans,f[MAXN];
int n,k;

struct node{
	ll first;
	int second;
};

struct cmp{
	bool operator()(const node &a,const node &b)const{
		return a.first>b.first;
	}
};

priority_queue <node,vector<node>,cmp> Q;

int main(){
    freopen("bzoj2442.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    	scanf("%lld",&a[i]),sum+=a[i];
    Q.push((node){0,0});
    for(int i=1;i<=n;i++){
    	while(Q.top().second<i-k-1)
    		Q.pop();
    	f[i]=Q.top().first+a[i];
    	Q.push((node){f[i],i});
    }
    for(int i=max(1,n-k);i<=n;i++)
    	ans=max(ans,sum-f[i]);
    printf("%lld",ans);
    return 0;
}