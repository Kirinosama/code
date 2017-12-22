#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll f[5][10010];
int n;

int main(){
    freopen("bzoj1643.in","r",stdin);
    scanf("%d",&n);
    f[0][0]=1;
    for(int i=1;i<=4;i++)
    	for(int j=0;j<=n;j++)
    		for(int k=0;k<=100;k++){
    			if(j-k*k>=0)
    				f[i][j]+=f[i-1][j-k*k];
    		}
    printf("%lld",f[4][n]);
    return 0;
}