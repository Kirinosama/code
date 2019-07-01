#include <bits/stdc++.h>
using namespace std;

int f[2][200010];
int n,a[510],sum[510],tot;

int main(){
	//freopen("input","r",stdin);	
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	memset(f,0x3f,sizeof(f));f[1][100000]=0;
	for(int i=1;i<=n;i++){
	//	memset(f[(i+1)&1],0x3f,sizeof(f[(i+1)&1]));
		for(int j=100000-sum[i];j<=100000+sum[i];j++)f[(i+1)&1][j]=0x3f3f3f3f;
		for(int j=100000-sum[i-1];j<=100000+sum[i-1];j++){
			f[(i+1)&1][j]=min(f[(i+1)&1][j],f[i&1][j]+a[i]);
			f[(i+1)&1][j+a[i]]=min(f[(i+1)&1][j+a[i]],f[i&1][j]);
			f[(i+1)&1][j-a[i]]=min(f[(i+1)&1][j-a[i]],f[i&1][j]);
		}
	}
	tot=f[(n+1)&1][100000];
	printf("%d",(sum[n]-tot)/2+tot);
	return 0;
}
