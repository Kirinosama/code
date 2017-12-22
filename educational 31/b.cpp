#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int sum,n,m;

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		sum+=x;
	}
	sum+=n-1;
	if(sum==m) cout<<"YES";
	else cout<<"NO";
	return 0;
}