#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
ll a,b;

int main()
{
	freopen("input","r",stdin);
	cin>>a>>b;
	if(b-a>=5) cout<<0;
	else 
	{
		int ans=1;
		for(ll i=a+1;i<=b;i++)
			ans=(ans*(i%10))%10;
		cout<<ans;
	}
	return 0;
}