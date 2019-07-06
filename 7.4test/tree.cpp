#include <bits/stdc++.h>
using namespace std;

int ans,res,n,du[21],sum;

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&du[i]);
		if(du[i]>=2) ans++;
		else res++;
		sum+=du[i];
	}	
	if(sum!=2*n-2) cout<<-1;
	else cout<<(ans+min(res,2)-1);
	return 0;
}
