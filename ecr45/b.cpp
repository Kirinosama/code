#include <bits/stdc++.h>
using namespace std;

int n,k,a[200010];

int main(){
	freopen("input","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int ans=1;
	for(int i=1;i<n;i++){
		int b=upper_bound(a+1,a+n+1,a[i])-a;
		if(b==n+1 || a[b]>a[i]+k) ans++;
	}
	cout<<ans;
	return 0;
}
