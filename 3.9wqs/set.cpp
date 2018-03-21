#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 10000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ii b[100010],sum1;
ll a[100010],Max1,Max2,sum;
int n,k;

int main(){
    freopen("3.9wqs.in","r",stdin);
    ll mul1=741525,mul2=7007558;
    ll mul3=7007558,mul4=7749083;
    ll sum1=4756633,sum2=2505708;
    cin>>n>>k;Max1=Max2=-1e18;
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
    	sum=(sum+(a[i]%MOD+MOD)%MOD)%MOD;
    	Max2=max(Max2,a[i]);
    	if(Max2>Max1) swap(Max1,Max2);
    }
    if(Max1<=0 && Max2<=0){
    	sum+=((Max1+Max2)%MOD*(ll)k)%MOD;
    	sum%=MOD;
    	printf("%lld",sum);
    	return 0;
    }
   	if(Max2<0){
   		for(;Max2<0 && k;k--) Max2=Max1+Max2,sum=(sum+Max2)%MOD;
   	}
    for(;k>=10000;k-=10000){
    	ll new2=(mul1*Max2+mul2*Max1)%MOD;
    	ll new1=(mul3*Max2+mul4*Max1)%MOD;
    	sum=(sum+Max2*sum1+Max1*sum2)%MOD;
    	Max2=new2,Max1=new1;
    }
    for(int i=1;i<=k;i++){
    	ll new1=(Max1+Max2)%MOD;
    	Max2=Max1,Max1=new1;
    	sum=(sum+new1)%MOD;
    }
    printf("%lld",sum);
    return 0;
}