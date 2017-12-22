#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a[MAXN],f[MAXN][MAXN],ans;

int main(){
    freopen("bzoj1652.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    memset(f,0xef,sizeof(f));f[1][n]=0;
	for(int i=n-2;i>=0;i--){
		int mul=n-1-i;
		for(int j=1;j+i<=n;j++){
			if(j-1>=1) f[j][j+i]=max(f[j][j+i],f[j-1][j+i]+a[j-1]*mul);
			if(j+i+1<=n) f[j][j+i]=max(f[j][j+i],f[j][j+i+1]+a[j+i+1]*mul);
		}
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i][i]+a[i]*n);
	printf("%d",ans);
    return 0;
}