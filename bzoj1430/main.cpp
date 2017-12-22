#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;
const ll MOD=9999991;

int n;

ll pow(ll x,int k)
{
	ll res=1;
	while(k)
	{
		if(k&1) {res=(res*x)%MOD,k--;}
		x=(x*x)%MOD; k>>=1;
	}
	return res;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);ll ans=1;
	for(ll i=1;i<n;i++)
		ans=(ans*i)%MOD;
	ll mul=pow((ll)n,n-2);
	cout<<(ans*mul)%MOD;
	return 0;
}