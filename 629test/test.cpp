#include <bits/stdc++.h>
using namespace std;

void solve(){
	cnt=0;
	for(int i=1;i<=n;i++){
		int Max=512;
		while(Max>c[i])Max>>=1;
	}
}

int main(){
	freopen("input","r",stdin);
	while(1){
		cin>>n>>m;
		if((!n)&&(!m)) break;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%d",&c[i]);
		solve();
	}
	return 0;
}
