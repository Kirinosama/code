#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,MOD;
int a[20],ans;

void solve(){
	for(int i=1;i<=n;i++){
		if(i==1 || i==n) continue;
		if(a[i]>a[i-1] && a[i]<a[i+1]) return;
		if(a[i]<a[i-1] && a[i]>a[i+1]) return;
	}
	ans++;
}

int main(){
	freopen("czy.in","r",stdin);
	freopen("czy.out","w",stdout);
	cin>>n>>MOD;
	for(int i=1;i<=n;i++)
		a[i]=i;
	solve();
	while(next_permutation(a+1,a+1+n))
		solve();
	printf("%d\n",ans%MOD);
	return 0;
}
