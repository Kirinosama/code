#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

int n,k,t;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&k,&t);
	if(t<=k) printf("%d",t);
	else if(t<=n) printf("%d",k);
	else printf("%d",k-(t-n));
	return 0;
}