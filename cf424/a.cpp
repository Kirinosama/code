#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
int n,k;
int cnt2,cnt5;

int main()
{
	freopen("input","r",stdin);
	cin>>n>>k;
	ll ans=n;
	while(n%2==0) 
		n/=2,cnt2++;
	while(n%5==0)
		n/=5,cnt5++;
	int cur=min(cnt2,cnt5);
	cnt2-=cur,cnt5-=cur;
	while(cur<k)
	{
		if(cnt2)
		{
			ans*=5;
			cnt2--;
			cur++;
		}
		else if(cnt5)
		{
			ans*=2;
			cnt5--;
			cur++;
		}
		else 
		{
			ans*=10;
			cur++;
		}
	}
	cout<<ans;
	return 0;
}
