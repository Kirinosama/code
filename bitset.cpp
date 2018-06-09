#include <bits/stdc++.h>
using namespace std;

bitset <2000010> a;
int n;

int main(){
	scanf("%d",&n);
	a.set(0);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a^=(a<<x);
	}
	int ans=0;
	for(int i=0;i<=2000000;i++)if(a[i])
		ans^=i;
	cout<<ans;
	return 0;
}
