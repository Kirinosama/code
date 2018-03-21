#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define INV 3323403
#define MOD 19940417
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll n,m,res1,res2,ans;

ll cal(ll x,ll y){
	ll s1=((y*(y+1))%MOD*(2*y+1))%MOD;
	ll s2=((x*(x-1))%MOD*(2*x-1))%MOD;
	s1-=s2;if(s1<0)s1+=MOD;
	return (s1*INV)%MOD;
}

ll cal2(ll x,ll y){
	return ((x+y)*(y-x+1)/2)%MOD;
}

int main(){
    freopen("bzoj2956.in","r",stdin);
   	scanf("%lld %lld",&n,&m);
   	for(ll i=1;i<=n;i=n/(n/i)+1){
   		ll ed=n/(n/i);
   		res1+=(n*(ed-i+1))%MOD;res1%=MOD;
   		res1-=((n/i)*cal2(i,ed))%MOD;if(res1<0)res1+=MOD;
   	}
   	for(ll i=1;i<=m;i=m/(m/i)+1){
   		ll ed=m/(m/i);
   		res2+=(m*(ed-i+1))%MOD;res2%=MOD;
   		res2-=((m/i)*cal2(i,ed))%MOD;if(res2<0)res2+=MOD;
   	}
   	ans=(res1*res2)%MOD;
    for(ll i=1;i<=min(n,m);i=min(n/(n/i),m/(m/i))+1){
    	ll x=n/i,y=m/i,ed=min(n/(n/i),m/(m/i));
    	ans-=((ed-i+1)*((n*m)%MOD))%MOD;if(ans<0)ans+=MOD;
    	ans-=(((x*y)%MOD)*cal(i,ed))%MOD;if(ans<0)ans+=MOD;
    	ans+=(cal2(i,ed)*((m*x)%MOD))%MOD;ans%=MOD;
    	ans+=(cal2(i,ed)*((n*y)%MOD))%MOD;ans%=MOD;
    }
    printf("%lld\n",ans);
    return 0;
}