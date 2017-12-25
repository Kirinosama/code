#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
ll a,b,c;

ll gcd(ll x,ll y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
	freopen("bzoj5105.in","r",stdin);
	scanf("%lld %lld %lld",&a,&b,&c);
	b=a*b/gcd(a,b);
	printf("%lld",b*c/gcd(b,c));
	return 0;
}
