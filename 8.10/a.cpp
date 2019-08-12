#include <bits/stdc++.h>
using namespace std;

int f[5010],a[5010];
int n,m;

int main(){
	//freopen("a.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			if(j-a[i]>=0)
				f[j]=min(f[j],f[j-a[i]]+1);
	}
	printf("%d",f[m]==0x3f3f3f3f?-1:f[m]);
	return 0;
}
