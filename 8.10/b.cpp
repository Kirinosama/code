#include <bits/stdc++.h>
using namespace std;

int n,a[310];
int Max[310][310],f[310][310];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		Max[i][i]=a[i];
	}
	for(int len=2;len<=n;len++)
		for(int i=1;i<=n;i++){
			int j=i+len-1;
			if(j>n) continue;
			for(int k=i;k<j;k++){
				Max[i][j]=max(Max[i][k],Max[k+1][j]);
			}
		}
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int len=2;len<=n;len++)
		for(int i=1;i<=n;i++){
			int j=i+len-1;
			if(j>n) continue;
			for(int k=i;k<j;k++){
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+Max[i][j]);
			}
		}
	cout<<f[1][n];
	return 0;
}
