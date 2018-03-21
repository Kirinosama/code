#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define w(x,y) (sum[y]-sum[x-1])
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a[210],f[210][210],sum[210],s[210][210];

int main(){
    freopen("p1880.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=n+1;i<2*n;i++) a[i]=a[i-n];
   	for(int i=1;i<2*n;i++)sum[i]=sum[i-1]+a[i];
    memset(f,0x3f,sizeof(f));int ans=INF;
	for(int i=1;i<2*n;i++) f[i][i]=0,s[i][i]=i;
	for(int l=1;l<n;l++)
		for(int i=1;i<2*n-l;i++){
			int j=i+l;
			for(int k=s[i][j-1];k<=s[i+1][j];k++){
				if(f[i][k-1]+f[k][j]+w(i,j)<f[i][j])
					f[i][j]=f[i][k-1]+f[k][j]+w(i,j),s[i][j]=k;
			}	
			if(l==n-1) ans=min(ans,f[i][j]);
		}
	printf("%d\n",ans);
    memset(f,0xc0,sizeof(f));ans=0;
	for(int i=1;i<2*n;i++) f[i][i]=0;
	for(int l=1;l<n;l++)
		for(int i=1;i<2*n-l;i++){
			int j=i+l;
			f[i][j]=max(f[i+1][j],f[i][j-1])+w(i,j);	
			if(l==n-1) ans=max(ans,f[i][j]);
		}
	printf("%d",ans);
    return 0;
}