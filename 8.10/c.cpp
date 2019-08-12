#include <bits/stdc++.h>
using namespace std;

int n,m,p;
int w[110],val[110];
int f[110][1010];

int main(){
	cin>>n>>m>>p;
	memset(f,0xc0,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)scanf("%d%d",&w[i],&val[i]);
	for(int i=1;i<=n;i++)
		for(int j=i;j>=1;j--)
			for(int k=p;k>=w[i];k--)
				f[j][k]=max(f[j][k],f[j-1][k-w[i]]+val[i]);
	int ans=0xc0c0c0c0;
	for(int i=m;i<=n;i++)
		for(int j=1;j<=p;j++)
			ans=max(ans,f[i][j]);
	cout<<ans;
	return 0;
}
