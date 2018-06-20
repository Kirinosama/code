#include <bits/stdc++.h>
using namespace std;

#define MAXN 500010
typedef long long ll;
const ll INF=1e18;

int n,q,Q[MAXN],pre[MAXN];
ll a[MAXN],sum[MAXN];

void solve(){
	int x,y;
	scanf("%d%d",&x,&y);
	if(n<=300){
		ll ans=INF;
		for(int i=y;i>=1 && y-i<x;i--){
			ans=min(ans,sum[y]-sum[i-1]+(ll)(x-y+i-1)*a[i]);	
		}
		cout<<ans<<endl;
	}else{
		ll ans=INF;
		for(int i=y;i>=1 && y-i<x;i=pre[i]){
			ans=min(ans,sum[y]-sum[i-1]+(ll)(x-y+i-1)*a[i]);	
		}
		cout<<ans<<endl;
	}
}

void premake(){
	int tail=0;	
	for(int i=1;i<=n;i++){
		if(!tail) Q[++tail]=i,pre[i]=0;
		while(tail && a[Q[tail]]>=a[i]) tail--;
		pre[i]=Q[tail],Q[++tail]=i;
	}
}

int main(){
	freopen("function.in","r",stdin);
	freopen("function2.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	cin>>q;
	premake();
	while(q--)
		solve();
	return 0;
}
