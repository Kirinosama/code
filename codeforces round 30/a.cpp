#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,k,x,t,ans;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&k,&x);
	for(int i=1;i<=n-k;i++){
		scanf("%d",&t);
		ans+=t;
	}
	for(int i=1;i<=k;i++){
		scanf("%d",&t);
		ans+=x;
	}
	cout<<ans;
	return 0;
}