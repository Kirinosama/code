#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,a,b,c;

int main()
{
	freopen("input","r",stdin);
	cin>>n>>a>>b>>c;
	if(n==1) cout<<0;
	else{
		if(a<=b && a<=c) cout<<a*(n-1);
		else if(b<=a && b<=c) cout<<b*(n-1);
		else{
			if(n==2) cout<<min(a,b);
			else cout<<min(a,b)+(n-2)*c;
		} 
	}
	return 0;
}