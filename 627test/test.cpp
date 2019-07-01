#include <bits/stdc++.h>
using namespace std;

int n,i;

int main()
{
	cin>>n;
	for(i=1;i<=n;i=i+1)
	{
		if(n%i==0)
			cout<<i<<' ';
	}
	return 0;
}
