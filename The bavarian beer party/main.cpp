#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int n,t;
int f[1010][1010];
int a[1010];

void init()
{
	memset(f,-1,sizeof(f));
}

int dp(int l,int r)
{
	if(l>=r)
		return f[l][r]=0;
	if(f[l][r]!=-1)
		return f[l][r];
	for(int i=l+1;i<=r;i+=2)
	{
		if(a[i]==a[l])
		{
			f[l][r]=max(f[l][r],(dp(l+1,i-1)+dp(i+1,r)+1));
		}
		else
		{
			f[l][r]=max(f[l][r],(dp(l+1,i-1)+dp(i+1,r)));
		}	
	}
		if(f[l][r]==-1)
			f[l][r]=0;
		return f[l][r];
}	

void solve()
{
	init();
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(n%2==1)
		cout<<0<<endl;
	else
		cout<<dp(1,n)<<endl;

}

int main()
{
	freopen("input","r",stdin);
	cin>>t;
	while(t--)
		solve();
	return 0;
}
