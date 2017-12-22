#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps=1e-8;
long long l,r,x,y,k;

int main()
{
	freopen("input","r",stdin);
	cin>>l>>r>>x>>y>>k;
	if(k*x>r || k*y<l)
		printf("NO");
	else 
		printf("YES");
	return 0;
}