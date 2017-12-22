#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010

int x,c[MAXN],n,ans,sum;

int main(){
	freopen("input","r",stdin);
	cin>>n;c[1]=1;c[n+1]=-1;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		c[max(i-x,1)]--;
		c[i]++;
	}
	for(int i=1;i<=n;i++){
		sum+=c[i];
		if(sum>0) ans++;
	}
	cout<<ans;
	return 0;
}