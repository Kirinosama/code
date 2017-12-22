#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

int minx[MAXN],minx1[MAXN],a[MAXN],maxx,n,k;

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&k);
	minx[0]=1e9;maxx=-1e9;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		minx[i]=min(a[i],minx[i-1]);
		maxx=max(maxx,a[i]);
	}
	if(k==1) cout<<minx[n];
	else if(k>=3) cout<<maxx;
	else{
		int ans=-1e9;
		minx1[n+1]=1e9;
		for(int i=n;i>=1;i--){
			minx1[i]=min(minx1[i+1],a[i]);
		}
		for(int i=1;i<n;i++){
			ans=max(ans,max(minx[i],minx1[i+1]));
		}
		cout<<ans;
	}
	return 0;
}