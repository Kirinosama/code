#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 300010
typedef long long ll;
const ll MOD=1e9+7;
ll a[MAXN],sum[MAXN],w[MAXN];
int n;

void solve1(){
	ll res=0,ans=0;
	for(int i=1;i<=(n+1)/2;i++){
		int l=i,r=n-i+1;
		res=(res+sum[r]-sum[l-1])%MOD;
		if(res<0) res+=MOD;
		if(i<=n/2) ans=(ans+((w[i]+w[n-i+1])*res)%MOD)%MOD;
		else ans=(ans+(res*w[i])%MOD)%MOD;
	}
	cout<<ans;
}

void solve2(){
	ll res=0,ans=0;
	for(int i=1;i<=n/2;i++){
		int l=i,r=n-i+1;
		res=(res+sum[r]-sum[l-1])%MOD;
		if(res<0) res+=MOD;
		ans=(ans+(res*(w[i]+w[n-i+1]))%MOD)%MOD;
	}
	cout<<ans;
}

int main()
{
    freopen("avg.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
    	sum[i]=(sum[i-1]+a[i])%MOD;
    }
   	for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
   	if(n&1) solve1();
   	else solve2();
    return 0;
}