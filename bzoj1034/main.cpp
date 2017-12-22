#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<deque>
#define inf 2000000000
#define ll long long 
using namespace std;

int n;
int a[100005],b[100005];
int ans1,ans2;
set<int> q;
int solve(int a[],int b[])
{
	int l1=1,r1=n,l2=1,r2=n,ans=0;
	while(l1<=r1&&l2<=r2)
	{
		if(a[l1]>b[l2]){ans+=2;l1++;l2++;}
		else if(a[r1]>b[r2]){ans+=2;r1--;r2--;}
		else {ans+=(a[l1]==b[r2]);l1++;r2--;}
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	printf("%d %d\n",solve(a,b),2*n-solve(b,a));
	return 0;
}