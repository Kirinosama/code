#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20
typedef long long ll;

int n;
ll ans,a[MAXN],m[MAXN];

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){
		d=a,x=1,y=0;
	}
	else{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}

int inv(ll a,ll b){
	ll d,x,y;
	exgcd(a,b,d,x,y);
	return d==1 ? (x+b)%b : -1;
}

int main(){
	freopen("input","r",stdin);
	cin>>n;ll Mul=1;
	for(int i=1;i<=n;i++){
		scanf("%lld %lld",&m[i],&a[i]);
		Mul*=m[i];
	}
	for(int i=1;i<=n;i++){
		ll M=Mul/m[i];
		ans+=a[i]*M*inv(M,m[i]);
	}
	cout<<ans%Mul;
	return 0;
}