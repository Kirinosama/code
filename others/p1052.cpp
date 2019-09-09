#include <bits/stdc++.h>
using namespace std;

int l,s,t,m;
int a[110],b[110],dp[300010];
int book[300010];

int main(){
	freopen("river0.in","r",stdin);
	cin>>l>>s>>t>>m;
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++){
		if(a[i]>=a[i-1]+2520)
			b[i]=b[i-1]+2520;
		else 
			b[i]=b[i-1]+a[i]-a[i-1];
		book[b[i]]=1;
	}
	if(s==t){
		int ans=0;
		for(int i=1;i<=m;i++)if(a[i]%s==0)
			ans++;
		cout<<ans;
		return 0;
	}
	memset(dp,0x3f,sizeof(dp));dp[0]=0;
	for(int i=1;i<=300000;i++){
		for(int j=s;j<=t;j++)if(i-j>=0){
			dp[i]=min(dp[i],dp[i-j]);
		}
		if(book[i]) dp[i]++;
	}
	cout<<dp[300000];
	return 0;
}
