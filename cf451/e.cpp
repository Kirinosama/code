#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
ll ans,a[MAXN],cost1[MAXN],cost2[MAXN];
priority_queue <ll> q1,q2;

int main(){
    freopen("cf451.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
    	ll l=(ll)sqrt(a[i]),r=l+1;
    	cost1[i]=min(abs(l*l-a[i]),abs(r*r-a[i]));
    	if(l*l==a[i] || r*r==a[i])
    		cost2[i]=(a[i]==0?2:1);
    	else cost2[i]=0;
    }
    for(int i=1;i<=n;i++){
    	if(i<=n/2) ans+=cost1[i],q1.push(cost1[i]-cost2[i]);
    	else ans+=cost2[i],q2.push(cost2[i]-cost1[i]);
    }
    while(q1.top()+q2.top()>0){
    	ans-=q1.top()+q2.top();
    	int tp1=q1.top(),tp2=q2.top();
    	q1.pop(),q2.pop();q1.push(-tp2),q2.push(-tp1);
    }
    cout<<ans;
    return 0;
}