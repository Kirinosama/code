#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;	

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll n,k,p,ans,res;

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b)
		d=a,x=1,y=0;
	else{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}

ll niyuan(ll a,ll b){
	ll d,x,y;
	exgcd(a,b,d,x,y);
	return d==1?(x+b)%b:-1;
}

ll pow(ll x,ll y){
	ll mul=1;
	while(y){
		if(y&1) mul=(mul*x)%p; 
		y>>=1;x=(x*x)%p;
	}
	return mul;
}

int main(){
    freopen("loj6044.in","r",stdin);
    scanf("%lld %lld %lld",&n,&k,&p);
    ans=1;
    ans=(ans*pow(k,n-k-1))%p;
    ans=(ans*pow(n-k,k-1))%p;
    res=1;
    for(ll i=1;i<=n-k;i++)
    	res=(res*i)%p;
    ans=(ans*niyuan(res,p))%p;
  	res=1;
  	for(ll i=1;i<=k-1;i++)
  		res=(res*i)%p;
  	ans=(ans*niyuan(res,p))%p;
  	for(ll i=1;i<=n-1;i++)
  		ans=(ans*i)%p;
  	cout<<ans;
    return 0;
}