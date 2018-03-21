#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,w,a[20],f[1000010];

int main(){
    freopen("catclimb.in","r",stdin);
    freopen("catclimb.out","w",stdout);
    cin>>n>>w;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    memset(f,0xc0,sizeof(f));f[0]=w;
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<n);j++) if(f[j]>=0) f[j]=w;
		for(int j=1;j<(1<<n);j++){
			for(int k=0;k<n;k++)if((1<<k)&j)
				f[j]=max(f[j],f[j-(1<<k)]-a[k+1]);
		}
		if(f[(1<<n)-1]>=0){
			printf("%d",i);return 0;
		}
	}
    return 0;
}